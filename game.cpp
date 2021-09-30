#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <string>
#include "game.h"
#include "Header.h"
#include <algorithm>
#include <iomanip>
using namespace std;

BaseGame* BaseGame::checkerOne(int temp1, char* temp2[]) { 
	if (temp1 > 1) {
	string s = temp2[1];
		//if argv[2] input is "TicTacToe" or "Gomoku"
		if (temp1 == 2) {
			if (s == "TicTacToe") {
				TicTacToeGame* game = new TicTacToeGame();

				return game; // game itself is a pointer variable that points at a dynamically allocated object
			}
			else if (s == "Gomoku") {
				//dynamically allocate the game object
				GomokuGame* game = new GomokuGame();

				//Since there is no additional argument that sets custom boardsize or custom win number, make default board(19x19 and 5 consecutive to win) win)
				game->customBoard = 19;
				game->customWin = 5;
				game->customTotal = game->customBoard * game->customBoard;
				//making empty game pieces
				for (int i = 1; i <= game->customTotal; i++) {
					game->finalGamePiece.push_back(game->emptyGamePiece);
				}
				return game;
			}
			else {
				//returns null ptr
				return nullptr;
			}
		}
		//extra credit - if user decided to change only the size of the custom game board, not winning piece number. 
		else if (temp1 == 3) {
			string c = temp2[2];
			int count = 0;

			//checks if it contains character other than number. 
			for (unsigned int k = 0; k < c.length(); k++) {
				if (!isdigit(c[k])) {
					count++;
				}
			}

			//if argv[3] is purely numbers. 
			if (count == 0) {
				stringstream cc(c);
				int ccc = 0;
				cc >> ccc;
				//since default winning move is 5, board size has to be bigger than 5. 
				if (ccc > 4) {
					GomokuGame* game = new GomokuGame();
					game->customBoard = ccc;
					game->customWin = 5;
					game->customTotal = game->customBoard * game->customBoard;
					for (int i = 1; i <= game->customTotal; i++) {
						game->finalGamePiece.push_back(game->emptyGamePiece);
					}
					return game;
				}
				else {
					return nullptr;
				}
			}
			else {
				return nullptr;
			}
		}
		//extra credit - if user decided to change both board size and number of winning game pieces. 
		else if (temp1 == 4 && s == "Gomoku") {
			string c = temp2[2];
			string v = temp2[3];
			int count = 0;

			for (unsigned int k = 0; k < c.length(); k++) {
				if (!isdigit(c[k])) {
						count++;
				}
			}

			//if string c only includes digits
			if (count == 0) {
				for (unsigned int k = 0; k < v.length(); k++) {
					//if string c only includes digits
					if (isdigit(v[k])) {
						GomokuGame* game = new GomokuGame();
						stringstream vv(v);
						stringstream cc(c);
						int ccc = 0;
						int vvv = 0;
						cc >> ccc;
						vv >> vvv;
						if (ccc > 2 && vvv > 2 && ccc >= vvv) {
							game->customBoard = ccc;
							game->customWin = vvv;
							game->customTotal = game->customBoard * game->customBoard;
							for (int i = 1; i <= game->customTotal; i++) {
								game->finalGamePiece.push_back(game->emptyGamePiece);
							}
							return game;
						}
						else {
							return nullptr;
						}

					}
					else {
						return nullptr;
					}
				}
			}
			else {
				return nullptr;
			}

		}
		else { 
			return nullptr;
		}

		return nullptr;
	}
	else {
		return nullptr;
	}
	
}

TicTacToeGame::TicTacToeGame() {
	//defining variables
	row = rowAndCol;
	col = rowAndCol;
	whoWon = "";
	totalPlayed = minIndex;
	Xsofar = " ";
	Osofar = " ";
	//making a emptyGamePiece with .display and .realDisplay value of " "
	emptyGamePiece.display = " ";
	emptyGamePiece.realDisplay = " ";
	int numOfPieces = rowAndCol * rowAndCol;
	maxLength = 0;

	//pushing a emptyGamePiece to vector
	for (int i = 0; i < numOfPieces; i++) {
		finalGamePiece.push_back(emptyGamePiece);
	};
}

