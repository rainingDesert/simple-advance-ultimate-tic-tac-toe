#ifndef TTT_H
#define TTT_H
#include <iostream>
using namespace std;


//game function
class Game{
protected:
	Game();
	char userMark;
	char compMark;
	int row;
	double win;
	double loss;
	double draw;
	double noResult;
public:
	Game(double, double, double, double, int);
	virtual double gameOverTTT(char*, char);
	virtual char* getboard();
	virtual int getPosition(char*, char*);
	virtual char** getNextBoards(char*, char);
	bool result(double);
	void setMark(char, char);
	char getUserMark();
	char getCompMark();
	int getResult(double);
	int getRow();
	void changeMark();
};

//3x3 tic-tac-toe
class SimpleTTT: public Game{
private:
	char* board;
public:
	SimpleTTT(double, double, double, double);
	~SimpleTTT();
	double gameOverTTT(char*, char);
	char* getboard();
	int getPosition(char*, char*);
	char** getNextBoards(char*, char);
};

//3x(3x3) tic-tac-toe
class AdvanceTTT : public Game{
protected:
	int blockNum;
	int perBlockRow;
	char* board;
	int takePosNum;
	int takeBlockNum;
	char* endBlocks;
	char* dangerBlocks;

public:
	AdvanceTTT(double, double, double, double);
	virtual ~AdvanceTTT();
	char* updateBlock(char*, char*, int);
	char* updateDangerBlock(char*, char*, int);
	char** getNextBoards(char*, char);
	double gameOverTTT(char*, char);
	double gameOverTTT(char*, char*, int, char);
	double HResultTTT(char*, char*, int*, int, char);
	double HResultTTT(char*, int*, char);

	char* getboard();
	int getPosition(char*, char*);
	char*** getNextBoards(char*, char, int ,char*);
	int getPerBlockRow();
	int getBlockNum();
	char blockUseful(int);
	int getNextBlock();
	char* getEndBlocks();
	char* getDangerBlocks();
	void setTakeBlock(int);
	int getLastBlock();
	void setLastBlock(int);
};

//Ultimate tic-tac-toe
class UltimateTTT : public AdvanceTTT{
private:

public:
	UltimateTTT(double, double, double, double);
	~UltimateTTT();
	char* updateBlock(char*,  char*, int, char);
	double gameOverTTT(char*, char);
	double HResultTTT(char*, char*, int*, int*, char);
};

//class for interaction
class TTTUI{
protected:
	Game* game;
	char marks[2];
	void initInput();
public:
	TTTUI(Game*);
	virtual ~TTTUI();
	virtual void displayBoard();
	virtual void userTurn();
	virtual void compTurn(int);
	virtual void assignTurn(int, char);
	void printResult(int);
	void setGame();
};

//class for Simple TTT UI
class STTTUI : public TTTUI{
public:
	STTTUI(Game*);
	void displayBoard();
};

//class for 3x(3x3) TTT UI
class ATTTUI : public TTTUI{
private:
	AdvanceTTT* attt;
public:
	ATTTUI(Game*);
	void displayBoard();
	void userTurn();
	void compTurn(int);
	void assignTurn(int, char);

};

//class for ultimate TTT UI
class UTTTUI: public TTTUI{
private:
	UltimateTTT* uttt;
public:
	UTTTUI(Game*);
	void displayBoard();
	void userTurn();
	void compTurn(int);
	void assignTurn(int, char);
};

//class for computer's stratagem
class Stratagem{
private:
	/////////////////////////////////////////----------AlphaBeta--------------//////////////////////////////////////////////////
	class AlphaBeta{
	protected:
		struct node;
		//heap
		node* heap;
		double* alphas;
		double* betas;
		int limitDepth;
		int length;
		int boardSize;
		int top;
		int blockNum;
		node* getNode();
		void pushNode(char*, int, bool);
		virtual double getResult(node*, Game*);
	public:
		AlphaBeta();
		AlphaBeta(char*, int);
		virtual ~AlphaBeta();
		virtual void pushNextSteps(node*, Game*);
		int doAlphaBeta(Game*);
	};

	//alpha beta search for advance
	class AlphaBetaForAdvanced: public AlphaBeta{
	protected:
		void pushNode(char*, char*, int, bool, char*, int, int);
		virtual double getResult(node*, Game*);
	public:
		AlphaBetaForAdvanced(AdvanceTTT*, int);
		virtual ~AlphaBetaForAdvanced();
		void pushNextSteps(node*, Game*);
	};

