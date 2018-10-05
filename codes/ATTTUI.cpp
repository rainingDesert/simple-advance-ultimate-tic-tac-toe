#include "TTT.h"
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

ATTTUI::ATTTUI(Game* game):TTTUI(game){
	this->attt = (AdvanceTTT*)(game);
}

//display board
void ATTTUI::displayBoard(){
	int row = this->attt->getRow();
	int blockRow = this->attt->getPerBlockRow();
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
			if(this->game->getboard()[position] == '\0')
				cerr << setw(dec + 2) << (i % 3) * blockRow + (j % 3) + 1 ;
			else
				cerr << setw(dec + 2) << this->game->getboard()[position];
		}
		cerr << "|" << endl;
	}
}

//user decides a position to mark
void ATTTUI::userTurn(){
	//set user's mark
	int perRow = this->attt->getPerBlockRow();
	char userMark = this->attt->getUserMark();

	if(userMark == '\0'){
		this->initInput();
	}

	//choose a place to mark
	else{
		int blockNum = this->attt->getBlockNum();
		int block = 0;
		int position = 0;
		while(true){
			if(this->attt->getNextBlock() == -1){
				cerr << "It's your turn, human, please input an usable block among [1, " << blockNum << "] at first: ";
				cin >> block;
				if(block < 1 || block > blockNum){
					cerr << "Wrong block number" << endl;
				}
				else if(this->attt->blockUseful(--block) != '\0'){
					cerr << "Such block is full" << endl;
				}
				else{
					break;
				}
			}
			else{
				block = this->attt->getNextBlock();
				break;
			}
		}
		while(true){
			cerr << "Input a position in block " << block + 1 << " among [1, " << perRow * perRow <<"]:";
			cin >> position;
			position -= 1;
			int index = (block % perRow) * perRow  + int(block / perRow) * perRow * this->attt->getRow() + position % perRow + int(position / perRow) * this->attt->getRow();
			if(position < 0 || position >= perRow * perRow){
				cerr << "Wrong position number" << endl;
			}
			else if(this->attt->getboard()[index] != '\0'){
				cerr << "Such position has been occupied" << endl;
			}
			else{
				this->attt->getboard()[index] = userMark;
				break;
			}
		}
		(this->attt->getEndBlocks())[block] = (this->attt->updateBlock(this->attt->getEndBlocks(), this->attt->getboard(), block))[block];
		if(this->attt->blockUseful(position) != '\0'){
			this->attt->setTakeBlock(-1);
		}
		else{
			this->attt->setTakeBlock(position);
		}
		this->attt->setLastBlock(block);
	}

	this->displayBoard();
	cerr << endl;
}

//computer decides a position to mark
void ATTTUI::compTurn(int position){

	position -= 1;
	int row = int(position / this->attt->getRow());
	int column = position % this->attt->getRow();
	int perRow = this->attt->getPerBlockRow();
	int block = int(row / perRow) * perRow + column / perRow;
	int pos = (row % perRow) * perRow + column % perRow;

	cerr << "Super Computer occpuy position in block " << block + 1 << " with position " << pos + 1 << endl;
	cout << block + 1 << " " << pos + 1 << endl;
	this->attt->getboard()[position] = this->attt->getCompMark();
	(this->attt->getEndBlocks())[block] = (this->attt->updateBlock(this->attt->getEndBlocks(), this->attt->getboard(), block))[block];
	if(this->attt->blockUseful(pos) != '\0'){
		this->attt->setTakeBlock(-1);
	}
	else{
		this->attt->setTakeBlock(pos);
	}
	this->attt->setLastBlock(block);
	this->displayBoard();
	cerr << endl;
}

//assign position and mark for advance TTT
void ATTTUI::assignTurn(int position, char mark){
	position -= 1;
	int row = int(position / this->attt->getRow());
	int column = position % this->attt->getRow();
	int perRow = this->attt->getPerBlockRow();
	int block = int(row / perRow) * perRow + column / perRow;
	int pos = (row % perRow) * perRow + column % perRow;

	cerr << "Super Computer occpuy position in block " << block + 1 << " with position " << pos + 1 << endl;
	cout << block + 1 << " " << pos + 1 << endl; 
	this->attt->getboard()[position] = mark;
	(this->attt->getEndBlocks())[block] = (this->attt->updateBlock(this->attt->getEndBlocks(), this->attt->getboard(), block))[block];
	if(this->attt->blockUseful(pos) != '\0'){
		this->attt->setTakeBlock(-1);
	}
	else{
		this->attt->setTakeBlock(pos);
	}
	this->attt->setLastBlock(block);
	this->displayBoard();
	cerr << endl;
}