GomokuGame::GomokuGame() {
	//defining variables
	row = gomokuRowAndCol;
	col = gomokuRowAndCol;
	whoWon = "";
	totalPlayed = minIndex;
	Xsofar = " ";
	Osofar = " ";
	//making a emptyGamePiece with .display and .realDisplay value of " "
	emptyGamePiece.display = " ";
	emptyGamePiece.realDisplay = " ";
	int numOfPieces = gomokuRowAndCol * gomokuRowAndCol;
	maxLength = 0;

	int customBoard =0;
	int customWin =0;

	int customTotal = customBoard * customBoard;
}

ostream& operator << (ostream& out, const TicTacToeGame& game) {
	int totalGamePieceNum = rowAndCol * rowAndCol;

	//prints out the gamepieces to console.
	for (int i = game.row - 1; i >= 0; i--) {
		//prints out the division line.
		out << i << "|";
		//actual print out of the gamepieces. 
		for (int j = 0; j < game.col; j++) {
			int index = i * game.col + j;
			out << setw(game.maxLength) <<game.finalGamePiece[index].realDisplay ;

		}
		out << endl;
	}

	//prints out a division line
	//out << " " << " ";
	//for (int i = game.row - 1; i >= 0; i--) {
	//	out << "-";
	//}
	//out << endl;

	//prints out guideline to show width index in a console.
	out << " " << " ";
	for (int i = 0; i < game.col; i++) {
		out << i << setw(game.maxLength);
	}

	return out;

}

ostream& operator << (ostream& out, const GomokuGame& game) {
	// number of total game pieces. 
	int totalGamePieceNum = game.customBoard * game.customBoard;


	for (int i = game.customBoard; i >= 1; i--) {
		//prints out index guide for row. 
		out << i;
		if (i < 10) {
			out << " ";
		}
		for (unsigned int j = 0; j < game.customBoard; j++) {
			int index = (i-1) * game.customBoard + j;
			//to get same size board. 
			if (j > 9) {
				//printing out "|" for better visibility and printing out pieces placed in board. 
				out << "| " << game.finalGamePiece[index].realDisplay;
			}
			else {
				out << "| " << game.finalGamePiece[index].realDisplay;
			}
		}
		cout << "|";
		out << endl;
	}
	

	out << "X";
	out << " ";
	//print out index guide for column
	for (unsigned int k = 1; k < game.customBoard+1; k++) {
		if (k < 11) {
			out << "  " << k;
		}
		else {
			out << " " << k;
		}
		
	}

	return out;
}

void TicTacToeGame::print() {
	cout << *this;
}

void GomokuGame::print() {
	cout << *this;
}

