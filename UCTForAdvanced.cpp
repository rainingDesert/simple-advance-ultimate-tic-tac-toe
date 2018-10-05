#include "TTT.h"
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

//struct node
struct Stratagem::UCT::node{
	char* board;
	char* endBlocks;
	node** children;
	node* parent;
	int childrenNum;
	double leafResult;
	int score;
	int totalTurn;
	int depth;
	int takePosNum;
	int takeBlockNum;
	bool userTurn;
	node(char* board, int depth, bool userTurn, char* endBlocks, int takePosNum, int takeBlockNum, int score = 0, int totalTurn = 0){
		this->board = board;
		this->endBlocks = endBlocks;
		this->depth = depth;
		this->userTurn = userTurn;
		this->takePosNum = takePosNum;
		this->takeBlockNum = takeBlockNum;
		this->score = score;
		this->totalTurn = totalTurn;
		this->children = NULL;
		this->parent = NULL;
		this->childrenNum = 0;
		this->leafResult = 0;
	};
	node(char* board, int depth, bool userTurn){
		this->board = board;
		this->endBlocks = NULL;
		this->takeBlockNum = -1;
		this->takePosNum = -1;
		this->depth = depth;
		this->userTurn = userTurn;
		this->score = 0;
		this->totalTurn = 0;
		this->children = NULL;
		this->parent = NULL;
		this->childrenNum = -1;
		this->leafResult = 0;
	};
	node(){
		this->board = NULL;
		this->depth = -1;
		this->userTurn = false;
		this->endBlocks = NULL;
		this->takeBlockNum = -1;
		this->takePosNum = -1;
		this->score = 0;
		this->totalTurn = 0;
		this->children = NULL;
		this->parent = NULL;
		this->childrenNum = -1;
		this->leafResult = 0;
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
	};
};

//instructor
Stratagem::UCTForAdvanced::UCTForAdvanced(Game* game, double c, int limitSim)
: Stratagem::UCT::UCT(game, ((AdvanceTTT*) game)->getBlockNum(), c, limitSim){
	this->attt = (AdvanceTTT*) game;
	this->root = NULL;
}

//destructor
Stratagem::UCTForAdvanced::~UCTForAdvanced(){}

//get result value
double Stratagem::UCTForAdvanced::getResult(node* curNode){
	return this->attt->gameOverTTT(curNode->board, curNode->endBlocks, curNode->takeBlockNum, this->attt->getCompMark());
}

