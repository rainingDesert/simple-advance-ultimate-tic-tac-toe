#include "TTT.h"
#include <iostream>
#include <math.h>
using namespace std;

//test
void getBoard(char* board){

	int i = 0;
	int start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 0 || j == 5 || j == 6 || j == 7){
			board[pos] = 'o';
		}
		else if(j != 8)
			board[pos] = 'x';
	}

	i = 8;
	start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 5 || j == 6 || j == 7){
			board[pos] = 'o';
		}
		else if(j != 0)
			board[pos] = 'x';
	}

	i = 1;
	start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 0 || j == 5 || j == 6 || j == 7){
			board[pos] = 'o';
		}
		else if(j != 2)
			board[pos] = 'x';
	}

	i = 2;
	start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 5 || j == 6 || j == 7){
			board[pos] = 'o';
		}
		else if(j != 0)
			board[pos] = 'x';
	}

	i = 3;
	start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 0 || j == 5 || j == 6 || j == 7){
			board[pos] = 'o';
		}
		else if(j != 4)
			board[pos] = 'x';
	}

	i = 4;
	start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 0 || j == 6 || j == 7){
			board[pos] = 'o';
		}
		else if(j != 5)
			board[pos] = 'x';
	}

	i = 5;
	start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 0 || j == 5 || j == 6 || j == 7){
			board[pos] = 'o';
		}
		else if(j != 1)
			board[pos] = 'x';
	}

	i = 6;
	start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 0 || j == 5 || j == 6 || j == 7){
			board[pos] = 'o';
		}
		else if(j != 1)
			board[pos] = 'x';
	}

	i = 7;
	start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 0 || j == 5 || j == 6 || j == 7){
			board[pos] = 'o';
		}
		else if(j != 1)
			board[pos] = 'x';
	}

}

void getBoard2(char* board){
	board[4] = board[13] = board[20] = board[24] = board[29] = board[34] = board[43] = board[47] = board[50] = board[52] = board[57] = board[67] = board[69] = board[72] = board[77] = 'o';
	board[1] = board[17] = board[22] = board[23] = board[28] = board[39] = board[40] = board[49] = board[56] = board[60] = board[65] = board[66] = board[78] = board[79] = 'x';
}

void getBoard3(char* board){

	int i = 0;
	int start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 0 ||j == 6 || j == 7){
			board[pos] = 'o';
		}
		else if(j == 3 || j == 4 || j == 5)
			board[pos] = 'x';
	}

	i = 1;
	start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 1 || j == 5 || j == 6){
			board[pos] = 'o';
		}
		else if(j == 2 || j == 3 || j == 7)
			board[pos] = 'x';
	}

	i = 2;
	start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 0 || j == 3 || j == 6){
			board[pos] = 'o';
		}
		else if(j == 8)
			board[pos] = 'x';
	}

	i = 3;
	start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 0 || j == 1 || j == 5 || j == 8){
			board[pos] = 'o';
		}
		else if(j == 2 || j == 4)
			board[pos] = 'x';
	}

	i = 4;
	start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 2 || j == 5 || j == 8){
			board[pos] = 'o';
		}
		else if(j == 4)
			board[pos] = 'x';
	}

	i = 5;
	start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 1 || j == 6){
			board[pos] = 'o';
		}
		else if(j == 3 || j == 4 || j == 5)
			board[pos] = 'x';
	}

	i = 6;
	start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 0 || j == 1 || j == 2)
			board[pos] = 'x';
	}

	i = 7;
	start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 8 || j == 6 || j == 7){
			board[pos] = 'o';
		}
		else if(j == 0 || j == 4 || j == 5)
			board[pos] = 'x';
	}

	i = 8;
	start = (i % 3) * 3 + int(i / 3) * 3 * 9;
	for(int j = 0; j < 9; j++){
		int pos = start + j % 3 + int(j / 3) * 9;
		if(j == 8){
			board[pos] = 'o';
		}
		else if(j == 0 || j == 3 || j == 6)
			board[pos] = 'x';
	}

}

void minBoard(char* endBlocks){
	for(int i = 0; i <8; i++){
		endBlocks[i] = '-';
	}
}

void minBoard2(char* endBlocks){
	// endBlocks[0] = 'x';
	// endBlocks[2] = 'o';
	// endBlocks[4] = 'o';
	// endBlocks[5] = 'x';
	// endBlocks[6] = 'x';
	// endBlocks[7] = 'o';
	// endBlocks[8] = 'x';
	endBlocks[5] = 'o';
	endBlocks[7] = 'o';
}

//instructor
AdvanceTTT::AdvanceTTT(double win, double loss, double draw, double noResult):Game(win, loss, draw, noResult, 9){
	this->board = new char[9 * 9];
	for(int i = 0; i < 9 * 9; i++){
		this->board[i] = '\0';
	}
	// getBoard2(this->board);
	this->takePosNum = -1;
	this->blockNum = 9;
	this->perBlockRow = 3;
	this->endBlocks = new char[this->blockNum];
	this->dangerBlocks = new char[this->blockNum];
	for(int i = 0; i < this->blockNum; i++){
		this->endBlocks[i] = '\0';
		this->dangerBlocks[i] = '\0';
	}
	// minBoard2(this->endBlocks);
}

