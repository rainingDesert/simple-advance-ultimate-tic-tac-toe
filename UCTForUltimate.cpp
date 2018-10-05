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
Stratagem::UCTForUltimate::UCTForUltimate(Game* game, double c, int limitSim)
: Stratagem::UCT::UCT(game, ((UltimateTTT*)(game))->getBlockNum(), c, limitSim){
	this->uttt = ((UltimateTTT*)(game));
	this->root = NULL;
}

//destructor
Stratagem::UCTForUltimate::~UCTForUltimate(){}

//get result value
double Stratagem::UCTForUltimate::getResult(node* curNode){
	return (this->uttt->gameOverTTT(curNode->endBlocks, this->uttt->getCompMark()));
}

//get children nodes
void Stratagem::UCTForUltimate::getChildren(node* curNode){
	bool newUserTurn = !curNode->userTurn;
	char mark = curNode->userTurn ? this->uttt->getUserMark() : this->uttt->getCompMark();
	int newDepth = curNode->depth + 1;
	int takePosNum = curNode->takePosNum;
	int perBlockSize = this->uttt->getPerBlockRow() * this->uttt->getPerBlockRow();
	char* newEndBlock = NULL;
	char* curEndBlock = new char[this->blockNum];
	curNode->children = new node*[this->boardSize];

	for(int i = 0; i < this->blockNum; i++){
		curEndBlock[i] = curNode->endBlocks[i];
	}

	//get next possible boards
	char*** newBoard = this->uttt->getNextBoards(curNode->board, mark, takePosNum, curEndBlock);

	//push nodes
	//certain block
	if(takePosNum != -1){
		for(int i = 0; i < perBlockSize; i++){
			if(newBoard[0][i] != NULL){
				newEndBlock = this->uttt->updateBlock(curEndBlock, newBoard[0][i], takePosNum, mark);
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
		for(int i = 0; i < this->uttt->getBlockNum(); i++){
			if(newBoard[i] != NULL){
				for(int j = 0; j < perBlockSize; j++){
					if(newBoard[i][j] != NULL){
						newEndBlock = this->uttt->updateBlock(curEndBlock, newBoard[i][j], i, mark);
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
		if(this->uttt->result(result)){
			curNode->children[i]->childrenNum = -1;
			curNode->children[i]->leafResult = result;
		}
		curNode->children[i]->parent = curNode;
	}
}

//get children nodes for simulation
Stratagem::UCT::node* Stratagem::UCTForUltimate::simChildren(node* curNode){
	return this->randomPosition(curNode);
}

//calculate score for current node
double Stratagem::UCTForUltimate::calScore(node* curNode){
	return Stratagem::UCT::calScore(curNode);
}			

//get next move randomly
Stratagem::UCT::node* Stratagem::UCTForUltimate::randomPosition(node* curNode){
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
	char mark = curNode->userTurn ? this->uttt->getUserMark() : this->uttt->getCompMark();
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
	newEndBlock = this->uttt->updateBlock(curNode->endBlocks, newBoard, block, mark);

	if(newEndBlock[takePosNum] == '\0')
		newNode = new node(newBoard, curNode->depth + 1, !(curNode->userTurn), newEndBlock, takePosNum, block);
	else
		newNode = new node(newBoard, curNode->depth + 1, !(curNode->userTurn), newEndBlock, -1, block);

	result = this->getResult(newNode);

	if(this->uttt->result(result)){
		newNode->childrenNum = -1;
		newNode->leafResult = result;
	}

	delete[] boardIndex;
	boardIndex = NULL;

	return newNode;
}	

int Stratagem::UCTForUltimate::UCTSearch(){
	node* curNode = NULL;
	double result = 0;
	int simTime = 0;
	int position = 0;

	//search position of the node
	// if root hasn't been initialized
	if(this->root == NULL){
		char* newBoard = new char[boardSize];
		char* newEndBlocks = new char[blockNum];
		char* board = this->uttt->getboard();
		char* endBlocks = this->uttt->getEndBlocks();

		for(int i = 0; i < boardSize; i++){
			newBoard[i] = board[i];
		}
		for(int i = 0; i < blockNum; i++){
			newEndBlocks[i] = endBlocks[i];
		}

		this->root = new node(newBoard, 0, false, newEndBlocks, this->uttt->getNextBlock(), this->uttt->getLastBlock());
	}

	//if children of root have not been expanded
	else if(this->root->children == NULL){
		char* newBoard = new char[this->boardSize];
		char* newEndBlocks = new char[this->blockNum];
		char* board = this->uttt->getboard();
		char* endBlocks = this->uttt->getEndBlocks();
		for(int i = 0; i < this->boardSize; i++)
			newBoard[i] = board[i];
		for(int i = 0; i < this->blockNum; i++)
			newEndBlocks[i] = endBlocks[i];

		delete this->root;
		this->root = new node(newBoard, 0, false, newEndBlocks, this->uttt->getNextBlock(), this->uttt->getLastBlock());
	}

	//children exist
	else{
		node* tempNode = NULL;
		for(int i = 0; i < this->root->childrenNum; i++){
			if(this->root->children[i]->takePosNum == this->uttt->getNextBlock() && this->root->children[i]->takeBlockNum == this->uttt->getLastBlock())
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
	position = this->uttt->getPosition(curNode->board, this->root->board) + 1;
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