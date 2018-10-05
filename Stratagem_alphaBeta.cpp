#include "TTT.h"
#include <iostream>
#include <iomanip>
#include <time.h>
#include <math.h>
using namespace std;


struct Stratagem::AlphaBeta::node{
	char* board;
	int depth;
	int takePosNum;
	int takeBlockNum;
	bool userTurn;
	char* endBlocks;
	char* dangerBlocks;
	node(char* board, int depth, bool userTurn, char* endBlocks, char* dangerBlocks, int takePosNum, int takeBlockNum){
		this->board = board;
		this->endBlocks = endBlocks;
		this->dangerBlocks = dangerBlocks;
		this->depth = depth;
		this->userTurn = userTurn;
		this->takePosNum = takePosNum;
		this->takeBlockNum = takeBlockNum;
	};
	node(char* board, int depth, bool userTurn){
		this->board = board;
		this->endBlocks = NULL;
		this->takeBlockNum = -1;
		this->depth = depth;
		this->userTurn = userTurn;
		this->dangerBlocks = NULL;
	};
	node(){
		this->board = NULL;
		this->depth = -1;
		this->userTurn = false;
		this->endBlocks = NULL;
		this->takeBlockNum = -1;
		this->dangerBlocks = NULL;
	};
	~node(){
		if(this->board != NULL){
			delete[] this->board;
			this->board = NULL;
		}
		if(this->endBlocks != NULL){
			delete[] this->endBlocks;
			this->endBlocks = NULL;
		}
		if(this->dangerBlocks != NULL){
			delete[] this->dangerBlocks;
			this->dangerBlocks = NULL;
		}
	};
};

//randomly select position
int Stratagem::randomMove(char* board, int length){
	srand((unsigned)time(NULL));
	int count = 0;
	int* boardIndex = new int[length];
	for(int i = 1;i <= length; i++){
		if(board[i - 1] == '\0')
			boardIndex[count++] = i;
	}
	return boardIndex[rand() % count];
}

//randomly select position for advance TTT
int Stratagem::randomMoveForAdvance(Game* game){
	srand((unsigned)time(NULL));
	int count = 0;
	AdvanceTTT* attt = (AdvanceTTT*)game;
	char* board = attt->getboard();
	int blockNum = attt->getBlockNum();
	int perBlockSize = attt->getPerBlockRow() * attt->getPerBlockRow();
	int indexMax = blockNum >= perBlockSize ? blockNum : perBlockSize;
	int block = 0;
	int blockPerRow = int(sqrt(blockNum));
	int perBlockRow = attt->getPerBlockRow();
	int position = 0;
	int start = 0;
	int* boardIndex = new int[indexMax];

	//select a block
	if(attt->getNextBlock() != -1){
		block = attt->getNextBlock();
	}
	else{
		for(int i = 0; i < blockNum; i++){
			if(attt->blockUseful(i) == '\0'){
				boardIndex[count++] = i;
			}
		}
		block = boardIndex[rand() % count];
		count = 0;
	}
	start = (block % blockPerRow) * perBlockRow + int(block / blockPerRow) * perBlockRow * (blockPerRow * perBlockRow);

	//select a place inside a block
	for(int i = 0; i < perBlockSize; i++){
		position = start + (i % perBlockRow) + int(i / perBlockRow) * (blockPerRow * perBlockRow);
		if(board[position] == '\0'){
			boardIndex[count++] = position;
		}
	}

	position = boardIndex[rand() % count];
	return position + 1;
}

////////////////////////////////////////------AlphaBeta Next-------///////////////////////////////////////////////////////////

//instructor
Stratagem::AlphaBeta::AlphaBeta(){}

//initialize alphaBeta object
Stratagem::AlphaBeta::AlphaBeta(char* board, int length){
	char* newBoard = new char[length];
	for(int i = 0; i < length; i++)
		newBoard[i] = board[i];

	this->heap = new node[length * length + 1];
	this->alphas = new double[length];
	this->betas = new double[length];
	this->length = length * length + 1;
	this->boardSize = length;
	this->top = 0;
	this->pushNode(newBoard, 0, false);

	this->limitDepth = 10 * length; 	//no limit;

	for(int i = 0; i < length; i++){
		this->alphas[i] = -1000;
		this->betas[i] = 1000;
	}
}

