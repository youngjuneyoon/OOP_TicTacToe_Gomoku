Lab 4 
Group Member: YJ Yoon 
     Kon Yoo
Group Name: Groovyroom

Error:

1)
game.cpp line 15 - 17

Before casting temp2[1] (argv[1] input) as string type, as we now did in game.cpp line 15 (string s = temp2[1];),
we encountered a cmd error that returns _ instead of printing out game board.

2) 
game.cpp line 604

1>H:\konyoo-cse332\labs-yook0530\lab4-groovyroom\lab4\game.cpp(604,30): warning C4018:  '>': signed/unsigned mismatch
1>H:\konyoo-cse332\labs-yook0530\lab4-groovyroom\lab4\game.cpp(604,70): warning C4018:  '>': signed/unsigned mismatch

While we were working on extra credit portion, we creatd three new integer variables in baseclass: 
int customBoard;
int customWin;
int customTotal;

in line 604, because unsigned int& first and unsigned int& second were mismatched with int customBoard.
Thus, we changed customBoard into unsigned int to resolve the mismatch.


Test Cases:

1) lab4.exe TicTacToe

As we intended, TicTacToe game was printed in command line 

2) lab4.exe TicTacToe 111

It returned the usage message indicating that input is invalid 

3) lab4.exe tictactoe

Case sensitive. It returned error and printed the usage message indicating that input is invalid

4) lab4.exe Gomoku

As we intended, Gomoku game was printed in command line with the number of connecting pieces to win: 5

5) lab4.exe gomoku

Case sensitive. It returned error and printed the usage message indicating that input is invalid


Extra Credit:

1) lab4.exe Gomoku

Gomoku game with default condition, 19 x 19 game board and the number of connecting pieces to win: 5, was printed 

2) lab4.exe Gomoku 3

We implemented one additional argument case to return error when the board is smaller than 5, taking 3 as input returned
the usage message indicating that input is invalid

3) lab4.exe Gomoku  3 3

The input printed Gomoku game with game board size 3 x 3 and the number of connecting pieces to win: 5

4) lab4.exe Gomoku -1 3

Because negative value cannot be a board size of Gomoku game, the input returned error and printed the usage message indicating that input is invalid

5) lab4.exe Gomoku 5 6

Because the number of connecting pieces to win should always be smaller than or equal to the board size.
The input returned error and printed the usage message indicating that input is invalid

6) lab4.exe Gomoku 50 50

As we intended, the input printed Gomoku game with board size 50 x 50 and the number of connecting pieces to win: 5

7) lab4.exe Gomoku 10,10

Because we take in input as two int values without any special characters, the input returend error and
printed the usage message indicating that input is invalid