bool TicTacToeGame::done() {
	//X case
	//horizontal for x
	if (finalGamePiece[rowOneOne].display == "X" && finalGamePiece[rowOneTwo].display == "X" && finalGamePiece[rowOneThree].display == "X") {
		//to keep track which player won
		whoWon = "X";
		return true;
	}
	else if (finalGamePiece[rowTwoOne].display == "X" && finalGamePiece[rowTwoTwo].display == "X" && finalGamePiece[rowTwoThree].display == "X") {
		whoWon = "X";
		return true;
	}
	else if (finalGamePiece[rowThreeOne].display == "X" && finalGamePiece[rowThreeTwo].display == "X" && finalGamePiece[rowThreeThree].display == "X") {
		whoWon = "X";
		return true;
	}
	//vertical for x
	else if ((finalGamePiece[rowOneOne].display == "X" && finalGamePiece[rowTwoOne].display == "X" && finalGamePiece[rowThreeOne].display == "X")) {
		whoWon = "X";
		return true;
	}
	else if ((finalGamePiece[rowOneTwo].display == "X" && finalGamePiece[rowTwoTwo].display == "X" && finalGamePiece[rowThreeTwo].display == "X")) {
		whoWon = "X";
		return true;
	}
	else if ((finalGamePiece[rowOneThree].display == "X" && finalGamePiece[rowTwoThree].display == "X" && finalGamePiece[rowThreeThree].display == "X")) {
		whoWon = "X";
		return true;
	}
	//diagonal for x
	else if ((finalGamePiece[rowOneOne].display == "X" && finalGamePiece[rowTwoTwo].display == "X" && finalGamePiece[rowThreeThree].display == "X")) {
		whoWon = "X";
		return true;
	}
	else if (finalGamePiece[rowOneThree].display == "X" && finalGamePiece[rowTwoTwo].display == "X" && finalGamePiece[rowThreeOne].display == "X") {
		whoWon = "X";
		return true;
	}

	//Y case 
	//horizontal for x
	else if (finalGamePiece[rowOneOne].display == "O" && finalGamePiece[rowOneTwo].display == "O" && finalGamePiece[rowOneThree].display == "O") {
		whoWon = "O";
		return true;
	}
	else if (finalGamePiece[rowTwoOne].display == "O" && finalGamePiece[rowTwoTwo].display == "O" && finalGamePiece[rowTwoThree].display == "O") {
		whoWon = "O";
		return true;
	}
	else if (finalGamePiece[rowThreeOne].display == "O" && finalGamePiece[rowThreeTwo].display == "O" && finalGamePiece[rowThreeThree].display == "O") {
		whoWon = "O";
		return true;
	}
	//vertical for x
	else if ((finalGamePiece[rowOneOne].display == "O" && finalGamePiece[rowTwoOne].display == "O" && finalGamePiece[rowThreeOne].display == "O")) {
		whoWon = "O";
		return true;
	}
	else if ((finalGamePiece[rowOneTwo].display == "O" && finalGamePiece[rowTwoTwo].display == "O" && finalGamePiece[rowThreeTwo].display == "O")) {
		whoWon = "O";
		return true;
	}
	else if ((finalGamePiece[rowOneThree].display == "O" && finalGamePiece[rowTwoThree].display == "O" && finalGamePiece[rowThreeThree].display == "O")) {
		whoWon = "O";
		return true;
	}
	//diagonal for x
	else if ((finalGamePiece[rowOneOne].display == "O" && finalGamePiece[rowTwoTwo].display == "O" && finalGamePiece[rowThreeThree].display == "O")) {
		whoWon = "O";
		return true;
	}
	else if (finalGamePiece[rowOneThree].display == "O" && finalGamePiece[rowTwoTwo].display == "O" && finalGamePiece[rowThreeOne].display == "O") {
		whoWon = "O";
		return true;
	}

	//if no winner is found 
	else {
		return false;
	}

}

bool GomokuGame::done() {
	//checks if there is horizontal winning move in the board. 
	//checks from lower left to upper right
	for (unsigned int i = 0; i < customBoard; i++) {
		for (unsigned int j = 0; j < customBoard - customWin +1; j++) {
			int index = i * customBoard + j;

			int count = 0;

			if (finalGamePiece[index].realDisplay != " ") {
				for (int i = 1; i < customWin; i++) {
					if (finalGamePiece[index].realDisplay == finalGamePiece[index +i].realDisplay) {
						count++;
					}
				}

				if (count == customWin - 1) {
					if (finalGamePiece[index].realDisplay == "B") {
						whoWon = "Black";
					}
					else if (finalGamePiece[index].realDisplay == "W") {
						whoWon = "White";
					}
					return true;
				}		
			}
		}
	}
	//checks if there is vertical winning move in the board. 
	//checks from lower left to upper right
	for (unsigned int i = 0; i < customBoard - customWin + 1; i++) {
		for (unsigned int j = 0; j < customBoard; j++) {
			int index = i * customBoard + j;

			int count = 0;
			
			if (finalGamePiece[index].realDisplay != " ") {
				for (int i = 1; i < customWin; i++) {
					if (finalGamePiece[index].realDisplay == finalGamePiece[index + customBoard * i].realDisplay) {
						count++;
					}
				}

				if (count == customWin - 1) {
					if (finalGamePiece[index].realDisplay == "B") {
						whoWon = "Black";
					}
					else if (finalGamePiece[index].realDisplay == "W") {
						whoWon = "White";
					}
					return true;
				}
			}

		}
	}
	//checks if there is diagonal(from down to up) winning move in the board. 
	//checks from lower left to upper right
	for (unsigned int i = 0; i < customBoard - customWin + 1; i++) {
		for (unsigned int j = 0; j < customBoard - customWin + 1; j++) {
			int index = i * customBoard + j;

			int count = 0;

			if (finalGamePiece[index].realDisplay != " ") {
				for (int i = 1; i < customWin; i++) {
					if (finalGamePiece[index].realDisplay == finalGamePiece[index + (customBoard+1) * i].realDisplay) {
						count++;
					}
				}

				if (count == customWin - 1) {
					if (finalGamePiece[index].realDisplay == "B") {
						whoWon = "Black";
					}
					else if (finalGamePiece[index].realDisplay == "W") {
						whoWon = "White";
					}
					return true;
				}
			}

		}
	}
	//checks if there is diagonal(from up to down) winning move in the board. 
	//checks from upper left to lower right
	for (int i = customBoard-1; i > customWin -2; i--) {
		for (unsigned int j = 0; j < customBoard - customWin + 1; j++) {
			int index = i * customBoard + j;

			int count = 0;

			if (finalGamePiece[index].realDisplay != " ") {
				for (int i = 1; i < customWin; i++) {
					if (finalGamePiece[index].realDisplay == finalGamePiece[index - (customBoard - 1) * i].realDisplay) {
						count++;
					}
				}

				if (count == customWin - 1) {
					if (finalGamePiece[index].realDisplay == "B") {
						whoWon = "Black";
					}
					else if (finalGamePiece[index].realDisplay == "W") {
						whoWon = "White";
					}
					return true;
				}
			}

		}
	}
	return false;
}


