#include "TTT.h"
#include <iostream>
#include <math.h>
#include <time.h>
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
Stratagem::UCT::UCT(Game* game, int blockNum, double c, int limitSim){
	this->game = game;
	this->boardSize = game->getRow() * game->getRow();
	this->blockNum = blockNum;
	this->c = c;

	if(limitSim < 1){
		this->limitSim = 100;
	}
	else
		this->limitSim = limitSim;
}

//destructor
Stratagem::UCT::~UCT(){
	if(this->root != NULL){
		this->deleteNode(this->root);
		this->root = NULL;
	}
}

//delete nodes
void Stratagem::UCT::deleteNode(node* curNode){
	if(curNode->children == NULL){
		delete curNode;
		curNode = NULL;
		return;
	}

	for(int i = 0; i < curNode->childrenNum; i++){
		this->deleteNode(curNode->children[i]);
	}
	delete[] curNode->children;
	curNode->children = NULL;
	delete curNode;
	curNode = NULL;
	return;
}

//level up nodes
void Stratagem::UCT::descendNode(node* curNode){
	if(curNode->children == NULL){
		curNode->depth -= 1;
		return;
	}

	for(int i = 0; i < curNode->childrenNum; i++){
		this->descendNode(curNode->children[i]);
	}
	curNode->depth -= 1;
	return;
}

//detect whether node has been expanded totally
bool Stratagem::UCT::whetherExpand(node* curNode){
	if(curNode->children == NULL)
		return false;
	if(curNode == this->root && curNode->totalTurn < curNode->childrenNum)
		return false;
	if(curNode != this->root && (curNode->totalTurn - 1) < curNode->childrenNum)
		return false;
	return true;
}

//select nodes to be expanded
Stratagem::UCT::node* Stratagem::UCT::selection(node* curNode){
	node* newNode = curNode;
	while(newNode->childrenNum != -1){	//while non terminal and within depth
		
		//have not been totally expanded
		if(!this->whetherExpand(newNode))
			return this->expand(newNode);

		//resturn best child
		newNode = this->bestChild(newNode);
	}

	return newNode;
}

//expand current node to select a child for rollup
Stratagem::UCT::node* Stratagem::UCT::expand(node* curNode){

	//have been totally expanded
	if(this->whetherExpand(curNode)){	
		cerr << "Error: have been expanded" << endl;
		return NULL;
	}
	if(curNode->children == NULL){
		this->getChildren(curNode);
	}
	if(curNode == this->root)
		return curNode->children[curNode->totalTurn];
	else
		return curNode->children[curNode->totalTurn - 1];
}

//return the best child
Stratagem::UCT::node* Stratagem::UCT::bestChild(node* curNode){

	//current node have not been totally expanded
	if(!this->whetherExpand(curNode)){	
		cerr << "Error: have not been expanded totally" << endl;
		return NULL;
	}
	node* bestNode = NULL;
	double bestScore = -10000;
	for(int i = 0; i < curNode->childrenNum; i++){
		double newScore = this->calScore(curNode->children[i]);
		if(newScore > bestScore){
			bestNode = curNode->children[i];
			bestScore = newScore;
		}
	}

	return bestNode;
}

//simulation randomly
double Stratagem::UCT::simulation(node* curNode){
	node* simNode = curNode;
	double result = 0;
	while(simNode->childrenNum != -1){	//non terminal

		node* tempNode = this->simChildren(simNode);	//get children

		if(simNode != curNode){
			this->deleteNode(simNode);
		}
		simNode = tempNode;
	}

	result = simNode->leafResult;
	if(simNode != curNode){
		this->deleteNode(simNode);
	}
	simNode = NULL;
	return result;
}

//back up to update parents' scores
void Stratagem::UCT::backup(node* curNode, double result){
	node* newNode = curNode;
	while(newNode != NULL){		//previous is not root
		newNode->totalTurn += 1;
		newNode->score += result;
		newNode = newNode->parent;
	}
}

//get result
double Stratagem::UCT::getResult(node* curNode){
	cerr << "You should over write" << endl;
	return 0;	
}

//get children
void Stratagem::UCT::getChildren(node* curNode){
	cerr << "You should over write" << endl;
}

//get children during simulation
Stratagem::UCT::node* Stratagem::UCT::simChildren(node* curNode){
	cerr << "You should over write" << endl;
	return NULL;
}

//calculate score
double Stratagem::UCT::calScore(node* curNode){

	double value = 0;
	if(!curNode->parent->userTurn)
		value = (double(curNode->score) / curNode->totalTurn) + double(this->c) * sqrt(2.0 * log(curNode->parent->totalTurn) / curNode->totalTurn);
	else
		value = (- double(curNode->score) / curNode->totalTurn) + double(this->c) * sqrt(2.0 * log(curNode->parent->totalTurn) / curNode->totalTurn);

	return value;
}

///////////////////-----------function to be called from outside----------//////////////////////////////
//do UCT search
int Stratagem::UCT::UCTSearch(){
	cerr << "You should over write" << endl;
	return 0;
}
