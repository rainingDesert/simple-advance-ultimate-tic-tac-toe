#include "TTT.h"
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

//initialize board and marks
TTTUI::TTTUI(Game* game){
	this->game = game;
}

//destructor
TTTUI::~TTTUI(){}

//display board for TTT
void TTTUI::displayBoard(){
	cerr << "call child please" << endl;
	return;
}

//initial input
void TTTUI::initInput(){
	char userMark, compMark;
	char mark = '\0';
	cerr << "----------- Game start -----------" << endl;
	while(true){
		cerr << "Please select your mark (x or o)(x will go first): ";
		cin >> mark;
		if(mark == 'x' || mark == 'X'){
			userMark = 'x';
			compMark = 'o';
			break;
		}
		if(mark == 'o' || mark == 'O'){
			userMark = 'o';
			compMark = 'x';
			break;
		}
		cerr << "Wrong input, please select again." << endl;
	}
	this->game->setMark(userMark, compMark);	
}

//read the input of user
void TTTUI::userTurn(){
	//set user's mark
	char userMark = this->game->getUserMark();

	if(userMark == '\0'){
		this->initInput();
	}

	//choose a place to mark
	else{
		int position = 0;
		while(true){
			cerr << "It's your turn, human, please input an empty position among [1, " << this->game->getRow() * this->game->getRow() << "]: ";
			cin >> position;
			if(position < 1 || position > this->game->getRow() * this->game->getRow()){
				cerr << "Wrong position, please input again" << endl;
			}
			else if(this->game->getboard()[position - 1] != '\0'){
				cerr << "The position has been occupied, please input again" << endl;
			}
			else{
				this->game->getboard()[position - 1] = userMark;
				break;
			}
		}
	}

	this->displayBoard();
	cerr << endl;
}

//get the input of computer
void TTTUI::compTurn(int position){
	cerr << "Super Computer occpuy position " << position << endl;
	cout << position << endl;
	this->game->getboard()[position - 1] = this->game->getCompMark();
	this->displayBoard();
	cerr << endl;
}

//assign position and mark
void TTTUI::assignTurn(int position, char mark){}

//get result
void TTTUI::printResult(int goal){
	if(goal == 1){
		cerr << "oh, human, you win" << endl;
	}
	if(goal == -1){
		cerr << "Super Computer will always be super" << endl;
	}
	if(goal == 0){
		cerr << "this is your best action, I just know it hahahaha" << endl;
	}
}

//get board of Simple TTT
void STTTUI::displayBoard(){
	int row = this->game->getRow();
	int dec = ceil(log10(row * row + 1));
	cerr.flags(ios::internal);
	for(int i = 0; i < row; i++){
		cerr << '|';
		for(int j = 0; j < row; j++){
			if(this->game->getboard()[i * row + j] == '\0'){
				cerr << setw(dec + 2) << i * row + j + 1 << '|';
			}
			else{
				cerr << setw(dec + 2) << this->game->getboard()[i * row + j] << '|';
			}
		}
		cerr << endl;
	}
}

//instructor
STTTUI::STTTUI(Game* game):TTTUI(game){}