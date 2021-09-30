// lab4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "game.h"
#include "Header.h"
using namespace std;

void usage(char* warning) {
	cout << "Usage Example: <" << warning << " TicTacToe> OR <" << warning << " Gomoku> OR <" << warning << " Gomoku 10 10>"<< endl;
}


int main(int argc, char* argv[])
{
	try {
		shared_ptr<BaseGame> sharedT(BaseGame::checkerOne(argc, argv));	

		//if the checkerOne function returns nullptr
		if (sharedT == nullptr) {
			usage(argv[success]);
			return invalid_initiation;
		}

		//if the checkerOne function returns pointer to the created object
		else {
			return sharedT->play();
		}
	}

	// catch for bad alloc
	catch (bad_alloc &ba){
		cout << "bad alloc caught: "<< ba.what() <<endl;
		return b_alloc;
	}
}