bool TicTacToeGame::draw() {

	//If there are 9 turns played and no winner found till then, draw returns true
	if (totalPlayed == maxPlayedNum) {
		return true;
	}

	//when draw is not the case
	else if (done() == false || totalPlayed < 9) {
		return false;
	}
	else {
		return false;
	}
}

bool GomokuGame::draw() {

// cout << *this << endl; 

	GomokuGame blacktest = *this; // within this function scope
	GomokuGame whitetest = *this; // shallow copy
	int numOfPieces = customBoard * customBoard;

		//insert B and W into all of the empty pieces location in duplicated current board. 
		for (unsigned int i = 0; i < customBoard; i++) {
			for (unsigned int j = 0; j < customBoard; j++) {
				int index = i * customBoard + j;
				if (blacktest.finalGamePiece[index].realDisplay == " ") {
					blacktest.finalGamePiece[index].realDisplay = "B";
				}
			}
		}

		for (unsigned int i = 0; i < customBoard; i++) {
			for (unsigned int j = 0; j < customBoard; j++) {
				int index = i * customBoard + j;
				if (whitetest.finalGamePiece[index].realDisplay == " ") {
					whitetest.finalGamePiece[index].realDisplay = "W";
				}
			}
		}

		//check copied and filled board(blacktext filled with B and whitetest filled with W) with done() method. If one of the done returns true, it means that
		//at least one winning move remains. If both of the done() methods return false, it means that there are no winning move remain for both B and W, which means the 
		//game is draw. 
		if (blacktest.done() == true) {
			return false;
		}
		else if (whitetest.done() == true) {
			return false;
		}
		else {
			return true;
		}

}

int BaseGame::prompt(unsigned int& first, unsigned int& second) {

	string i;
	string firstVal;
	string secondVal;
	bool testing = false;

	while (testing == false) {
		//When move is successfully made, the program does +1 to totalPlayed. if totalPlayed % 2 == 0, it means that it is player X's turn.
		if (totalPlayed % 2 == 0) {
			cout << endl;
			cout << "Player X's turn (type quit to quit the game)" << endl;
		}
		else if (totalPlayed % 2 == 1) {
			cout << endl;
			cout << "Player O's turn (type quit to quit the game)" << endl;
		}

		//Grabs user input and put it to string i
		string t;
		getline(cin, t);

		int spaceCount = 0;
		for (unsigned int v = 0; v < t.length(); v++) {
			if (t[v] == ' ') {
				spaceCount++;
			}
		}

		if (spaceCount == 0) {
			i = t;
		}

		if (i == "quit") {
			return didQuit;
		}
		//if the input is not "quit" and has three
		else if (i != "quit" && i.size() == 3 && i != "") {
			int count = 0;

			//replace "," with " "
			replace(i.begin(), i.end(), ',', ' ');

			for (unsigned int k = 0; k < i.length(); k++) {
				if (isdigit(i[k])) {
					count++;
				}
			}

			//check if there is two digits
			if (count == 2) {

				//wrap it in istringstream
				istringstream iss(i);

				iss >> first;
				iss >> second;

				//coordinate bigger than 3 filtering
				if (first < 4 && second < 4) {
					testing = true;
				}
				//printing out of range message
				else {
					cout << "Coordinates out of range!" << endl;
					cout << "Correct Usage Example : 3,2 (Only cooardinates from 1 to 3 are available)" << endl;
				}

			}
			//printing out incorrect coordinate message
			else {
				cout << "!Please enter correct coordinates!" << endl;
				cout << "Correct Usage Example : 3,2 (Only cooardinates from 1 to 3 are available)" << endl;
			}
		}
		else {
			cout << "!Please enter correct coordinates!" << endl;
			cout << "Correct Usage Example : 3,2 (Only cooardinates from 1 to 3 are available)" << endl;
		}

	}
	return success;
}