//destructor
AdvanceTTT::~AdvanceTTT(){
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
}

//update blocks
char* AdvanceTTT::updateBlock(char* endBlocks, char* board, int block){

	char* newBlocks = new char[this->blockNum];
	for(int i = 0; i < this->blockNum; i++){
		newBlocks[i] = endBlocks[i];
	}

	if(block < 0 || block >= this->blockNum){
		cerr << "wrong block number" << endl;
		return NULL;
	}
	if(newBlocks[block] != '\0'){
		cerr << "block has already end" << endl;
		return NULL;
	}
	int i = 0;
	int blockPerRow = int(sqrt(this->blockNum));
	int start = (block % blockPerRow) * this->perBlockRow + int(block / blockPerRow) * this->perBlockRow * this->row;

	//not end
	for(; i < this->perBlockRow * this->perBlockRow; i++){
		int position = start + (i % 3) + int(i / 3) * this->row;
		if(board[position] == '\0'){
			return newBlocks;
		}
	}

	newBlocks[block] = '-';
	endBlocks = NULL;
	return newBlocks;
}

//update dangerous block
char* AdvanceTTT::updateDangerBlock(char* dangerBlocks, char* board, int block){
	int userCount = 0;
	int compCount = 0;
	int blockPerRow = int(sqrt(this->blockNum));
	int start = (block % blockPerRow) * this->perBlockRow + int(block / blockPerRow) * this->perBlockRow * this->row;
	char* newDangerBlocks = new char[this->blockNum];
	for(int i = 0; i < this->blockNum; i++)
		newDangerBlocks[i] = dangerBlocks[i];
	newDangerBlocks[block] = '\0';

	//for rows and columns
	for(int i = 0; i < this->perBlockRow; i++){
		//for rows
		userCount = 0;
		compCount = 0;
		for(int column = 0; column < this->perBlockRow; column++){
			if(board[start + column + i * this->row] == this->userMark)
				userCount += 1;
			else if(board[start + column + i * this->row] == this->compMark)
				compCount += 1;
		}
		if(userCount * compCount == 0){
			if(userCount == 2){
				if(newDangerBlocks[block] == this->compMark)
					newDangerBlocks[block] = 'b';
				else if(newDangerBlocks[block] == '\0')
					newDangerBlocks[block] = this->userMark;
			}
			else if(compCount == 2){
				if(newDangerBlocks[block] == this->userMark)
					newDangerBlocks[block] = 'b';
				else if(newDangerBlocks[block] == '\0')
					newDangerBlocks[block] = this->compMark;
			}
		}

		//for columns
		userCount = 0;
		compCount = 0;
		for(int row = 0; row < this->perBlockRow; row++){
			if(board[start + i + row * this->row] == this->userMark)
				userCount += 1;
			else if(board[start + i + row * this->row] == this->compMark)
				compCount += 1;
		}
		if(userCount * compCount == 0){
			if(userCount == 2){
				if(newDangerBlocks[block] == this->compMark)
					newDangerBlocks[block] = 'b';
				else if(newDangerBlocks[block] == '\0')
					newDangerBlocks[block] = this->userMark;
			}
			else if(compCount == 2){
				if(newDangerBlocks[block] == this->userMark)
					newDangerBlocks[block] = 'b';
				else if(newDangerBlocks[block] == '\0')
					newDangerBlocks[block] = this->compMark;
			}
		}
	}

	//for diagnosis
	userCount = 0;
	compCount = 0;
	for(int row = 0; row < this->perBlockRow; row++){
		if(board[start + row * (1 + this->row)] == this->userMark)
			userCount += 1;
		else if(board[start + row * (1 + this->row)] == this->compMark)
			compCount += 1;
	}

	if(userCount * compCount == 0){
		if(userCount == 2){
			if(newDangerBlocks[block] == this->compMark)
				newDangerBlocks[block] = 'b';
			else if(newDangerBlocks[block] == '\0')
				newDangerBlocks[block] = this->userMark;
		}
		else if(compCount == 2){
			if(newDangerBlocks[block] == this->userMark)
				newDangerBlocks[block] = 'b';
			else if(newDangerBlocks[block] == '\0')
				newDangerBlocks[block] = this->compMark;
		}
	}

	//for another diagnosis
	userCount = 0;
	compCount = 0;
	for(int row = 0; row < this->perBlockRow; row++){
		if(board[start + this->perBlockRow - 1 + row * (this->row - 1)] == this->userMark)
			userCount += 1;
		else if(board[start + this->perBlockRow - 1 + row * (this->row - 1)] == this->compMark)
			compCount += 1;
	}

	if(userCount * compCount == 0){
		if(userCount == 2){
			if(newDangerBlocks[block] == this->compMark)
				newDangerBlocks[block] = 'b';
			else if(newDangerBlocks[block] == '\0')
				newDangerBlocks[block] = this->userMark;
		}
		else if(compCount == 2){
			if(newDangerBlocks[block] == this->userMark)
				newDangerBlocks[block] = 'b';
			else if(newDangerBlocks[block] == '\0')
				newDangerBlocks[block] = this->compMark;
		}
	}

	//detect draw
	if(newDangerBlocks[block] == '\0'){
		for(int row = 0; row < this->perBlockRow; row++){
			for(int column = 0; column < this->perBlockRow; column++){
				if(board[start + column + row * this->row] == '\0'){
					return newDangerBlocks;
				}
			}
		}
		newDangerBlocks[block] = '-';
	}

	return newDangerBlocks;
}

