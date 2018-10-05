#include "TTT.h"
#include <iostream>
#include <time.h>
using namespace std;

//initial Imp
Imp::Imp(char statType, char playType, double win, double loss, double draw, double noResult, int limit, double UCTConstant){
	if(statType == 'a')
		this->limitDepth = limit;
	else if(statType == 'u'){
		this->limitSim = limit;
		this->UCTConstant = UCTConstant;
	}
	this->statType = statType;
	this->playType = playType;
	this->game = this->getGame(win, loss, draw, noResult);
	this->tttui = this->getUI();
	this->tttui->userTurn();
	this->stat = new Stratagem();
	// this->game->setMark('o', 'x');
}



//destructor
Imp::~Imp(){
	if(this->game != NULL){
		delete this->game;
		this->game = NULL;
	}
	if(this->tttui != NULL){
		delete this->tttui;
		this->tttui = NULL;
	}
	if(this->statType == 'u'){
		this->stat->deleteUCT();
	}
}

//begin 3x3 tic-tac-toe
Game* Imp::simpleTTT(double win, double loss, double draw, double noResult){
	return (new SimpleTTT(win, loss, draw, noResult));
}

//begin 3x(3x3) tic-tac-tie
Game* Imp::advanceTTT(double win, double loss, double draw, double noResult){
	return (new AdvanceTTT(win, loss, draw, noResult));
}

//begin ultimate tic-tac-toe
Game* Imp::ultimateTTT(double win, double loss, double draw, double noResult){
	return (new UltimateTTT(win, loss, draw, noResult));
}

//get game pointer
Game* Imp::getGame(double win, double loss, double draw, double noResult){
	switch(this->playType){
		case 's': return this->simpleTTT(win, loss, draw, noResult);
		case 'a': return this->advanceTTT(win, loss, draw, noResult);
		case 'u': return this->ultimateTTT(win, loss, draw, noResult);
		default: cerr << "Error" << endl; return NULL;
	}
}

//get tttui
TTTUI* Imp::getUI(){
	switch(this->playType){
		case 's': return (new STTTUI(this->game));
		case 'a': return (new ATTTUI(this->game));
		case 'u': return (new UTTTUI(this->game));
		default: cerr << "Error" << endl; return NULL;
	}
}

//get result
double Imp::getResult(){
	switch(this->playType){
		case 's': return this->game->gameOverTTT(this->game->getboard(), this->game->getUserMark());
		case 'a': return ((AdvanceTTT*)(this->game))->gameOverTTT(this->game->getboard(), ((AdvanceTTT*)(this->game))->getEndBlocks(), ((AdvanceTTT*)(this->game))->getLastBlock(), this->game->getUserMark());
		case 'u': return ((UltimateTTT*)(this->game))->gameOverTTT(((UltimateTTT*)(this->game))->getEndBlocks(), this->game->getUserMark());
		default: cerr << "Error" << endl; return 0;
	}
}

//get position
int Imp::getPosition(){
	if(this->statType == 'a'){
		switch(this->playType){
			case 's': return this->stat->alphaBetaSearch(this->game);
			case 'a': return this->stat->hAlphaBetaAdvanceSearch(this->game, this->limitDepth);
			case 'u': return this->stat->hAlphaBetaUltimateSearch(this->game, this->limitDepth);
			default: cerr << "Error" << endl; return 0;
		}
	}
	else if(this->statType == 'u'){
		switch(this->playType){
			case 'a': return this->stat->UCTAdvancedSearch(this->game, this->UCTConstant, this->limitSim);
			case 'u': return this->stat->UCTUltimateSearch(this->game, this->UCTConstant, this->limitSim);
			default: cerr << "Error" << endl; return 0;
		}
	}
	cerr << "error statagem type" << endl;
	return 0;
}

//execute the game
void Imp::execution(){
	bool user = true;
	double result = this->getResult();

	if(this->game->getCompMark() == 'x')
		user = false;
	while(!this->game->result(result)){
		if(user){
			this->tttui->userTurn();
			user = !user;
		}
		else{
			cerr << "I am thinking..." << endl;

			clock_t start, end;
			int position = 0;
			start = clock();
			position = this->getPosition();
			end = clock();
			
			this->tttui->compTurn(position);
			cerr << "ps. I took " << (double)(end - start) / CLOCKS_PER_SEC << " seconds to think" << endl << endl;
			user = !user;
		}
		result = this->getResult();
	}
	this->tttui->printResult(this->game->getResult(result));
}