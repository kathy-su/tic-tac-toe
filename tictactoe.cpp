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