char** AdvanceTTT::getNextBoards(char * board, char mark){cerr << "no use here" << endl; return NULL;}

double AdvanceTTT::gameOverTTT(char * board, char mark){cerr << "no use here" << endl; return -1;}

//detect whether game over for 3x(3x3) tic-tac-toe
double AdvanceTTT::gameOverTTT(char* board, char* endBlocks, int block, char mark){
	int i = 0;
	int blockPerRow = int(sqrt(this->blockNum));
	int start = (block % blockPerRow) * this->perBlockRow + int(block / blockPerRow) * this->perBlockRow * this->row;

	//for each row and column
	for(; i < this->perBlockRow; i++){
		int subStart = start + i * this->row;
		//for rows
		if(board[subStart] == board[subStart + 1] && board[subStart] == board[subStart + 2]){
			if(board[subStart] == mark)
				return this->win;
			else if(board[subStart] != '\0')
				return this->loss;
		}

		//for columns
		subStart = start + i;
		if(board[subStart] == board[subStart + this->row] && board[subStart] == board[subStart + 2 * this->row]){
			if(board[subStart] == mark)
				return this->win;
			else if(board[subStart] != '\0')
				return this->loss;
		}
	}

	//for each diagnosis
	if(board[start] == board[start + this->row + 1] && board[start] == board[start + 2 * this->row + 2]){
		if(board[start] == mark)
			return this->win;
		else if(board[start] != '\0'){
			return this->loss;
		}
	}

	if(board[start + 2] == board[start + this->row + 1] && board[start + 2] == board[start + 2 * this->row]){
		if(board[start + 2] == mark)
			return this->win;
		else if(board[start + 2] != '\0'){
			return this->loss;
		}
	}

	//check draw
	for(i = 0; i < this->perBlockRow * this->perBlockRow; i++){
		int position = start + (i % 3) + int(i / 3) * this->row;
		if(board[position] == '\0'){
			return this->noResult;
		}
	}

	for(i = 0; i < this->blockNum; i++){
		if(endBlocks[i] == '\0'){
			return this->noResult;
		}
	}
	return this->draw;
}

