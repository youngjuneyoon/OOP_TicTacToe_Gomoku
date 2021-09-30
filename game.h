#pragma once
#include <iostream>
#include <iostream>
#include <string>
#include <vector>
#include "Header.h"
using namespace std;

class BaseGame {
public: static BaseGame* checkerOne(int temp1, char* temp2[]); 
		virtual void print() = 0; 
		virtual bool done() = 0; 
		virtual bool draw() = 0;
		virtual int prompt(unsigned int&, unsigned int&);
		virtual int turn() = 0;
		int play(); 

protected:
	struct game_piece {
		string display;
		string realDisplay;
	};

	int row;
	int col;

	vector<game_piece> finalGamePiece;
	game_piece emptyGamePiece;

	string whoWon;
	int totalPlayed;

	string Xsofar;
	string Osofar;

	unsigned int customBoard;
	int customWin;
	int customTotal;

	unsigned int maxLength; // max character length
};

class TicTacToeGame : public BaseGame {
	friend ostream& operator <<(ostream& out, const TicTacToeGame& game);

public:
	TicTacToeGame();
	virtual bool done(); 
	virtual bool draw(); 
	virtual int turn(); 

	void print(); 
};

class GomokuGame : public BaseGame {
	friend ostream& operator <<(ostream& out, const GomokuGame& game);
public:
	GomokuGame(); 
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	virtual int prompt(unsigned int&, unsigned int&);

	void print();
};

ostream& operator <<(ostream& out, const TicTacToeGame& game);

ostream& operator <<(ostream& out, const GomokuGame& game);