	//H-alphaBeta search for advance
	class HAlphaBetaForAdvanced: public AlphaBetaForAdvanced{
	protected:
		int* points;
		double getResult(node*, Game*);
	public:
		HAlphaBetaForAdvanced(AdvanceTTT*, int);
		~HAlphaBetaForAdvanced();
	};

	//H-alphaBeta search for ultimate TTT
	class HAlphaBetaForUltimate: public AlphaBeta{
	protected:
		int* inPoints;
		int* outPoints;
		void pushNode(char*, int, bool, char*, int, int);
		double getResult(node*, Game*);
	public:
		HAlphaBetaForUltimate(UltimateTTT*, int, int*, int*);
		HAlphaBetaForUltimate(UltimateTTT*, int);
		~HAlphaBetaForUltimate();
		void pushNextSteps(node*, Game*);
	};

	/////////////////////////////////////////----------UCT--------------//////////////////////////////////////////////////
	// class for UCT (Upper Confidence Bound for Trees)
	class UCT{
	protected:
		struct node;
		Game* game;
		int boardSize;
		int blockNum;
		int limitSim;
		double c;	//constant number of UCT
		node* root;	//root board

		void printDepth(node*);

		bool whetherExpand(node*);	//detect whether node has been expanded
		node* selection(node*);	//select node to be expanded
		node* expand(node*);	//expand current node
		node* bestChild(node*);	//algorith for selecting node
		double simulation(node*);	//randomly select actions
		void backup(node*, double);	//save result
		void deleteNode(node*);		//call by destructor
		void descendNode(node*);	//level up nodes
		virtual double getResult(node*);	//get result value
		virtual void getChildren(node*);	//get children nodes
		virtual node* simChildren(node*);	//get children nodes for simulation
		virtual double calScore(node*);		//calculate score for current node
	public:
		UCT(Game*, int, double, int limitSim = -1);
		virtual ~UCT();
		virtual int UCTSearch();	//call UCT Search
	};

	// class for UCT applied to Advanced Tic-Tac-Toe
	class UCTForAdvanced: public UCT{
	protected:
		AdvanceTTT* attt;
		double getResult(node*);		//get result value
		void getChildren(node*);		//get children nodes
		node* simChildren(node*);		//get Children nodes for simulation
		double calScore(node*);			//calculate score for current node
		node* randomPosition(node*);	//get next move randomly
	public:
		UCTForAdvanced(Game*, double, int);
		~UCTForAdvanced();
		int UCTSearch();
	};

	// class for UCT applied to Ultimate Tic-Tac-Toe
	class UCTForUltimate: public UCT{
	protected:
		UltimateTTT* uttt;
		double getResult(node*);		//get result value
		void getChildren(node*);		//get children nodes
		node* simChildren(node*);		//get Children nodes for simulation
		double calScore(node*);			//calculate score for current node
		node* randomPosition(node*);	//get next move randomly
	public:
		UCTForUltimate(Game*, double, int);
		~UCTForUltimate();
		int UCTSearch();
	};

	UCT* uct;

public:
	Stratagem();
	~Stratagem();
	int randomMove(char*, int);
	int randomMoveForAdvance(Game*);
	int alphaBetaSearch(Game*);
	int alphaBetaAdvanceSearch(Game*);
	int hAlphaBetaAdvanceSearch(Game*, int);
	int hAlphaBetaUltimateSearch(Game*, int, int* inPoint = NULL, int* outPOint = NULL);
	int UCTAdvancedSearch(Game*, double, int);
	int UCTUltimateSearch(Game*, double, int);
	void deleteUCT();
};

//class for implementation
class Imp{
private:
	Stratagem* stat;
	char userMark;
	char playType;
	char statType;
	int limitDepth;
	int limitSim;
	double UCTConstant;
	TTTUI* tttui;
	Game* game;
	Game* getGame(double, double, double, double);
	double getResult();
	TTTUI* getUI();
	int getPosition();
public:
	Imp(char, char, double, double, double, double, int, double UCTConstant = 0.5);
	~Imp();
	Game* simpleTTT(double, double, double, double);
	Game* advanceTTT(double, double, double, double);
	Game* ultimateTTT(double, double, double, double);
	void execution();
}; 

#endif