int GomokuGame::prompt(unsigned int& first, unsigned int& second) {
	bool testing = false;
	string i;

	//until testing becomes true
	while (testing == false) {
		//check turn and let users know who's turn it is
		if (totalPlayed % 2 == 0) {
			cout << endl;
			cout << "Black's turn (type quit to quit the game)" << endl;
		}
		else if (totalPlayed % 2 == 1) {
			cout << endl;
			cout << "White's turn (type quit to quit the game)" << endl;
		}

		//getting input (coordinate) from user. 
		string t;
		getline(cin,t);

		int spaceCount = 0;
		//checking whitespace from user input (cin)
		for (unsigned int v = 0; v < t.length(); v++) {
			if (t[v] == ' ') {
				spaceCount++;
			}
		}

		if (spaceCount == 0) {
			i = t;
		}


		if (i == "quit") {
			return didQuit;
		}
		else {
			//check if input is greater than 3 and is not an empty string ("")
			if (i.length() < 3 || i.length() > 5 || i == "") {
				cout << "Please enter a valid coordinate. Correct Usage: 5,5" << endl;
			}
			else {
				int count = 0;
				int commaCount = 0;

				for (unsigned int k = 0; k < i.length(); k++) {
					if (i[k] == ',') {
						commaCount++;
					}
				}
				//if there are more than 1 comma
				if (commaCount != 1) {
					cout << "Please enter a valid coordinate. Correct Usage: 5,5" << endl;
				}
				else {
					//replace comma to ' '
					replace(i.begin(), i.end(), ',', ' ');

					//check if there is alphabet or things other than digit
					for (unsigned int k = 0; k < i.length(); k++) {
						if (!isdigit(i[k])) {
							if (i[k] != ' ') {
								count++;
							}
						}
					}

					//if the string contains character other than digits and " "(space).
					if (count != 0) {
						cout << "Please enter a valid coordinate. Correct Usage: 5,5"<<endl;
					}
					else {
						istringstream iss(i);

						iss >> first;
						iss >> second;

						//we do -1 here since our coordinate starts from 0.
						first = first - 1;
						second = second - 1;

						// if users try to input coordinate out of the range. 
						if (first < 0 || first > customBoard-1 || second < 0 || second > customBoard-1) {
							cout << "Please enter a valid coordinate." << endl;
						}
						else {
							testing = true;
						}
					}
				}
			}
		}

	}
	return success;
}