//destructor
Stratagem::AlphaBeta::~AlphaBeta(){
	if(this->heap != NULL){
		delete[] this->heap;
		this->heap = NULL;
	}
	if(this->alphas != NULL){
		delete[] this->alphas;
		this->alphas = NULL;
	}
	if(this->betas != NULL){
		delete[] this->betas;
		this->betas = NULL;
	}
}

//get node (pop heap)
Stratagem::AlphaBeta::node* Stratagem::AlphaBeta::getNode(){
	if(this->top == 0){
		cerr << "empty heap" << endl;
		int i = 0;
		cin >> i;
		return NULL;
	}

	return &(this->heap[--this->top]);
} 

//push node into heap
void Stratagem::AlphaBeta::pushNode(char* newBoard, int depth, bool userTurn){
	if(this->top > this->length){
		cerr << "out of general heap" << endl;
		return;
	}

	if(this->heap[this->top].board != NULL){
		delete[] this->heap[this->top].board;
	}
	this->heap[this->top].board = newBoard;
	this->heap[this->top].depth = depth;
	this->heap[this->top++].userTurn = userTurn;
}

//get result for alpha-beta search
double Stratagem::AlphaBeta::getResult(node* curNode, Game* game){
	return game->gameOverTTT(curNode->board, game->getCompMark());
}

//get next steps
void Stratagem::AlphaBeta::pushNextSteps(node* currentNode, Game* game){
	bool newUserTurn = !currentNode->userTurn;
	char mark = currentNode->userTurn ? game->getUserMark() : game->getCompMark();
	int newDepth = currentNode->depth + 1;

	//get next possible boards
	char** newBoard = game->getNextBoards(currentNode->board, mark);

	for(int i = 0; i < this->boardSize; i++){
		if(newBoard[i] != NULL){
			this->pushNode(newBoard[i], newDepth, newUserTurn);
		}
	}

	delete[] newBoard;
	newBoard = NULL;
}

//do alpha-beta search
int Stratagem::AlphaBeta::doAlphaBeta(Game* game){
	int nextDepth = 0;
	int currentDepth = 0;
	bool userTurn = 0;
	node* currentNode = this->getNode();
	char* tempBoard = new char[this->boardSize];
	char* bestBoard = NULL;
	char* rootBoard = new char[this->boardSize];
	double result;

	for(int i = 0; i < this->boardSize; i++){
		rootBoard[i] = currentNode->board[i];
	}

	while(true){

		currentDepth = currentNode->depth;
		userTurn = currentNode->userTurn;
		result = this->getResult(currentNode, game);

		//reach leaf
		if(!game->result(result) && currentDepth < this->limitDepth){
			if(currentNode->depth == 1){
				for(int i = 0; i < this->boardSize; i++){
					tempBoard[i] = currentNode->board[i];
				}
			}
			this->pushNextSteps(currentNode, game);
			currentNode = this->getNode();

			continue;
		}

		//leaf nodes
		if(userTurn){
			this->betas[currentDepth] = result;
		}
		else{	
			this->alphas[currentDepth] = result;
		}

		//get next node
		if(currentDepth == 1){
			for(int i = 0; i < this->boardSize; i++){
				tempBoard[i] = currentNode->board[i];
			}
		}
		if(this->top == 0){
			nextDepth = 0;
		}
		else{
			currentNode = this->getNode();
			nextDepth = currentNode->depth;
		}

		// update alpha & beta
		for(int i = currentDepth; i > nextDepth - 1; i--){

			if(i == 0){
				break;
			}
			if(userTurn){	//parent node is a computer turn (max turn)

				//pass value to upper layer
				if(this->alphas[i - 1] < this->betas[i]){
					this->alphas[i - 1] = this->betas[i];
					if(i == 1){
						bestBoard = tempBoard;
						tempBoard = new char[this->boardSize];
					}
				}

				//try pruning
				if(i == nextDepth && i > 1 && this->betas[i - 2] <= this ->alphas[i - 1]){
					while(currentNode->depth == i && this->top != 0){
						currentNode = this->getNode();
					}
					nextDepth = (currentNode->depth != i) ? currentNode->depth : 0;
				}
				this->betas[i] = 1000;
			}
			else{	//parent node is a user turn

				//pass value to upper layer
				if(this->betas[i - 1] > this->alphas[i]){
					this->betas[i - 1] = this->alphas[i];
					if(i == 1){
						bestBoard = tempBoard;
						tempBoard = new char[this->boardSize];
					}
				}

				//try pruning
				if(i == nextDepth && i > 1 && this->alphas[i - 2] >= this ->betas[i - 1]){	//pruning
					while(currentNode->depth == i && this->top != 0){
						currentNode = this->getNode();
					}
					nextDepth = (currentNode->depth != i) ? currentNode->depth : 0;
				}
				this->alphas[i] = -1000;
			}

			userTurn = !userTurn;	//go to parent node
		}

		//return to root
		if(nextDepth == 0)
			break;
	}

	int position = game->getPosition(rootBoard, bestBoard) + 1;
	delete[] tempBoard;
	tempBoard = NULL;
	delete[] bestBoard;
	bestBoard = NULL;
	delete[] rootBoard;
	rootBoard= NULL;
	return position;
}