//heuristic function 2 for 3x(3x3) tic-tac-toe (use danger block)
double AdvanceTTT::HResultTTT(char* board, char* dangerBlock, int* points, int takePosNum, char mark){
	double sumPoint = 0;
	bool whetherDoubleMark = false;
	bool whetherDoubleUnMark = false;
	int markCount = 0;
	int unmarkCount = 0;
	int markDangerCount = 0;
	int unmarkDangerCount = 0;
	int blockPerRow = int(sqrt(this->blockNum));
	int start = 0;
	int subStart = 0;
	char unmark = (this->compMark == mark ? this->userMark : this->compMark);
	bool markDangerExist = false;
	bool unmarkDangerExist = false;
	for(int i = 0; i < this->blockNum; i++){
		if(dangerBlock[i] == mark || dangerBlock[i] == 'b')
			markDangerExist = true;
		if(dangerBlock[i] == unmark || dangerBlock[i] == 'b')
			unmarkDangerExist = true;
	}

	for(int block = 0; block < this->blockNum; block++){

	    start = (block % blockPerRow) * this->perBlockRow + int(block / blockPerRow) * this->perBlockRow * this->row;

		//calculate point for current block
		//for each row and column
		for(int i = 0; i < this->perBlockRow; i++){
			//for row
			subStart = start + i * this->row;
			for(int j = 0; j < this->perBlockRow; j++){
				if(board[subStart + j] == mark)
					markCount += 1;
				else if(board[subStart + j] == unmark)
					unmarkCount += 1;
				else if(dangerBlock[i * this->perBlockRow + j] != 'b'){
					if(dangerBlock[i * this->perBlockRow + j] == mark)
						markDangerCount += 1;
					else if(dangerBlock[i * this->perBlockRow + j] == unmark)
						unmarkDangerCount += 1;
					else if(dangerBlock[i * this->perBlockRow + j] == '-'){
						if(markDangerExist)
							markDangerCount += 1;
						if(unmarkDangerExist)
							unmarkDangerCount += 1;
					}
				}
				else if(dangerBlock[i * this->perBlockRow + j] == 'b'){
					unmarkDangerCount += 1;
					markDangerCount += 1;
				}
			}
			//calculate for row
			if(markCount * unmarkCount == 0){
				if(markCount == 2){
					if(!whetherDoubleMark){
						sumPoint += points[2];
						whetherDoubleMark = true;
					}
					else
						sumPoint += points[1];
				}
				else if(unmarkCount == 2){
					if(!whetherDoubleUnMark){
						sumPoint -= points[2];
						whetherDoubleUnMark = true;
					}
					else{
						sumPoint -= points[1];
					}
				}
				else if(markCount == 1){
					if(unmarkDangerCount != 2)
						sumPoint += points[1];
				}
				else if(unmarkCount == 1){
					if(markDangerCount != 2)
						sumPoint -= points[1];
				}
				if(markCount == 3 || unmarkCount == 3)
					cerr << "impossible here!!!" << endl;
			}
			markCount = 0;
			unmarkCount = 0;
 			markDangerCount = 0;
			unmarkDangerCount = 0;

			//for column
			subStart = start + i;
			for(int j = 0; j < this->perBlockRow; j++){
				if(board[subStart + j * this->row] == mark)
					markCount += 1;
				else if(board[subStart + j * this->row] != '\0')
					unmarkCount += 1;
				else if(dangerBlock[i + j * this->perBlockRow] != 'b'){
					if(dangerBlock[i + j * this->perBlockRow] == mark)
						markDangerCount += 1;
					else if(dangerBlock[i + j * this->perBlockRow] == unmark)
						unmarkDangerCount += 1;
					else if(dangerBlock[i + j * this->perBlockRow] == '-'){
						if(markDangerExist)
							markDangerCount += 1;
						if(unmarkDangerExist)
							unmarkDangerCount += 1;
					}
				}
				else if(dangerBlock[i + j * this->perBlockRow] == 'b'){
					unmarkDangerCount += 1;
					markDangerCount += 1;
				}
			}
			//calculate for column
			if(markCount * unmarkCount == 0){
				if(markCount == 2){
					if(!whetherDoubleMark){
						sumPoint += points[2];
						whetherDoubleMark = true;
					}
					else
						sumPoint += points[1];
				}
				else if(unmarkCount == 2){
					if(!whetherDoubleUnMark){
						sumPoint -= points[2];
						whetherDoubleUnMark = true;
					}
					else{
						sumPoint -= points[1];
					}
				}
				else if(markCount == 1){
					if(unmarkDangerCount != 2)
						sumPoint += points[1];
				}
				else if(unmarkCount == 1){
					if(markDangerCount != 2)
						sumPoint -= points[1];
				}
				if(markCount == 3 || unmarkCount == 3)
					cerr << "impossible here!!!" << endl;
			}
			markCount = 0;
			unmarkCount = 0;
 			markDangerCount = 0;
			unmarkDangerCount = 0;
		}

		//for each diagnosis
		for(int i = 0; i < this->perBlockRow; i++){
			if(board[start + i * (1 + this->row)] == mark)
				markCount += 1;
			else if(board[start + i * (1 + this->row)] != '\0')
				unmarkCount += 1;
			else if(dangerBlock[i * (1 + this->perBlockRow)] != 'b'){
				if(dangerBlock[i * (1 + this->perBlockRow)] == mark)
					markDangerCount += 1;
				else if(dangerBlock[i * (1 + this->perBlockRow)] == unmark)
					unmarkDangerCount += 1;
				else if(dangerBlock[i * (1 + this->perBlockRow)] == '-'){
					if(markDangerExist)
						markDangerCount += 1;
					if(unmarkDangerExist)
						unmarkDangerCount += 1;
				}
			}
			else if(dangerBlock[i * (1 + this->perBlockRow)] == 'b'){
				unmarkDangerCount += 1;
				markDangerCount += 1;
			}
		}
		//calculate
		if(markCount * unmarkCount == 0){
			if(markCount == 2){
				if(!whetherDoubleMark){
					sumPoint += points[2];
					whetherDoubleMark = true;
				}
				else
					sumPoint += points[1];
			}
			else if(unmarkCount == 2){
				if(!whetherDoubleUnMark){
					sumPoint -= points[2];
					whetherDoubleUnMark = true;
				}
				else{
					sumPoint -= points[1];
				}
			}
			else if(markCount == 1){
				if(unmarkDangerCount != 2)
					sumPoint += points[1];
			}
			else if(unmarkCount == 1){
				if(markDangerCount != 2)
					sumPoint -= points[1];
			}
			if(markCount == 3 || unmarkCount == 3)
				cerr << "impossible here!!!" << endl;
		}
		markCount = 0;
		unmarkCount = 0;
		markDangerCount = 0;
		unmarkDangerCount = 0;

		//another diagnosis
		for(int i = 0; i < this->perBlockRow; i++){
			if(board[start + (this->perBlockRow - 1) + i * (this->row - 1)] == mark)
				markCount += 1;
			else if(board[start + (this->perBlockRow - 1) + i * (this->row - 1)] != '\0')
				unmarkCount += 1;
			else if(dangerBlock[(this->perBlockRow - 1) + i * (this->perBlockRow - 1)] != 'b'){
				if(dangerBlock[(this->perBlockRow - 1) + i * (this->perBlockRow - 1)] == mark)
					markDangerCount += 1;
				else if(dangerBlock[(this->perBlockRow - 1) + i * (this->perBlockRow - 1)] == unmark)
					unmarkDangerCount += 1;
				else if(dangerBlock[(this->perBlockRow - 1) + i * (this->perBlockRow - 1)] == '-'){
					if(markDangerExist)
						markDangerCount += 1;
					if(unmarkDangerExist)
						unmarkDangerCount += 1;
				}
			}
			else if(dangerBlock[(this->perBlockRow - 1) + i * (this->perBlockRow - 1)] == 'b'){
				unmarkDangerCount += 1;
				markDangerCount += 1;
			}
		}
		//calculate
		if(markCount * unmarkCount == 0){
			if(markCount == 2){
				if(!whetherDoubleMark){
					sumPoint += points[2];
					whetherDoubleMark = true;
				}
				else
					sumPoint += points[1];
			}
			else if(unmarkCount == 2){
				if(!whetherDoubleUnMark){
					sumPoint -= points[2];
					whetherDoubleUnMark = true;
				}
				else{
					sumPoint -= points[1];
				}
			}
			else if(markCount == 1){
				if(unmarkDangerCount != 2)
					sumPoint += points[1];
			}
			else if(unmarkCount == 1){
				if(markDangerCount != 2)
					sumPoint -= points[1];
			}
			if(markCount == 3 || unmarkCount == 3){
				cerr << "impossible here!!!" << endl;
			}
		}
		markCount = 0;
		unmarkCount = 0;
		markDangerCount = 0;
		unmarkDangerCount = 0;
		whetherDoubleMark = false;
		whetherDoubleUnMark = false;
	}

	//calculate the dangerous of current move
	if(dangerBlock[takePosNum] == unmark || dangerBlock[takePosNum] == 'b'){
		sumPoint -= points[3];
	}
	// else{
	// 	int markPoint = 0;
	// 	int unmarkPoint = 0;
	// 	int* stopPosition = new int[this->perBlockRow * this->perBlockRow];
	// 	int stopPoint = 0;
	// 	markCount = 0;
	// 	unmarkCount = 0;
	// 	markDangerCount = 0;
	// 	unmarkDangerCount = 0;
	// 	start = (takePosNum % blockPerRow) * this->perBlockRow + int(takePosNum / blockPerRow) * this->perBlockRow * this->row;
	// 	//for rows and columns
	// 	for(int i = 0; i < this->perBlockRow; i++){
	// 		//for rows
	// 		markCount = 0;
	// 		unmarkCount = 0;
	// 		markDangerCount = 0;
	// 		unmarkDangerCount = 0;
	// 		for(int column = 0; column < this->perBlockRow; column++){
	// 			if(board[start + i * this->row + column] == mark)
	// 				markCount += 1;
	// 			else if(board[start + i * this->row + column] != '\0')
	// 				unmarkCount += 1;
	// 			else if(dangerBlock[i * this->perBlockRow + column] != 'b'){
	// 				if(dangerBlock[i * this->perBlockRow + column] == mark)
	// 					markDangerCount += 1;
	// 				else if(dangerBlock[i * this->perBlockRow + column] == unmark)
	// 					unmarkDangerCount += 1;
	// 				else if(dangerBlock[i * this->perBlockRow + column] == '-'){
	// 					if(markDangerExist)
	// 						markDangerCount += 1;
	// 					if(unmarkDangerExist)
	// 						unmarkDangerCount += 1;
	// 				}
	// 			}
	// 			else if(dangerBlock[i * this->perBlockRow + column] == 'b'){
	// 				unmarkDangerCount += 1;
	// 				markDangerCount += 1;
	// 			}
	// 		}
	// 		if(markCount * unmarkCount == 0){
	// 			if(markCount == 2 && markDangerCount == 0){
	// 				for(int column = 0; column < this->perBlockRow; column++){
	// 					if(board[start + i * this->row + column] == '\0')
	// 						stopPosition[stopPoint++] = i * this->perBlockRow + column;
	// 				}
	// 			}
	// 			else if(markCount == 1 && unmarkDangerCount != 2){
	// 				markPoint += 1;
	// 			}
	// 			else if(unmarkCount == 1 && markDangerCount != 2){
	// 				unmarkPoint += 1;
	// 			}
	// 		}

	// 		//for columns
	// 		markCount = 0;
	// 		unmarkCount = 0;
	// 		markDangerCount = 0;
	// 		unmarkDangerCount = 0;
	// 		for(int row = 0; row < this->perBlockRow; row++){
	// 			if(board[start + row * this->row + i] == mark)
	// 				markCount += 1;
	// 			else if(board[start + row * this->row + i] != '\0')
	// 				unmarkCount += 1;
	// 			else if(dangerBlock[row * this->perBlockRow + i] != 'b'){
	// 				if(dangerBlock[row * this->perBlockRow + i] == mark)
	// 					markDangerCount += 1;
	// 				else if(dangerBlock[row * this->perBlockRow + i] == unmark)
	// 					unmarkDangerCount += 1;
	// 				else if(dangerBlock[row * this->perBlockRow + i] == '-'){
	// 					if(markDangerExist)
	// 						markDangerCount += 1;
	// 					if(unmarkDangerExist)
	// 						unmarkDangerCount += 1;
	// 				}
	// 			}
	// 			else if(dangerBlock[row * this->perBlockRow + i] == 'b'){
	// 				unmarkDangerCount += 1;
	// 				markDangerCount += 1;
	// 			}
	// 		}
	// 		if(markCount * unmarkCount == 0){
	// 			if(markCount == 2 && markDangerCount == 0){
	// 				for(int row = 0; row < this->perBlockRow; row++){
	// 					if(board[start + row * this->row + i] == '\0')
	// 						stopPosition[stopPoint++] = row * this->perBlockRow + i;
	// 				}
	// 			}
	// 			else if(markCount == 1 && unmarkDangerCount != 2){
	// 				markPoint += 1;
	// 			}
	// 			else if(unmarkCount == 1 && markDangerCount != 2){
	// 				unmarkPoint += 1;
	// 			}
	// 		}
	// 	}

	// 	markCount = 0;
	// 	unmarkCount = 0;
	// 	markDangerCount = 0;
	// 	unmarkDangerCount = 0;
	// 	//for diagnosis
	// 	for(int i = 0; i < this->perBlockRow; i++){
	// 		if(board[start + i * (1 + this->row)] == mark)
	// 			markCount += 1;
	// 		else if(board[start + i * (1 + this->row)] != '\0')
	// 			unmarkCount += 1;
	// 		else if(dangerBlock[i * (1 + this->perBlockRow)] != 'b'){
	// 			if(dangerBlock[i * (1 + this->perBlockRow)] == mark)
	// 				markDangerCount += 1;
	// 			else if(dangerBlock[i * (1 + this->perBlockRow)] == unmark)
	// 				unmarkDangerCount += 1;
	// 			else if(dangerBlock[i * (1 + this->perBlockRow)] == '-'){
	// 				if(markDangerExist)
	// 					markDangerCount += 1;
	// 				if(unmarkDangerExist)
	// 					unmarkDangerCount += 1;
	// 			}
	// 		}
	// 		else if(dangerBlock[i * (1 + this->perBlockRow)] == 'b'){
	// 			unmarkDangerCount += 1;
	// 			markDangerCount += 1;
	// 		}
	// 	}
	// 	//calculate
	// 	if(markCount * unmarkCount == 0){
	// 		if(markCount == 2 && markDangerCount == 0){
	// 			for(int i = 0; i < this->perBlockRow; i++){
	// 				if(board[start + i * (1 + this->row)] == '\0')
	// 					stopPosition[stopPoint++] = i * (1 + this->perBlockRow);
	// 			}
	// 		}
	// 		else if(markCount == 1 && unmarkDangerCount != 2){
	// 			markPoint += 1;
	// 		}
	// 		else if(unmarkCount == 1 && markDangerCount != 2){
	// 			unmarkPoint += 1;
	// 		}
	// 	}

	// 	//for another diagnosis
	// 	for(int i = 0; i < this->perBlockRow; i++){
	// 		if(board[start + (this->perBlockRow - 1) + i * (this->row - 1)] == mark)
	// 			markCount += 1;
	// 		else if(board[start + (this->perBlockRow - 1) + i * (this->row - 1)] != '\0')
	// 			unmarkCount += 1;
	// 		else if(dangerBlock[(this->perBlockRow - 1) + i * (this->perBlockRow - 1)] != 'b'){
	// 			if(dangerBlock[(this->perBlockRow - 1) + i * (this->perBlockRow - 1)] == mark)
	// 				markDangerCount += 1;
	// 			else if(dangerBlock[(this->perBlockRow - 1) + i * (this->perBlockRow - 1)] == unmark)
	// 				unmarkDangerCount += 1;
	// 			else if(dangerBlock[(this->perBlockRow - 1) + i * (this->perBlockRow - 1)] == '-'){
	// 				if(markDangerExist)
	// 					markDangerCount += 1;
	// 				if(unmarkDangerExist)
	// 					unmarkDangerCount += 1;
	// 			}
	// 		}
	// 		else if(dangerBlock[(this->perBlockRow - 1) + i * (this->perBlockRow - 1)] == 'b'){
	// 			unmarkDangerCount += 1;
	// 			markDangerCount += 1;
	// 		}
	// 	}

	// 	//calculate
	// 	if(markCount * unmarkCount == 0){
	// 		if(markCount == 2 && markDangerCount == 0){
	// 			for(int i = 0; i < this->perBlockRow; i++){
	// 				if(board[start + (this->perBlockRow - 1) + i * (this->row - 1)] == '\0')
	// 					stopPosition[stopPoint++] = (this->perBlockRow - 1) + i * (this->perBlockRow - 1);
	// 			}
	// 		}
	// 		else if(markCount == 1 && unmarkDangerCount != 2){
	// 			markPoint += 1;
	// 		}
	// 		else if(unmarkCount == 1 && markDangerCount != 2){
	// 			unmarkPoint += 1;
	// 		}
	// 	}

	// 	//mark has two points in a line
	// 	if(stopPoint == 1){
	// 		int tempPos = stopPosition[stopPoint];
	// 		if(tempPos == 0 || tempPos == 3 || tempPos == 6){
	// 			if(board[start + int(tempPos / 3) * this->row + 1] == unmark || board[start + int(tempPos / 3) * this->row + 2] == unmark){
	// 				sumPoint -= points[2];
	// 			}
	// 			else if(board[start] == unmark || board[start + this->row] == unmark || board[start + 2 * this->row] == unmark){
	// 				sumPoint -= points[2];
	// 			}
	// 		}

	// 		else if(tempPos == 1 || tempPos == 4 || tempPos == 7){
	// 			if(board[start + int(tempPos / 3) * this->row] == unmark || board[start + int(tempPos / 3) * this->row + 2] == unmark){
	// 				sumPoint -= points[2];
	// 			}
	// 			else if(board[start + 1] == unmark || board[start + this->row + 1] == unmark || board[start + 2 * this->row + 1] == unmark){
	// 				sumPoint -= points[2];
	// 			}
	// 		}

	// 		else if(tempPos == 2 || tempPos == 5 || tempPos == 8){
	// 			if(board[start + int(tempPos / 3) * this->row] == unmark || board[start + int(tempPos / 3) * this->row + 1] == unmark){
	// 				sumPoint -= points[2];
	// 			}
	// 			else if(board[start + 2] == unmark || board[start + this->row + 2] == unmark || board[start + 2 * this->row + 2] == unmark){
	// 				sumPoint -= points[2];
	// 			}
	// 		}

	// 		else if(tempPos == 0 || tempPos == 4 || tempPos == 8){
	// 			if(board[start] == unmark || board[start + 1 + this->row] == unmark || board[start + 2 + 2 * this->row] == unmark){
	// 				sumPoint -= points[2];
	// 			}
	// 		}

	// 		else if(tempPos == 6 || tempPos == 4 || tempPos == 2){
	// 			if(board[start + 2] == unmark || board[start + 1 + this->row] == unmark || board[start + 2 * this->row] == unmark){
	// 				sumPoint -= points[2];
	// 			}
	// 		}
	// 	}

	// 	//unmark has one point in a line
	// 	else if(unmarkPoint > 0){
	// 		sumPoint -= 0.5 * points[2];
	// 	}
	// }

	return sumPoint;
}