int TicTacToeGame::turn() {

	bool testing = false;

	while (testing == false) {
		unsigned int one = 0;
		unsigned int two = 0;

		int callPrompt = prompt(one, two);
		//calling prompt repeatidely until it spits out success
		while (callPrompt != success) {
			if (callPrompt == didQuit) {
				return didQuit;
			}
		}
		//check if input coordinate is out of range
		if (one != 0 && one != 4 && two != 0 && two != 4) {
			//index formula
			int checkIndex = rowAndCol * two + one;

			string getFinalGamePiece = finalGamePiece[checkIndex].display;

			//check if the spot is taken. 
			if (getFinalGamePiece == " ") {
				if (totalPlayed % 2 == 0) {
					finalGamePiece[checkIndex].display = "X";

					finalGamePiece[checkIndex].realDisplay = "X";
					//setting max length for longer display
					if (maxLength == 0) {
						for (unsigned int i = 0; i < finalGamePiece[checkIndex].realDisplay.length(); i++) {
							
							maxLength++;
						}
					}


					//incremention total played number since the input is valid & move has made
					totalPlayed++;

					//convert x coordinate and y coordinate int to string, and then append it to string that class holds for printing out previous moves.  
					string a = to_string(one);
					string b = to_string(two);
					Xsofar.append(a);
					Xsofar.append(", ");
					Xsofar.append(b);
					Xsofar.append("; ");

					testing = true;
				}
				else {
					finalGamePiece[checkIndex].display = "O";

					finalGamePiece[checkIndex].realDisplay = "O";
					//setting max length for longer display
					if (maxLength < finalGamePiece[checkIndex].realDisplay.length()) {
						for (unsigned int i = 0; i < finalGamePiece[checkIndex].realDisplay.length(); i++) {

							maxLength++;
						}
					}


					//same as above
					totalPlayed++;

					string a = to_string(one);
					string b = to_string(two);
					Osofar.append(a);
					Osofar.append(", ");
					Osofar.append(b);
					Osofar.append("; ");

					testing = true;
				}
			}
			//if spot is already taken
			else {
				cout << "The spot is already taken" << endl;
			}
		}
		else {
			cout << "!Please enter correct coordinates!" << endl;
			cout << "Correct Usage Example : 3,2 (Only cooardinates from 1 to 3 are available)" << endl;
		}
	}

	TicTacToeGame game;
	cout << endl;
	//printing out board using insertion operator defined above
	cout << *this << endl;
	cout << endl;

	//print out player's log depends on the turn
	if (totalPlayed % 2 == 0) {
		cout << "Player O:" << Osofar << endl;
	}
	else {
		cout << "Player X:" << Xsofar << endl;
	}
	cout << endl;

	return success;

}

int GomokuGame::turn() {
	bool testing = false;

	while (testing == false) {
		unsigned int one = 0;
		unsigned int two = 0;

		int callPrompt = prompt(one, two);

		//calling prompt repeatidely until it spits out success
		while (callPrompt != success) {
			if (callPrompt == didQuit) {
				return didQuit;
			}
		}

		int finalIndex = customBoard * two + one;

		//checks if the spot is already taken. 
		if (finalGamePiece[finalIndex].realDisplay != " ") {
			cout << "The spot is already taken" << endl;
		}

		//same as TicTacToeGame::turn()
		else {
			if (totalPlayed % 2 == 0) {
				finalGamePiece[finalIndex].realDisplay = "B";

				totalPlayed++;

				string a = to_string(one + 1);
				string b = to_string(two + 1);
				Xsofar.append(a);
				Xsofar.append(", ");
				Xsofar.append(b);
				Xsofar.append("; ");

				testing = true;
			}
			else if (totalPlayed % 2 == 1) {
				finalGamePiece[finalIndex].realDisplay = "W";

				totalPlayed++;

				string a = to_string(one + 1);
				string b = to_string(two + 1);
				Osofar.append(a);
				Osofar.append(", ");
				Osofar.append(b);
				Osofar.append("; ");

				testing = true;
			}
		}
	}
	print();

	//prints out all moves
	if (totalPlayed % 2 == 0) {
		cout << endl;
		cout << "White:" << Osofar << endl;
	}
	else if (totalPlayed % 2 == 1) {
		cout << endl;
		cout << "Black:" << Xsofar << endl;
	}
	cout << endl;

	return success;
}

int BaseGame::play() {
	//printing out board
	print();

	//keep calling turn() until done() and draw() return true, which means game ended
	while (done() == false && draw() == false) {
		//calling turn() and check if it returns unique quit value
		if (turn() == didQuit) {
			cout << "Game quitted: " << totalPlayed << " turns played." << endl;
			return didQuit;
		}
	}

	//if done() is true, then it prints out who won and returns unique success value
	if (done() == true) {
		cout << "Player " << whoWon << " won the game!" << endl;
		return success;
		//if draw() is true, then it prints out total turn played and return unique draw return value
	}
	else if (draw() == true) {
		cout << "Draw: " << totalPlayed << " turns played." << " No more move remains" << endl;
		return didDraw;
	}
	//returns success when done() is true, which means game ended with winner
	return success;
}