/////////////////////////////////////////----AlphaBeta for Advanced next----//////////////////////////////////////////////////////////

//initalize alpha beta for adcenced TTT
Stratagem::AlphaBetaForAdvanced::AlphaBetaForAdvanced(AdvanceTTT* attt, int limitDepth = -1):Stratagem::AlphaBeta::AlphaBeta(){
	int length = attt->getRow();
	this->blockNum = attt->getBlockNum();
	this->boardSize = length * length;
	this->length = this->boardSize * this->boardSize + 1;
	this->heap = new node[this->length];
	this->alphas = new double[this->boardSize];
	this->betas = new double[this->boardSize];
	this->top = 0;
	char* tempBlock = attt->getEndBlocks();
	char* tempBoard = attt->getboard();
	char* tempDanger = attt->getDangerBlocks();
	char* endBlocks = new char[this->blockNum];
	char* dangerBlocks = new char[this->blockNum];
	char* board = new char[this->boardSize];

	for(int i = 0; i < this->blockNum; i++){
		endBlocks[i] = tempBlock[i];
		dangerBlocks[i] = tempDanger[i];
	}
	for(int i = 0; i < this->boardSize; i++){
		board[i] = tempBoard[i];
	}

	this->pushNode(board, dangerBlocks, 0, false, endBlocks, attt->getNextBlock(), attt->getLastBlock());

	for(int i = 0; i < this->boardSize; i++){
		this->alphas[i] = -1000;
		this->betas[i] = 1000;
	}

	if(limitDepth == -1)
		this->limitDepth = 10 * this->boardSize; //no limit
	else
		this->limitDepth = limitDepth;
}

//destructor for alphaBeta advance
Stratagem::AlphaBetaForAdvanced::~AlphaBetaForAdvanced(){}

//push node into heap for advance TTT
void Stratagem::AlphaBetaForAdvanced::pushNode(char* newBoard, char* dangerBlocks, int depth, bool userTurn, char* endBlocks, int takePosNum, int takeBlockNum){
	if(this->top > this->length){
		cerr << "out of general heap" << endl;
		return;
	}

	if(this->heap[this->top].board != NULL)
		delete[] this->heap[this->top].board;
	if(this->heap[this->top].endBlocks != NULL)
		delete[] this->heap[this->top].endBlocks;
	if(this->heap[this->top].dangerBlocks != NULL)
		delete[] this->heap[this->top].dangerBlocks;
	this->heap[this->top].board = newBoard;
	this->heap[this->top].depth = depth;
	this->heap[this->top].userTurn = userTurn;
	this->heap[this->top].endBlocks = endBlocks;
	this->heap[this->top].dangerBlocks = dangerBlocks;
	this->heap[this->top].takePosNum = takePosNum;
	this->heap[this->top++].takeBlockNum = takeBlockNum;
}

