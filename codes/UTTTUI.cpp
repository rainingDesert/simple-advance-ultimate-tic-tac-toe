#include "TTT.h"
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

UTTTUI::UTTTUI(Game* game):TTTUI(game){
	this->uttt = (UltimateTTT*)(game);
}

//display board
void UTTTUI::displayBoard(){
	int row = this->uttt->getRow();
	int blockRow = this->uttt->getPerBlockRow();
	int dec = ceil(log10(row * row + 1));

	//for each row
	for(int i = 0; i < row; i++){
		if(i != 0 && i % blockRow == 0){
			for(int j = 0; j < (dec + 3) * row + row / blockRow; j++){
				cerr << "-";
			}
			cerr << endl;
		}

		//for each column
		for(int j = 0; j < row; j++){
			//for each block
			if(j != 0 && j % blockRow == 0){
				cerr << "|";
			}

			cerr << "|";
			int position = i * row + j;
			if(this->uttt->getboard()[position] == '\0')
				cerr << setw(dec + 2) << (i % 3) * blockRow + (j % 3) + 1 ;
			else
				cerr << setw(dec + 2) << this->uttt->getboard()[position];
		}
		cerr << "|" << endl;
	}

	cerr << endl << "------------------General Board------------------" << endl;

	dec = ceil(log10(blockRow * blockRow + 1));
	cerr.flags(ios::internal);
	for(int i = 0; i < blockRow; i++){
		cerr << '|';
		for(int j = 0; j < blockRow; j++){
			if(this->uttt->getEndBlocks()[i * blockRow + j] == '\0'){
				cerr << setw(dec + 2) << i * blockRow + j + 1 << '|';
			}
			else{
				cerr << setw(dec + 2) << this->uttt->getEndBlocks()[i * blockRow + j] << '|';
			}
		}
		cerr << endl;
	}
}

//user decides a position to mark
void UTTTUI::userTurn(){
	//set user's mark
	int perRow = this->uttt->getPerBlockRow();
	char userMark = this->uttt->getUserMark();

	if(userMark == '\0'){
		this->initInput();
	}

	//choose a place to mark
	else{
		int blockNum = this->uttt->getBlockNum();
		int block = 0;
		int position = 0;
		while(true){
			if(this->uttt->getNextBlock() == -1){
				cerr << "It's your turn, human, please input an usable block among [1, " << blockNum << "] at first: ";
				cin >> block;
				if(block < 1 || block > blockNum){
					cerr << "Wrong block number" << endl;
				}
				else if(this->uttt->blockUseful(--block) != '\0'){
					cerr << "Such block is full" << endl;
				}
				else{
					break;
				}
			}
			else{
				block = this->uttt->getNextBlock();
				break;
			}
		}
		while(true){
			cerr << "Input a position in block " << block + 1 << " among [1, " << perRow * perRow <<"]:";
			cin >> position;
			position -= 1;
			int index = (block % perRow) * perRow  + int(block / perRow) * perRow * this->uttt->getRow() + position % perRow + int(position / perRow) * this->uttt->getRow();
			if(position < 0 || position >= perRow * perRow){
				cerr << "Wrong position number" << endl;
			}
			else if(this->uttt->getboard()[index] != '\0'){
				cerr << "Such position has been occupied" << endl;
			}
			else{
				this->uttt->getboard()[index] = userMark;
				break;
			}
		}
		(this->uttt->getEndBlocks())[block] = (this->uttt->updateBlock(this->uttt->getEndBlocks(), this->uttt->getboard(), block, this->uttt->getUserMark()))[block];
		if(this->uttt->blockUseful(position) != '\0'){
			this->uttt->setTakeBlock(-1);
		}
		else{
			this->uttt->setTakeBlock(position);
		}
		this->uttt->setLastBlock(block);
	}

	this->displayBoard();
	cerr << endl;
}

//computer decides a position to mark
void UTTTUI::compTurn(int position){

	position -= 1;
	int row = int(position / this->uttt->getRow());
	int column = position % this->uttt->getRow();
	int perRow = this->uttt->getPerBlockRow();
	int block = int(row / perRow) * perRow + column / perRow;
	int pos = (row % perRow) * perRow + column % perRow;

	cerr << "Super Computer occpuy position in block " << block + 1 << " with position " << pos + 1 << endl;
	cout << block + 1 << " " << pos + 1 << endl;
	this->uttt->getboard()[position] = this->uttt->getCompMark();
	(this->uttt->getEndBlocks())[block] = (this->uttt->updateBlock(this->uttt->getEndBlocks(), this->uttt->getboard(), block, this->uttt->getCompMark()))[block];
	if(this->uttt->blockUseful(pos) != '\0'){
		this->uttt->setTakeBlock(-1);
	}
	else{
		this->uttt->setTakeBlock(pos);
	}
	this->uttt->setLastBlock(block);
	this->displayBoard();
	cerr << endl;
}

//assign position and mark for advance TTT
void UTTTUI::assignTurn(int position, char mark){
	position -= 1;
	int row = int(position / this->uttt->getRow());
	int column = position % this->uttt->getRow();
	int perRow = this->uttt->getPerBlockRow();
	int block = int(row / perRow) * perRow + column / perRow;
	int pos = (row % perRow) * perRow + column % perRow;

	cerr << "Super Computer occpuy position in block " << block + 1 << " with position " << pos + 1 << endl;
	cout << block + 1 << " " << pos + 1 << endl;
	this->uttt->getboard()[position] = mark;
	(this->uttt->getEndBlocks())[block] = (this->uttt->updateBlock(this->uttt->getEndBlocks(), this->uttt->getboard(), block, mark))[block];
	if(this->uttt->blockUseful(pos) != '\0'){
		this->uttt->setTakeBlock(-1);
	}
	else{
		this->uttt->setTakeBlock(pos);
	}
	this->uttt->setLastBlock(block);
	this->displayBoard();
	cerr << endl;
}