//heuristic function 1 for 3x(3x3) tic-tac-toe
double AdvanceTTT::HResultTTT(char* board, int* points, char mark){
	double sumPoint = 0;
	bool whetherDoubleMark = false;
	bool whetherDoubleUnMark = false;
	int markCount = 0;
	int unmarkCount = 0;
	int blockPerRow = int(sqrt(this->blockNum));
	int start = 0;
	int subStart = 0;

	for(int block = 0; block < this->blockNum; block++){

	    start = (block % blockPerRow) * this->perBlockRow + int(block / blockPerRow) * this->perBlockRow * this->row;

		//calculate point for current block
		//for each row and column
		for(int i = 0; i < this->perBlockRow; i++){
			//for row
			subStart = start + i * this->row;
			for(int j = 0; j < this->perBlockRow; j++){
				if(board[subStart + j] == mark)
					markCount += 1;
				else if(board[subStart + j] != '\0')
					unmarkCount += 1;
			}
			//calculate for row
			if(markCount * unmarkCount == 0){
				if(markCount == 2){
					if(!whetherDoubleMark){
						sumPoint += points[2];
						whetherDoubleMark = true;
					}
					else
						sumPoint += points[1];
				}
				else if(unmarkCount == 2){
					if(!whetherDoubleUnMark){
						sumPoint -= points[2];
						whetherDoubleUnMark = true;
					}
					else{
						sumPoint -= points[1];
					}
				}
				else{
					sumPoint += points[1] * (markCount - unmarkCount);
				}
				if(markCount == 3 || unmarkCount == 3)
					cerr << "impossible here!!!" << endl;
			}
			markCount = 0;
			unmarkCount = 0;

			//for column
			subStart = start + i;
			for(int j = 0; j < this->perBlockRow; j++){
				if(board[subStart + j * this->row] == mark)
					markCount += 1;
				else if(board[subStart + j * this->row] != '\0')
					unmarkCount += 1;
			}
			//calculate for column
			if(markCount * unmarkCount == 0){
				if(markCount == 2){
					if(!whetherDoubleMark){
						sumPoint += points[2];
						whetherDoubleMark = true;
					}
					else
						sumPoint += points[1];
				}
				else if(unmarkCount == 2){
					if(!whetherDoubleUnMark){
						sumPoint -= points[2];
						whetherDoubleUnMark = true;
					}
					else{
						sumPoint -= points[1];
					}
				}
				else{
					sumPoint += points[1] * (markCount - unmarkCount);
				}
				if(markCount == 3 || unmarkCount == 3)
					cerr << "impossible here!!!" << endl;
			}
			markCount = 0;
			unmarkCount = 0;
		}

		//for each diagnosis
		for(int i = 0; i < this->perBlockRow; i++){
			if(board[start + i * (1 + this->row)] == mark)
				markCount += 1;
			else if(board[start + i * (1 + this->row)] != '\0')
				unmarkCount += 1;
		}
		//calculate
		if(markCount * unmarkCount == 0){
			if(markCount == 2){
				if(!whetherDoubleMark){
					sumPoint += points[2];
					whetherDoubleMark = true;
				}
				else
					sumPoint += points[1];
			}
			else if(unmarkCount == 2){
				if(!whetherDoubleUnMark){
					sumPoint -= points[2];
					whetherDoubleUnMark = true;
				}
				else{
					sumPoint -= points[1];
				}
			}
			else{
				sumPoint += points[1] * (markCount - unmarkCount);
			}
			if(markCount == 3 || unmarkCount == 3)
				cerr << "impossible here!!!" << endl;
		}
		markCount = 0;
		unmarkCount = 0;

		//another diagnosis
		for(int i = 0; i < this->perBlockRow; i++){
			if(board[start + (this->perBlockRow - 1) + i * (this->row - 1)] == mark)
				markCount += 1;
			else if(board[start + (this->perBlockRow - 1) + i * (this->row - 1)] != '\0')
				unmarkCount += 1;
		}
		//calculate
		if(markCount * unmarkCount == 0){
			if(markCount == 2){
				if(!whetherDoubleMark){
					sumPoint += points[2];
					whetherDoubleMark = true;
				}
				else
					sumPoint += points[1];
			}
			else if(unmarkCount == 2){
				if(!whetherDoubleUnMark){
					sumPoint -= points[2];
					whetherDoubleUnMark = true;
				}
				else{
					sumPoint -= points[1];
				}
			}
			else{
				sumPoint += points[1] * (markCount - unmarkCount);
			}
			if(markCount == 3 || unmarkCount == 3){
				cerr << "impossible here!!!" << endl;
			}
		}
		markCount = 0;
		unmarkCount = 0;
		whetherDoubleMark = false;
		whetherDoubleUnMark = false;
	}
	return sumPoint;
}

