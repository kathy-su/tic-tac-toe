#include <iostream>
#include <string>
#include <array>
#include <sstream>
using namespace std;

//printing out the display board
void printBoard(string board[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << board[i][j] << "\t";
        }
        cout << "" << endl;
    }
}

//case when winning with 4 in diagonal
bool checkDiagonal(string board[4][4], string symbol) {
    //check if every value in a diagonal is the same symbol
    for (int i = 0; i < 4; i++) {
        //first diagonal possibility from top left to bottom right
        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[2][2] == board[3][3]) {
            return true;
        }
        //second diagonal possibility from top right to bottom left
        if (board[0][3] == board[1][2] && board[1][2] == board[2][1] && board[2][1] == board[3][0]) {
            return true;
        }
    }
    return false;
}

//case when winning with 4 in a vertical pattern
bool checkVertical(string board[4][4], string symbol) {
    //check if every value in the column is the same symbol
    for (int i = 0; i < 4; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[2][i] == board[3][i]) {
            return true;
        }
    }
    return false;
}

//case when winning with 4 in a horizontal pattern
bool checkHorizontal(string board[4][4], string symbol) {
    //check if every value in a row is the same symbol
    for (int i = 0; i < 4; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] == board[i][3]) {
            return true;
        }
    }
    return false;
}
//check if the location is already occupied on the board
bool checkLocation(string board[4][4], int& desired_location, int& row, int& col) {
    //initializing variable
    int location_on_board;
    //checking location
    //goes through every location on the board to see if the value equals to the user input
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            //converting integer to string
            istringstream(board[i][j]) >> location_on_board;
            //if value equals to the user input, the saves the row and the column location
            if (location_on_board == desired_location) {
                row = i;
                col = j;
                return true;
            }
        }
    }
    return false;
}

//keeps track of the scores for Player X and Player O
//sees which player won the game 
bool checkGameWon(string board[4][4], string symbol, int& score_x, int& score_o) {
    //checking the vertical way of winning
    //adding score count to the winner (either Player X or Player O)
    if (checkVertical(board, symbol)) {
        if (symbol == "X") {
            score_x++;
        }
        else {
            score_o++;
        }
        printBoard(board);
        cout << symbol << " is the Winner! Congrats!" << endl;
        return true;
    }
    //checking the horizontal way of winning
    //adding score count to the winner (either Player X or Player O)
    else if (checkHorizontal(board, symbol)) {
        if (symbol == "X") {
            score_x++;
        }
        else {
            score_o++;
        }
        printBoard(board);
        cout << symbol << " is the Winner! Congrats!" << endl;
        return true;
    }
    //checking the diagonal way of winning
    //adding score count to the winner (either Player X or Player O)
    else if (checkDiagonal(board, symbol)) {
        if (symbol == "X") {
            score_x++;
        }
        else {
            score_o++;
        }
        cout << symbol << " is the Winner! Congrats!" << endl;
        return true;
    }
    return false;
}
//checks when the game is tied and updates the number of ties
bool checkGameTie(string board[4][4], string symbol, int counter, bool winner_determined, int& number_of_ties) {
    if (counter == 15 && !winner_determined) {
        number_of_ties++;
        return true;
    }
    return false;
}