//get result for alpha-beta search, apply for advanced TTT
double Stratagem::AlphaBetaForAdvanced::getResult(node* curNode, Game* game){
	AdvanceTTT* attt = (AdvanceTTT*)game;
	double result = attt->gameOverTTT(curNode->board, curNode->endBlocks, curNode->takeBlockNum, game->getCompMark());
	attt = NULL;
	return result;
}

//overload push next step for advance TTT
void Stratagem::AlphaBetaForAdvanced::pushNextSteps(node* currentNode, Game* game){
	AdvanceTTT* attt = (AdvanceTTT*)game;
	bool newUserTurn = !currentNode->userTurn;
	char mark = currentNode->userTurn ? attt->getUserMark() : attt->getCompMark();
	int newDepth = currentNode->depth + 1;
	int takePosNum = currentNode->takePosNum;
	int perBlockSize = attt->getPerBlockRow() * attt->getPerBlockRow();
	char* newEndBlock = NULL;
	char* newDangerBlock = NULL;
	char* curEndBlock = new char[this->blockNum];
	char* curDangerBlock = new char[this->blockNum];

	for(int i = 0; i < this->blockNum; i++){
		curEndBlock[i] = currentNode->endBlocks[i];
		curDangerBlock[i] = currentNode->dangerBlocks[i];
	}

	//get next possible boards
	char*** newBoard = attt->getNextBoards(currentNode->board, mark, takePosNum, curEndBlock);

	//push nodes
	//certain block
	if(takePosNum != -1){
		for(int i = 0; i < perBlockSize; i++){
			if(newBoard[0][i] != NULL){
				newEndBlock = attt->updateBlock(curEndBlock, newBoard[0][i], takePosNum);
				newDangerBlock = attt->updateDangerBlock(curDangerBlock, newBoard[0][i], takePosNum);
				if(newEndBlock[i] == '\0')
					this->pushNode(newBoard[0][i], newDangerBlock, newDepth, newUserTurn, newEndBlock, i, takePosNum);
				else
					this->pushNode(newBoard[0][i], newDangerBlock, newDepth, newUserTurn, newEndBlock, -1, takePosNum);
			}
		}

		delete[] newBoard[0];
		newBoard[0] = NULL;
		delete[] newBoard;
		newBoard = NULL;
		delete[] curEndBlock;
		curEndBlock = NULL;
		delete[] curDangerBlock;
		curDangerBlock = NULL;
		return;
	}

	//whatever blocks
	for(int i = 0; i < attt->getBlockNum(); i++){
		if(newBoard[i] != NULL){
			for(int j = 0; j < perBlockSize; j++){
				if(newBoard[i][j] != NULL){
					newEndBlock = attt->updateBlock(curEndBlock, newBoard[i][j], i);
					newDangerBlock = attt->updateDangerBlock(curDangerBlock, newBoard[i][j], i);
					if(newEndBlock[j] == '\0')
						this->pushNode(newBoard[i][j], newDangerBlock, newDepth, newUserTurn, newEndBlock, j, i);
					else
						this->pushNode(newBoard[i][j], newDangerBlock, newDepth, newUserTurn, newEndBlock, -1, i);
				}
			}

			delete[] newBoard[i];
			newBoard[i] = NULL;
		}
	}
	delete[] curEndBlock;
	curEndBlock = NULL;
	delete[] curDangerBlock;
	curDangerBlock = NULL;
	delete[] newBoard;
	newBoard = NULL;
}

/////////////////////////////////////////----HAlphaBeta for Advanced next----//////////////////////////////////////////////////////////
Stratagem::HAlphaBetaForAdvanced::HAlphaBetaForAdvanced(AdvanceTTT* attt, int limitDepth):Stratagem::AlphaBetaForAdvanced::AlphaBetaForAdvanced(attt, limitDepth){
	this->points = new int[4];
	this->points[0] = 0;
	this->points[1] = 1;
	this->points[2] = 8;
	this->points[3] = 100;
}