//get board
char* AdvanceTTT::getboard(){
	return this->board;
}

//get position
int AdvanceTTT::getPosition(char* board1, char* board2){
	for(int position = 0; position < this->row * this->row; position++){
		if(board1[position] != board2[position])
			return position;
	}
	cerr << "wrong input" << endl;
	return -1;
}

//get next boards
char*** AdvanceTTT::getNextBoards(char* board, char mark, int takePosNum, char* endBlocks){
	char*** nextBoard = NULL;
	int blockPerRow = int(sqrt(this->blockNum));
	int boardSize = this->row * this->row;

	//in a certain block
	if(takePosNum != -1){
		nextBoard = new char**[1];
		nextBoard[0] = new char*[this->perBlockRow * this->perBlockRow];

		for(int i = 0; i < this->perBlockRow * this->perBlockRow; i++){
			int start = (takePosNum % blockPerRow) * this->perBlockRow + int(takePosNum / blockPerRow) * this->perBlockRow * this->row;
			int position = start + (i % 3) + int(i / 3) * this->row;
			if(board[position] == '\0'){
				nextBoard[0][i] = new char[boardSize];
				for(int j = 0; j < boardSize; j++){
					nextBoard[0][i][j] = board[j];
				}
				nextBoard[0][i][position] = mark;
			}
			else
				nextBoard[0][i] = NULL;
		}
		return nextBoard;
	}

	//any blocks
	nextBoard = new char**[this->blockNum];
	for(int i = 0; i < this->blockNum; i++){
		//for each blocks
		if(endBlocks[i] == '\0'){
			nextBoard[i] = new char*[this->perBlockRow * this->perBlockRow];

			//inside the block
			int start = (i % blockPerRow) * this->perBlockRow + int(i / blockPerRow) * this->perBlockRow * this->row;
			for(int j = 0; j < this->perBlockRow * this->perBlockRow; j++){
				int position = start + (j % 3) + int(j / 3) * this->row;
				if(board[position] == '\0'){
					nextBoard[i][j] = new char[boardSize];
					for(int k = 0; k < boardSize; k++){
						nextBoard[i][j][k] = board[k];
					}
					nextBoard[i][j][position] = mark;
				}
				else
					nextBoard[i][j] = NULL;
			}
		}
		else{
			nextBoard[i] = NULL;
		}
	}

	return nextBoard;
}

//get row in each block
int AdvanceTTT::getPerBlockRow(){
	return this->perBlockRow;
}

//get block number
int AdvanceTTT::getBlockNum(){
	return this->blockNum;
}

//get whether block is useful
char AdvanceTTT::blockUseful(int block){
	return this->endBlocks[block];
}

//get next block number (the position number that last turn take)
int AdvanceTTT::getNextBlock(){
	return this->takePosNum;
}

//get end blocks
char* AdvanceTTT::getEndBlocks(){
	return this->endBlocks;
}

//get danger blocks
char* AdvanceTTT::getDangerBlocks(){
	return this->dangerBlocks;
}

//set take block number
void AdvanceTTT::setTakeBlock(int takePosNum){
	this->takePosNum = takePosNum;
}

//get block number taken at last time
int AdvanceTTT::getLastBlock(){
	return this->takeBlockNum;
}

//set block number taken at last time
void AdvanceTTT::setLastBlock(int block){
	this->takeBlockNum = block;
}