//get children
void Stratagem::UCTForAdvanced::getChildren(node* curNode){
	if(curNode->children != NULL){
		cerr << "already have children" << endl;
		return;
	}

	bool newUserTurn = !curNode->userTurn;
	char mark = curNode->userTurn ? this->attt->getUserMark() : this->attt->getCompMark();
	int newDepth = curNode->depth + 1;
	int takePosNum = curNode->takePosNum;
	int perBlockSize = this->attt->getPerBlockRow() * this->attt->getPerBlockRow();
	char* newEndBlock = NULL;
	char* curEndBlock = new char[this->blockNum];

	curNode->children = new node*[this->boardSize];
	curNode->childrenNum = 0;


	for(int i = 0; i < this->blockNum; i++){
		curEndBlock[i] = curNode->endBlocks[i];
	}

	//get next possible boards
	char*** newBoard = this->attt->getNextBoards(curNode->board, mark, takePosNum, curEndBlock);

	//push nodes
	//certain block
	if(takePosNum != -1){
		for(int i = 0; i < perBlockSize; i++){
			if(newBoard[0][i] != NULL){
				newEndBlock = this->attt->updateBlock(curEndBlock, newBoard[0][i], takePosNum);
				if(newEndBlock[i] == '\0')
					curNode->children[curNode->childrenNum++] = new node(newBoard[0][i], newDepth, newUserTurn, newEndBlock, i, takePosNum);
				else
					curNode->children[curNode->childrenNum++] = new node(newBoard[0][i], newDepth, newUserTurn, newEndBlock, -1, takePosNum);
			}
		}

		delete[] newBoard[0];
		newBoard[0] = NULL;
		delete[] newBoard;
		newBoard = NULL;
		delete[] curEndBlock;
		curEndBlock = NULL;
	}

	//whatever blocks
	else{
		for(int i = 0; i < this->attt->getBlockNum(); i++){
			if(newBoard[i] != NULL){
				for(int j = 0; j < perBlockSize; j++){
					if(newBoard[i][j] != NULL){
						newEndBlock = this->attt->updateBlock(curEndBlock, newBoard[i][j], i);
						if(newEndBlock[j] == '\0')
							curNode->children[curNode->childrenNum++] = new node(newBoard[i][j], newDepth, newUserTurn, newEndBlock, j, i);
						else
							curNode->children[curNode->childrenNum++] = new node(newBoard[i][j], newDepth, newUserTurn, newEndBlock, -1, i);
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

	//detect whether children leaf and save parent
	for(int i = 0; i < curNode->childrenNum; i++){
		double result = this->getResult(curNode->children[i]);
		if(this->attt->result(result)){
			curNode->children[i]->childrenNum = -1;
			curNode->children[i]->leafResult = result;
		}
		curNode->children[i]->parent = curNode;
	}
}

//get children for simulation
Stratagem::UCT::node* Stratagem::UCTForAdvanced::simChildren(node* curNode){
	return this->randomPosition(curNode);
}

//calculate score
double Stratagem::UCTForAdvanced::calScore(node* curNode){
	return Stratagem::UCT::calScore(curNode);
}

///////////////////-----------function to be called from outside----------//////////////////////////////
//randomly get next move
Stratagem::UCT::node* Stratagem::UCTForAdvanced::randomPosition(node* curNode){
	srand((unsigned)time(NULL));
	int count = 0;
	int position = 0;
	int start = 0;
	int perBlockSize = int(this->boardSize / this->blockNum);
	int indexMax = this->blockNum >= perBlockSize ? this->blockNum : perBlockSize;
	int blockPerRow = int(sqrt(this->blockNum));
	int perBlockRow = int(sqrt(perBlockSize));
	int* boardIndex = new int[indexMax];

	//variable for next node
	int block = 0;
	int takePosNum = 0;
	char mark = curNode->userTurn ? this->attt->getUserMark() : this->attt->getCompMark();
	char* newBoard = new char[this->boardSize];
	char* newEndBlock = NULL;
	node* newNode = NULL;
	double result = 0;

	//select a block
	count = 0;
	if(curNode->takePosNum != -1){
		block = curNode->takePosNum;
	}
	else{
		for(int i = 0; i < this->blockNum; i++){
			if(curNode->endBlocks[i] == '\0'){
				boardIndex[count++] = i;
			}
		}
		block = boardIndex[rand() % count];
		count = 0;
	}
	start = (block % blockPerRow) * perBlockRow + int(block / blockPerRow) * perBlockRow * this->game->getRow();

	//select a place inside a block
	count = 0;
	for(int i = 0; i < perBlockSize; i++){
		position = start + (i % perBlockRow) + int(i / perBlockRow) * this->game->getRow();
		if(curNode->board[position] == '\0'){
			boardIndex[count++] = i;
		}
	}

	takePosNum = boardIndex[rand() % count];
	position = start + (takePosNum % perBlockRow) + int(takePosNum / perBlockRow) * this->game->getRow();

	//get new node
	for(int i = 0; i < this->boardSize; i++)
		newBoard[i] = curNode->board[i];
	newBoard[position] = mark;
	newEndBlock = this->attt->updateBlock(curNode->endBlocks, newBoard, block);

	if(newEndBlock[takePosNum] == '\0')
		newNode = new node(newBoard, curNode->depth + 1, !(curNode->userTurn), newEndBlock, takePosNum, block);
	else
		newNode = new node(newBoard, curNode->depth + 1, !(curNode->userTurn), newEndBlock, -1, block);

	result = this->getResult(newNode);

	if(this->attt->result(result)){
		newNode->childrenNum = -1;
		newNode->leafResult = result;
	}

	delete[] boardIndex;
	boardIndex = NULL;

	return newNode;
}

//do UCT search for advance tic-tac-toe
int Stratagem::UCTForAdvanced::UCTSearch(){
	node* curNode = NULL;
	double result = 0;
	int simTime = 0;
	int position = 0;

	//search position of the node
	// if root hasn't been initialized
	if(this->root == NULL){
		char* newBoard = new char[boardSize];
		char* newEndBlocks = new char[blockNum];
		char* board = this->attt->getboard();
		char* endBlocks = this->attt->getEndBlocks();

		for(int i = 0; i < boardSize; i++){
			newBoard[i] = board[i];
		}
		for(int i = 0; i < blockNum; i++){
			newEndBlocks[i] = endBlocks[i];
		}

		this->root = new node(newBoard, 0, false, newEndBlocks, this->attt->getNextBlock(), this->attt->getLastBlock());
	}

	//if children of root have not been expanded
	else if(this->root->children == NULL){
		char* newBoard = new char[this->boardSize];
		char* newEndBlocks = new char[this->blockNum];
		char* board = this->attt->getboard();
		char* endBlocks = this->attt->getEndBlocks();
		for(int i = 0; i < this->boardSize; i++)
			newBoard[i] = board[i];
		for(int i = 0; i < this->blockNum; i++)
			newEndBlocks[i] = endBlocks[i];

		delete this->root;
		this->root = new node(newBoard, 0, false, newEndBlocks, this->attt->getNextBlock(), this->attt->getLastBlock());
	}

	//children exist
	else{
		node* tempNode = NULL;
		for(int i = 0; i < this->root->childrenNum; i++){
			if(this->root->children[i]->takePosNum == this->attt->getNextBlock() && this->root->children[i]->takeBlockNum == this->attt->getLastBlock())
				tempNode = this->root->children[i];
			else
				this->deleteNode(this->root->children[i]);
		}
		delete[] this->root->children;
		this->root->children = NULL;
		delete this->root;
		tempNode->parent = NULL;
		this->descendNode(tempNode);
		this->root = tempNode;
	}

	//do search
	//search next depth in initial
	curNode = this->root;

	while(curNode->depth <= 1){

		//select a node to expand
		curNode = this->selection(this->root);

		//simulation
		result = this->simulation(curNode);

		//back up result
		this->backup(curNode, result);

		//depth 1 finishes
		if(this->root->totalTurn >= this->root->childrenNum)
			break;
	}

	//within simulation time
	for(simTime = 0; simTime < this->limitSim; simTime++){
		//select a node to expand
		curNode = this->selection(this->root);

		//simulation
		result = this->simulation(curNode);

		//back up result
		this->backup(curNode, result);
	}

	//get result
	curNode = this->bestChild(this->root);
	position = this->attt->getPosition(curNode->board, this->root->board) + 1;
	//delete nodes
	for(int i = 0; i < this->root->childrenNum; i++){
		if(this->root->children[i] != curNode){
			this->deleteNode(this->root->children[i]);
		}
	}

	//update root node
	delete[] this->root->children;
	delete this->root;
	this->descendNode(curNode);
	this->root = curNode;
	this->root->parent = NULL;
	curNode = NULL;

	return position;
}