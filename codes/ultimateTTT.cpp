#include "TTT.h"
#include <iostream>
#include <math.h>
using namespace std;

//constructor
UltimateTTT::UltimateTTT(double win, double loss, double draw, double noResult) : AdvanceTTT(win, loss, draw, noResult){}

//destructor
UltimateTTT::~UltimateTTT(){}

//update blockResults
char* UltimateTTT::updateBlock(char* endBlocks, char* board, int block, char mark){
	if(endBlocks[block] != '\0'){
		cerr << "block has already ended" << endl;
		return NULL;
	}

	char* newEndBlocks = new char[this->blockNum];
	for(int i = 0; i < this->blockNum; i++){
		newEndBlocks[i] = endBlocks[i];
	}

	//update current block
	double result = AdvanceTTT::gameOverTTT(board, endBlocks, block, mark);
	if(result == this->win){
		newEndBlocks[block] = mark;
	}
	else if(result == this->loss){
		if(mark == this->userMark)
			newEndBlocks[block] = this->compMark;
		else
			newEndBlocks[block] = this->userMark;
	}
	else{
		delete[] newEndBlocks;
		newEndBlocks = AdvanceTTT::updateBlock(endBlocks, board, block);
	}

	return newEndBlocks;
}

//game over test
double UltimateTTT::gameOverTTT(char* endBlocks, char mark){
	int blockPerRow = int(sqrt(this->blockNum));

	//diagonal
	if(endBlocks[0] == endBlocks[0 + blockPerRow + 1] && endBlocks[0] == endBlocks[0 + 2 * (blockPerRow + 1)]){
		if(endBlocks[0] == mark)
			return this->win;
		else if(endBlocks[0] != '\0' && endBlocks[0] != '-')
			return this->loss;
	}
	if(endBlocks[2] == endBlocks[2 + blockPerRow - 1] && endBlocks[2] == endBlocks[2 + 2 * (blockPerRow - 1)]){
		if(endBlocks[2] == mark)
			return this->win;
		else if(endBlocks[2] != '\0' && endBlocks[2] != '-')
			return this->loss;
	}

	for(int j = 0; j < blockPerRow; j++){
		//rows
		if(endBlocks[j * blockPerRow] == endBlocks[j * blockPerRow + 1] && endBlocks[j * blockPerRow] == endBlocks[j * blockPerRow + 2]){
			if(endBlocks[j * blockPerRow] == mark)
				return this->win;
			else if(endBlocks[j * blockPerRow] != '\0' && endBlocks[j * blockPerRow] != '-')
				return this->loss;
		}

		//columns
		if(endBlocks[j] == endBlocks[j + blockPerRow] && endBlocks[j] == endBlocks[j + 2 * blockPerRow]){
			if(endBlocks[j] == mark)
				return this->win;
			else if(endBlocks[j] != '\0' && endBlocks[j] != '-')
				return this->loss;
		}
	}

	//draw
	int i = 0;
	while(i < 9){
		if(endBlocks[i] == '\0')
			break;
		i += 1;
	}
	if(i == 9)
		return this->draw;
	return this->noResult;
}