Stratagem::HAlphaBetaForAdvanced::~HAlphaBetaForAdvanced(){
	if(this->points != NULL){
		delete[] this->points;
		this->points = NULL;
	}
}

//calculate heuristic value
double Stratagem::HAlphaBetaForAdvanced::getResult(node* curNode, Game* game){
	AdvanceTTT* attt = (AdvanceTTT*) game;
	double result = attt->gameOverTTT(curNode->board, curNode->endBlocks, curNode->takeBlockNum, game->getCompMark());
	if(curNode->depth < this->limitDepth || game->result(result)){
		attt = NULL;
		return result;
	}
	double sumPoint = attt->HResultTTT(curNode->board, curNode->dangerBlocks, this->points, curNode->takePosNum, game->getCompMark());
	attt = NULL;
	return sumPoint/ (10.0 * this->points[3]);
}


/////////////////////////////////////////----HAlphaBeta for Ultimate next----//////////////////////////////////////////////////////////
// general constructor
Stratagem::HAlphaBetaForUltimate::HAlphaBetaForUltimate(UltimateTTT* uttt, int limitDepth, int* inPoints, int* outPoints): Stratagem::AlphaBetaForAdvanced::AlphaBeta(){
	int length = uttt->getRow();
	this->blockNum = uttt->getBlockNum();
	this->boardSize = length * length;
	this->length = this->boardSize * this->boardSize + 1;
	this->heap = new node[this->length];
	this->alphas = new double[this->boardSize];
	this->betas = new double[this->boardSize];
	this->top = 0;
	char* tempBlock = uttt->getEndBlocks();
	char* tempBoard = uttt->getboard();
	char* endBlocks = new char[this->blockNum];
	char* board = new char[this->boardSize];

	for(int i = 0; i < this->blockNum; i++){
		endBlocks[i] = tempBlock[i];
	}
	for(int i = 0; i < this->boardSize; i++){
		board[i] = tempBoard[i];
	}

	this->pushNode(board, 0, false, endBlocks, uttt->getNextBlock(), uttt->getLastBlock());

	for(int i = 0; i < this->boardSize; i++){
		this->alphas[i] = -1000;
		this->betas[i] = 1000;
	}

	if(limitDepth == -1)
		this->limitDepth = 10 * this->boardSize; //no limit
	else
		this->limitDepth = limitDepth;

	//heuristic points
	this->inPoints = new int[4];
	for(int i = 0; i < 4; i++){
		this->inPoints[i] = inPoints[i];
	}

	this->outPoints = new int[4];
	for(int i = 0; i < 4; i++){
		this->outPoints[i] = outPoints[i];
	}
}

// constructor
Stratagem::HAlphaBetaForUltimate::HAlphaBetaForUltimate(UltimateTTT* uttt, int limitDepth): Stratagem::AlphaBetaForAdvanced::AlphaBeta(){
	int length = uttt->getRow();
	this->blockNum = uttt->getBlockNum();
	this->boardSize = length * length;
	this->length = this->boardSize * this->boardSize + 1;
	this->heap = new node[this->length];
	this->alphas = new double[this->boardSize];
	this->betas = new double[this->boardSize];
	this->top = 0;
	char* tempBlock = uttt->getEndBlocks();
	char* tempBoard = uttt->getboard();
	char* endBlocks = new char[this->blockNum];
	char* board = new char[this->boardSize];

	for(int i = 0; i < this->blockNum; i++){
		endBlocks[i] = tempBlock[i];
	}
	for(int i = 0; i < this->boardSize; i++){
		board[i] = tempBoard[i];
	}

	this->pushNode(board, 0, false, endBlocks, uttt->getNextBlock(), uttt->getLastBlock());

	for(int i = 0; i < this->boardSize; i++){
		this->alphas[i] = -1000;
		this->betas[i] = 1000;
	}

	if(limitDepth == -1)
		this->limitDepth = 10 * this->boardSize; //no limit
	else
		this->limitDepth = limitDepth;

	//heuristic points
	this->inPoints = new int[4];
	this->inPoints[0] = 0, this->inPoints[1] = 1, this->inPoints[2] = 5, this->inPoints[3] = 50;
	// this->inPoints[0] = 0, this->inPoints[1] = 1, this->inPoints[2] = 15, this->inPoints[3] = 50;

	this->outPoints = new int[4];
	this->outPoints[0] = 0, this->outPoints[1] = 1, this->outPoints[2] = 2, this->outPoints[3] = 3;
	// this->outPoints[0] = 0, this->outPoints[1] = 1, this->outPoints[2] = 3, this->outPoints[3] = 5;
}

