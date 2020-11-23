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
//updates the board as the game progresses
void updateBoard(bool& continue_game, int& player_counter, int& score_x, int& score_o, int& counter, int& number_of_ties) {
    //variable declaration and initialization
    string board[4][4] = { {"1", "2", "3", "4"},
                          {"5", "6", "7", "8"},
                          {"9", "10", "11", "12"},
                          {"13", "14", "15", "16"} };
    int desired_location;
    int row, col;
    string location_on_board;
    string symbol;
    bool valid_location = false;
    bool winner_determined = false, invalid_input = true, tie = false;
    char play_again = 'n';

    for (int i = 0; i < 16 && !winner_determined; i++) {
        //outputs updated board
        printBoard(board);
        //determines if the desired location is valid
        while (!valid_location) {
            cout << "Enter the number of the desired location (1-16): ";
            cin >> desired_location;
            if (desired_location >= 1 && desired_location <= 16 && checkLocation(board, desired_location, row, col)) {
                valid_location = true;
            }
            else {
                cout << "Wrong input. ";
            }
        }

        //if player counter is even, the first player will be player X, if not the first player will be player O
        //if the counter is even, the player to put down a symbol is the first player, if not the player to put down a symbol is the second player
        //updates board depending on the scenario
        if (player_counter % 2 == 0 && counter % 2 == 0) {
            board[row][col] = "X";
            symbol = "X";
        }
        else if (player_counter % 2 == 0 && counter % 2 == 1) {
            board[row][col] = "O";
            symbol = "O";
        }
        else if (player_counter % 2 == 1 && counter % 2 == 0) {
            board[row][col] = "O";
            symbol = "O";
        }
        else {
            board[row][col] = "X";
            symbol = "X";
        }
        //determines if there is a winner
        winner_determined = checkGameWon(board, symbol, score_x, score_o);

        //determines if there is a tie
        tie = checkGameTie(board, symbol, counter, winner_determined, number_of_ties);

        //options given after there is a winner
        if (winner_determined) {
            while (invalid_input) {
                cout << "Would you like to play again? (Y/N)" << endl;
                cin >> play_again;
                //if the players want to play again
                //restarts the game            
                if (play_again == 'Y' || play_again == 'y') {
                    continue_game = true;
                    invalid_input = false;
                }
                //if the players don't want to play again
                //prints the scores and the number of ties and then exits the program         
                else if (play_again == 'N' || play_again == 'n') {
                    continue_game = false;
                    invalid_input = false;
                    cout << "Number of Victories for Player X: " << score_x << endl;
                    cout << "Number of Victories for Player O: " << score_o << endl;
                    cout << "Number of Ties: " << number_of_ties << endl;
                    cout << "Game has ended. Thank you for playing! :)" << endl;
                    exit(0);
                }
            }
        }
        //options given if the game is tied
        if (tie) {
            printBoard(board);
            while (invalid_input) {
                cout << "This is tied! Play again? (Y/N)" << endl;
                cin >> play_again;
                //if the players want to play again
                //restarts the game            
                if (play_again == 'Y' || play_again == 'y') {
                    continue_game = true;
                    invalid_input = false;
                }
                //if the players don't want to play again
                //prints the scores and the number of ties and then exits the program   
                else if (play_again == 'N' || play_again == 'n') {
                    continue_game = false;
                    invalid_input = false;

                    cout << "Number of Victories for Player X: " << score_x << endl;
                    cout << "Number of Victories for Player O: " << score_o << endl;
                    cout << "Number of Ties: " << number_of_ties << endl;
                    cout << "Game has ended. Thank you for playing! :)" << endl;
                    exit(0);
                }
            }
        }
        //updates variables
        counter++;
        valid_location = false;
        invalid_input = true;
    } //end for loop

    //reset variables
    player_counter++;
    counter = 0;
}

//starts the game
void startGame() {
    //variable declaration and initialization
    bool continue_game = true;
    int score_x = 0, score_o = 0;
    int counter = 0, player_counter = 0;
    int number_of_ties = 0;

    //continues to play the game unless the user wants to end game
    while (continue_game) {
        updateBoard(continue_game, player_counter, score_x, score_o, counter, number_of_ties);
    }
}

int main()
{
    //calls function
    startGame();
}