//heuristic function
double UltimateTTT::HResultTTT(char* board, char* endBlocks, int* inPoints, int* outPoints, char mark){
	double* blockPoints = new double[this->blockNum];
	for(int i = 0; i < this->blockNum; i++){
		if(endBlocks[i] == '\0')
			blockPoints[i] = 0;
		else if(endBlocks[i] == mark)
			blockPoints[i] = 1;
		else if(endBlocks[i] == '-')
			blockPoints[i] = -2;
		else
			blockPoints[i] = -1;
	}

	bool whetherDoubleMark = false;
	bool whetherDoubleUnMark = false;
	double sumPoint = 0;
	int markCount = 0;
	int unmarkCount = 0;
	int blockPerRow = int(sqrt(this->blockNum));
	int start = 0;
	int subStart = 0;
	double markPoint = 0;
	double unmarkPoint = 0;

	//calculate points for each block
	for(int block = 0; block < this->blockNum; block++){

		if(blockPoints[block] != 0)
			continue;

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
						blockPoints[block] += inPoints[2];
						whetherDoubleMark = true;
					}
					else
						blockPoints[block]  += inPoints[1];
				}
				else if(unmarkCount == 2){
					if(!whetherDoubleUnMark){
						blockPoints[block]  -= inPoints[2];
						whetherDoubleUnMark = true;
					}
					else{
						blockPoints[block]  -= inPoints[1];
					}
				}
				else{
					blockPoints[block]  += inPoints[1] * (markCount - unmarkCount);
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
						blockPoints[block]  += inPoints[2];
						whetherDoubleMark = true;
					}
					else
						blockPoints[block]  += inPoints[1];
				}
				else if(unmarkCount == 2){
					if(!whetherDoubleUnMark){
						blockPoints[block]  -= inPoints[2];
						whetherDoubleUnMark = true;
					}
					else{
						blockPoints[block]  -= inPoints[1];
					}
				}
				else{
					blockPoints[block]  += inPoints[1] * (markCount - unmarkCount);
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
					blockPoints[block]  += inPoints[2];
					whetherDoubleMark = true;
				}
				else
					blockPoints[block]  += inPoints[1];
			}
			else if(unmarkCount == 2){
				if(!whetherDoubleUnMark){
					blockPoints[block]  -= inPoints[2];
					whetherDoubleUnMark = true;
				}
				else{
					blockPoints[block]  -= inPoints[1];
				}
			}
			else{
				blockPoints[block]  += inPoints[1] * (markCount - unmarkCount);
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
					blockPoints[block]  += inPoints[2];
					whetherDoubleMark = true;
				}
				else
					blockPoints[block]  += inPoints[1];
			}
			else if(unmarkCount == 2){
				if(!whetherDoubleUnMark){
					blockPoints[block]  -= inPoints[2];
					whetherDoubleUnMark = true;
				}
				else{
					blockPoints[block]  -= inPoints[1];
				}
			}
			else{
				blockPoints[block]  += inPoints[1] * (markCount - unmarkCount);
			}
			if(markCount == 3 || unmarkCount == 3){
				cerr << "impossible here!!!" << endl;
			}
		}
		markCount = 0;
		unmarkCount = 0;
		whetherDoubleMark = false;
		whetherDoubleUnMark = false;
		blockPoints[block] = blockPoints[block] / inPoints[3];
	}

	//calculate total point for general board
	for(int block = 0; block < this->perBlockRow; block++){
		//for row
		markPoint = 0;
		unmarkPoint = 0;
		markCount = 0;
		unmarkCount = 0;
		for(int column = 0; column < this->perBlockRow; column++){
			if(blockPoints[block + column] == -2){	//block draw
				markCount = -1;
				unmarkCount = -1;
				break;
			}
			if(blockPoints[block + column] == 1){	//entire advantage for current player
				unmarkCount = -1;
				if(markCount != -1){
					markCount += 1;
					markPoint += blockPoints[block + column];
				}
				else
					break;
				continue;
			}
			if(blockPoints[block + column] == -1){	//entire advantage for opposite player
				markCount = -1;
				if(unmarkCount != -1){
					unmarkCount += 1;
					unmarkPoint += blockPoints[block + column];
				}
				else
					break;
				continue;
			}
			if(blockPoints[block + column] == 0){	//block no advantage
				continue;
			}
			if(blockPoints[block + column] > 0){	//advantage for current player
				if(markCount != -1)
					markCount += 1;
				markPoint += blockPoints[block + column];
				continue;
			}
			if(blockPoints[block + column] < 0){	//advantage for opposite player
				if(unmarkCount != -1)
					unmarkCount += 1;
				unmarkPoint += blockPoints[block + column];
				continue;
			}
		}
		if(unmarkCount == -1 && markCount == -1)
			sumPoint += 0;
		else if(markCount == -1)
			sumPoint += unmarkPoint * outPoints[unmarkCount] + markPoint * outPoints[1] * 0.8;
		else if(unmarkCount == -1)
			sumPoint += markPoint * outPoints[markCount] + unmarkPoint * outPoints[1] * 0.8;
		else
			sumPoint += markPoint * outPoints[markCount] + unmarkPoint * outPoints[unmarkCount];

		//for column
		markPoint = 0;
		unmarkPoint = 0;
		markCount = 0;
		unmarkCount = 0;
		for(int row = 0; row < this->perBlockRow; row++){
			if(blockPoints[block + row * this->perBlockRow] == -2){	//block draw
				markCount = -1;
				unmarkCount = -1;
				break;
			}
			if(blockPoints[block + row * this->perBlockRow] == 1){	//entire advantage for current player
				unmarkCount = -1;
				if(markCount != -1){
					markCount += 1;
					markPoint += blockPoints[block + row * this->perBlockRow];
				}
				else
					break;
				continue;
			}
			if(blockPoints[block + row * this->perBlockRow] == -1){	//entire advantage for opposite player
				markCount = -1;
				if(unmarkCount != -1){
					unmarkCount += 1;
					unmarkPoint += blockPoints[block + row * this->perBlockRow];
				}
				else
					break;
				continue;
			}
			if(blockPoints[block + row * this->perBlockRow] == 0){	//block no advantage
				continue;
			}
			if(blockPoints[block + row * this->perBlockRow] > 0){	//advantage for current player
				if(markCount != -1)
					markCount += 1;
				markPoint += blockPoints[block + row * this->perBlockRow];
				continue;
			}
			if(blockPoints[block + row * this->perBlockRow] < 0){	//advantage for opposite player
				if(unmarkCount != -1)
					unmarkCount += 1;
				unmarkPoint += blockPoints[block + row * this->perBlockRow];
				continue;
			}
		}
		if(unmarkCount == -1 && markCount == -1)
			sumPoint += 0;
		else if(markCount == -1)
			sumPoint += unmarkPoint * outPoints[unmarkCount] + markPoint * outPoints[1] * 0.8;
		else if(unmarkCount == -1)
			sumPoint += markPoint * outPoints[markCount] + unmarkPoint * outPoints[1] * 0.8;
		else
			sumPoint += markPoint * outPoints[markCount] + unmarkPoint * outPoints[unmarkCount];
	}

	//for diagonal
	markPoint = 0;
	unmarkPoint = 0;
	markCount = 0;
	unmarkCount = 0;
	for(int row = 0; row < this->perBlockRow; row++){
		if(blockPoints[0 + row * (this->perBlockRow + 1)] == -2){	//block draw
			markCount = -1;
			unmarkCount = -1;
			break;
		}
		if(blockPoints[0 + row * (this->perBlockRow + 1)] == 1){	//entire advantage for current player
			unmarkCount = -1;
			if(markCount != -1){
				markCount += 1;
				markPoint += blockPoints[0 + row * (this->perBlockRow + 1)];
			}
			else
				break;
			continue;
		}
		if(blockPoints[0 + row * (this->perBlockRow + 1)] == -1){	//entire advantage for opposite player
			markCount = -1;
			if(unmarkCount != -1){
				unmarkCount += 1;
				unmarkPoint += blockPoints[0 + row * (this->perBlockRow + 1)];
			}
			else
				break;
			continue;
		}
		if(blockPoints[0 + row * (this->perBlockRow + 1)] == 0){	//block no advantage
			continue;
		}
		if(blockPoints[0 + row * (this->perBlockRow + 1)] > 0){	//advantage for current player
			if(markCount != -1)
				markCount += 1;
			markPoint += blockPoints[0 + row * (this->perBlockRow + 1)];
			continue;
		}
		if(blockPoints[0 + row * (this->perBlockRow + 1)] < 0){	//advantage for opposite player
			if(unmarkCount != -1)
				unmarkCount += 1;
			unmarkPoint += blockPoints[0 + row * (this->perBlockRow + 1)];
			continue;
		}
	}
	if(unmarkCount == -1 && markCount == -1)
		sumPoint += 0;
	else if(markCount == -1)
		sumPoint += unmarkPoint * outPoints[unmarkCount] + markPoint * outPoints[1] * 0.8;
	else if(unmarkCount == -1)
		sumPoint += markPoint * outPoints[markCount] + unmarkPoint * outPoints[1] * 0.8;
	else
		sumPoint += markPoint * outPoints[markCount] + unmarkPoint * outPoints[unmarkCount];

	markPoint = 0;
	unmarkPoint = 0;
	markCount = 0;
	unmarkCount = 0;
	for(int row = 0; row < this->perBlockRow; row++){
		if(blockPoints[this->perBlockRow + row * (this->perBlockRow - 1)] == -2){	//block draw
			markCount = -1;
			unmarkCount = -1;
			break;
		}
		if(blockPoints[this->perBlockRow + row * (this->perBlockRow - 1)] == 1){	//entire advantage for current player
			unmarkCount = -1;
			if(markCount != -1){
				markCount += 1;
				markPoint += blockPoints[this->perBlockRow + row * (this->perBlockRow - 1)];
			}
			else
				break;
			continue;
		}
		if(blockPoints[this->perBlockRow + row * (this->perBlockRow - 1)] == -1){	//entire advantage for opposite player
			markCount = -1;
			if(unmarkCount != -1){
				unmarkCount += 1;
				unmarkPoint += blockPoints[this->perBlockRow + row * (this->perBlockRow - 1)];
			}
			else
				break;
			continue;
		}
		if(blockPoints[this->perBlockRow + row * (this->perBlockRow - 1)] == 0){	//block no advantage
			continue;
		}
		if(blockPoints[this->perBlockRow + row * (this->perBlockRow - 1)] > 0){	//advantage for current player
			if(markCount != -1)
				markCount += 1;
			markPoint += blockPoints[this->perBlockRow + row * (this->perBlockRow - 1)];
			continue;
		}
		if(blockPoints[this->perBlockRow + row * (this->perBlockRow - 1)] < 0){	//advantage for opposite player
			if(unmarkCount != -1)
				unmarkCount += 1;
			unmarkPoint += blockPoints[this->perBlockRow + row * (this->perBlockRow - 1)];
			continue;
		}
	}
	if(unmarkCount == -1 && markCount == -1)
		sumPoint += 0;
	else if(markCount == -1)
		sumPoint += unmarkPoint * outPoints[unmarkCount] + markPoint * outPoints[1] * 0.8;
	else if(unmarkCount == -1)
		sumPoint += markPoint * outPoints[markCount] + unmarkPoint * outPoints[1] * 0.8;
	else
		sumPoint += markPoint * outPoints[markCount] + unmarkPoint * outPoints[unmarkCount];

	delete[] blockPoints;
	blockPoints = NULL;
	return sumPoint;
}