//destructor
Stratagem::HAlphaBetaForUltimate::~HAlphaBetaForUltimate(){
	if(this->heap != NULL){
		delete[] this->heap;
		this->heap = NULL;
	}
	if(this->alphas != NULL){
		delete[] this->alphas;
		this->alphas = NULL;
	}
	if(this->betas != NULL){
		delete[] this->betas;
		this->betas = NULL;
	}
	if(this->inPoints != NULL){
		delete[] this->inPoints;
		this->inPoints = NULL;
	}
	if(this->outPoints != NULL){
		delete[] this->outPoints;
		this->outPoints = NULL;
	}
}

//push node into heap
void Stratagem::HAlphaBetaForUltimate::pushNode(char* newBoard, int depth, bool userTurn, char* endBlocks, int takePosNum, int takeBlockNum){
	if(this->top > this->length){
		cerr << "out of general heap" << endl;
		return;
	}

	if(this->heap[this->top].board != NULL)
		delete[] this->heap[this->top].board;
	if(this->heap[this->top].endBlocks != NULL)
		delete[] this->heap[this->top].endBlocks;
	this->heap[this->top].board = newBoard;
	this->heap[this->top].depth = depth;
	this->heap[this->top].userTurn = userTurn;
	this->heap[this->top].endBlocks = endBlocks;
	this->heap[this->top].takePosNum = takePosNum;
	this->heap[this->top++].takeBlockNum = takeBlockNum;
}

//calculate heuristic value
double Stratagem::HAlphaBetaForUltimate::getResult(node* curNode, Game* game){
	UltimateTTT* uttt = (UltimateTTT*) game;
	double result = uttt->gameOverTTT(curNode->endBlocks, uttt->getCompMark());
	if(curNode->depth < this->limitDepth || uttt->result(result)){
		uttt = NULL;
		return result;
	}
	double sumPoint = uttt->HResultTTT(curNode->board, curNode->endBlocks, this->inPoints, this->outPoints, uttt->getCompMark());
	uttt = NULL;
	return sumPoint / (10.0 * this->inPoints[3] * this->outPoints[3]);
}

//push next steps into heap
void Stratagem::HAlphaBetaForUltimate::pushNextSteps(node* currentNode, Game* game){
	UltimateTTT* uttt = (UltimateTTT*)game;
	bool newUserTurn = !currentNode->userTurn;
	char mark = currentNode->userTurn ? uttt->getUserMark() : uttt->getCompMark();
	int newDepth = currentNode->depth + 1;
	int takePosNum = currentNode->takePosNum;
	int perBlockSize = uttt->getPerBlockRow() * uttt->getPerBlockRow();
	char* newEndBlock = NULL;
	char* curEndBlock = new char[this->blockNum];

	for(int i = 0; i < this->blockNum; i++){
		curEndBlock[i] = currentNode->endBlocks[i];
	}

	//get next possible boards
	char*** newBoard = uttt->getNextBoards(currentNode->board, mark, takePosNum, curEndBlock);

	//push nodes
	//certain block
	if(takePosNum != -1){
		for(int i = 0; i < perBlockSize; i++){
			if(newBoard[0][i] != NULL){
				newEndBlock = uttt->updateBlock(curEndBlock, newBoard[0][i], takePosNum, mark);
				if(newEndBlock[i] == '\0')
					this->pushNode(newBoard[0][i], newDepth, newUserTurn, newEndBlock, i, takePosNum);
				else
					this->pushNode(newBoard[0][i], newDepth, newUserTurn, newEndBlock, -1, takePosNum);
			}
		}

		delete[] newBoard[0];
		newBoard[0] = NULL;
		delete[] newBoard;
		newBoard = NULL;
		delete[] curEndBlock;
		curEndBlock = NULL;
		return;
	}

	//whatever blocks
	for(int i = 0; i < uttt->getBlockNum(); i++){
		if(newBoard[i] != NULL){
			for(int j = 0; j < perBlockSize; j++){
				if(newBoard[i][j] != NULL){
					newEndBlock = uttt->updateBlock(curEndBlock, newBoard[i][j], i, mark);
					if(newEndBlock[j] == '\0')
						this->pushNode(newBoard[i][j], newDepth, newUserTurn, newEndBlock, j, i);
					else
						this->pushNode(newBoard[i][j], newDepth, newUserTurn, newEndBlock, -1, i);
				}
			}

			delete[] newBoard[i];
			newBoard[i] = NULL;
		}
	}
	delete[] curEndBlock;
	curEndBlock = NULL;
	delete[] newBoard;
	newBoard = NULL;
}


