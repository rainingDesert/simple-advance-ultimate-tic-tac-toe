#include "TTT.h"
#include <iostream>
using namespace std;

//detect whether game over for 3x3 tic-tac-toe
double SimpleTTT::gameOverTTT(char* board, char mark){
	//diagonal
	if(board[0] == board[4] && board[0] == board[8]){
		if(board[0] == mark)
			return this->win;
		else if(board[0] != '\0')
			return this->loss;
	}
	if(board[2] == board[4] && board[2] == board[6]){
		if(board[2] == mark)
			return this->win;
		else if(board[2] != '\0')
			return this->loss;
	}

	for(int j = 0; j < 3; j++){
		//rows
		if(board[j * 3] == board[j * 3 + 1] && board[j * 3] == board[j * 3 + 2]){
			if(board[j * 3] == mark)
				return this->win;
			else if(board[j * 3] != '\0')
				return this->loss;
		}

		//columns
		if(board[j] == board[j + 3] && board[j] == board[j + 6]){
			if(board[j] == mark)
				return this->win;
			else if(board[j] != '\0')
				return this->loss;
		}
	}

	//draw
	int i = 0;
	while(i < 9){
		if(board[i] == '\0')
			break;
		i += 1;
	}
	if(i == 9)
		return this->draw;
	return this->noResult;
}

//intrustor for 3x3 TTT
SimpleTTT::SimpleTTT(double win, double loss, double draw, double noResult) : Game(win, loss, draw, noResult, 3){
	this->board = new char[3 * 3];
	for(int i = 0; i < 3 * 3; i++){
		this->board[i] = '\0';
	}
}

//destructor
SimpleTTT::~SimpleTTT(){
	if(this->board != NULL){
		delete[] this->board;
		this->board = NULL;
	}
}

//get position
int SimpleTTT::getPosition(char* board1, char* board2){
	int position = 0;
	for(; position < this->row * this->row; position++){
		if(board1[position] != board2[position])
			return position;
	}
	cerr << "wrong input" << endl;
	return -1;
}

//get board
char* SimpleTTT::getboard(){
	return this->board;
}

//get next boards
char** SimpleTTT::getNextBoards(char* board, char mark){
	int boardSize = this->row * this->row;
	char** nextBoards = new char*[boardSize];
	for(int i = 0; i < boardSize; i++){
		if(board[i] == '\0'){
			nextBoards[i] = new char[boardSize];
			for(int j = 0; j < boardSize; j++)
				nextBoards[i][j] = board[j];
			nextBoards[i][i] = mark;
		}
		else
			nextBoards[i] = NULL;
	}
	return nextBoards;
}
