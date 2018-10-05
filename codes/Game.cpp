#include "TTT.h"
#include <iostream>
using namespace std;

//initialize game object
Game::Game(double win, double loss, double draw, double noResult, int row){
	this->win = win;
	this->loss = loss;
	this->draw = draw;
	this->noResult = noResult;
	this->row = row;
	this->userMark = '\0';
	this->compMark = '\0';
}

char* Game::getboard(){cerr<<"call child please"<<endl; return NULL;}

int Game::getPosition(char* board1, char* board2){cerr<<"call child please"<<endl; return -1;}

double Game::gameOverTTT(char* board, char mark){cerr<<"call child please"<<endl; return -1;}

char** Game::getNextBoards(char * board, char mark){cerr<<"call child please"<<endl; return NULL;};

//get result
bool Game::result(double goal){
	if(goal == this->win){
		return true;
	}
	if(goal == this->loss){
		return true;
	}
	if(goal == this->draw){
		return true;
	}
	return false;
}

//get user's mark
char Game::getUserMark(){
	return this->userMark;
}

//get computers's mark
char Game::getCompMark(){
	return this->compMark;
}

//get win value
int Game::getResult(double result){
	if(result == this->win){
		return 1;
	}
	if(result == this->draw){
		return 0;
	}
	if(result == this->loss){
		return -1;
	}
	return -2;
}

//get row
int Game::getRow(){
	return this->row;
}

//set marks
void Game::setMark(char userMark, char compMark){
	this->userMark = userMark;
	this->compMark = compMark;
}

//change marks
void Game::changeMark(){
	char temp = this->userMark;
	this->userMark = this->compMark;
	this->compMark = temp;
}