/////////////////////////////////////////----functions for outside----//////////////////////////////////////////////////////////
//instructor
Stratagem::Stratagem(){
	this->uct = NULL;
}

//destructor
Stratagem::~Stratagem(){
	if(this->uct != NULL){
		this->deleteUCT();
	}
}

//call alpha-beta from outside
int Stratagem::alphaBetaSearch(Game* game){
	int length = game->getRow() * game->getRow();
	AlphaBeta* ab =new AlphaBeta(game->getboard(), length);
	int position = ab->doAlphaBeta(game);
	delete ab;
	ab = NULL;
	return position;
}

//call alpha-beta for advance from outside
int Stratagem::alphaBetaAdvanceSearch(Game* game){
	AdvanceTTT* attt = (AdvanceTTT*) game;
	AlphaBetaForAdvanced* abfa = new AlphaBetaForAdvanced(attt);
	int position = abfa->doAlphaBeta(attt);
	delete abfa;
	abfa = NULL;
	attt = NULL;
	return position;
}

//call heuristic alpha-beta for advance from outside
int Stratagem::hAlphaBetaAdvanceSearch(Game* game, int limitDepth){
	AdvanceTTT* attt = (AdvanceTTT*) game;
	HAlphaBetaForAdvanced* habfa = new HAlphaBetaForAdvanced(attt, limitDepth);
	int position = habfa->doAlphaBeta(attt);
	delete habfa;
	habfa = NULL;
	attt = NULL;
	return position;
}

//call heuristic alpha-bata for ultimate from outside
int Stratagem::hAlphaBetaUltimateSearch(Game* game, int limitDepth, int* inPoints, int* outPoints){
	UltimateTTT* uttt = (UltimateTTT*) game;
	HAlphaBetaForUltimate* habfu = NULL;
	if(inPoints == NULL || outPoints == NULL){
		habfu = new HAlphaBetaForUltimate(uttt, limitDepth);
	}
	else{
		habfu = new HAlphaBetaForUltimate(uttt, limitDepth, inPoints, outPoints);
	}
	int position = habfu->doAlphaBeta(uttt);
	delete habfu;
	habfu = NULL;
	uttt = NULL;
	return position;
}

//call UCT for advance from outside
int Stratagem::UCTAdvancedSearch(Game* game, double c, int limitSim){
	//start UCT
	if(uct == NULL){
		uct = new UCTForAdvanced(game, c, limitSim);
	}

	int position = uct->UCTSearch();
	deleteUCT();
	return position;
}

//call UCT for ultimate from outside
int Stratagem::UCTUltimateSearch(Game* game, double c, int limitSim){
	//start UCT
	if(uct == NULL){
		uct = new UCTForUltimate(game, c, limitSim);
	}

	int position = uct->UCTSearch();
	deleteUCT();
	return position;
}

//delete uct
void Stratagem::deleteUCT(){
	if(uct != NULL){
		delete uct;
		uct = NULL;
	}
}