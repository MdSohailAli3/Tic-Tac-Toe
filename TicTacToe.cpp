#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include<limits>

using namespace std;

class TicTacToe {
private:
    vector<char> board;
    int currentPlayer;

public:
    TicTacToe() : board(10) 
    {
        resetBoard();
        currentPlayer = 1; // Player 1 starts
    }

    void resetBoard() {
        for (int i = 1; i < 10; ++i) {
            board[i] = '0' + i; // Initialize board with numbers 1-9
        }
    }

    void drawBoard() {
        system("CLS");
        cout << "\n\t\t\t\t\t         |       |       ";
        cout << "\n\t\t\t\t\t     " << board[1] << "   |   " << board[2] << "   |   " << board[3];
        cout << "\n\t\t\t\t\t   ______|_______|_______";
        cout << "\n\t\t\t\t\t         |       |       ";
        cout << "\n\t\t\t\t\t     " << board[4] << "   |   " << board[5] << "   |   " << board[6];
        cout << "\n\t\t\t\t\t   ______|_______|_______";
        cout << "\n\t\t\t\t\t         |       |       ";
        cout << "\n\t\t\t\t\t     " << board[7] << "   |   " << board[8] << "   |   " << board[9];
        cout << "\n\t\t\t\t\t         |       |       \n";
    }

    bool isReserved(int choice) {
        return (board[choice] == 'X' || board[choice] == 'O');
    }

    void markBoard(char mark, int choice) {
        board[choice] = mark;
    }

    int checkWin() {
        // Check rows, columns, and diagonals
        for (int i = 1; i <= 9; i += 3) {
            if (board[i] == board[i + 1] && board[i + 1] == board[i + 2]) {
                return 1; // Win
            }
        }
        for (int i = 1; i <= 3; ++i) {
            if (board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
                return 1; // Win
            }
        }
        if (board[1] == board[5] && board[5] == board[9]) {
            return 1; // Win
        }
        if (board[3] == board[5] && board[5] == board[7]) {
            return 1; // Win
        }
        // Check for draw
        for (int i = 1; i <= 9; ++i) {
            if (board[i] != 'X' && board[i] != 'O') {
                return 7; // Game continues
            }
        }
        return 0; // Draw
    }

    void playGame() {
        while (true) {
            int choice;
            char mark = (currentPlayer % 2) ? 'X' : 'O';
            cout << "Player " << currentPlayer << " (" << mark << "), enter your choice: ";
            cin >> choice;
            
            // Check if the input is valid
            try{
              if (cin.fail()){
                 throw 1;
                }
            }
            catch(int x){    
               cin.clear(); // Clear the error state
               cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the invalid input
               cout << "\n!! Invalid input. Please enter a number between 1 and 9 !!\n" << endl;
               continue; // Ask for input again
            }

            if (choice < 1 || choice > 9 || isReserved(choice)) {
                cout << "\n!!INVALID MOVE! Try again.\n"<<endl;
                continue;
            }

            markBoard(mark, choice);
            drawBoard();

            int result = checkWin();
            if (result == 1) {
                cout << "PLAYER " << currentPlayer << " WINS!!!" << endl;
                break;
            } else if (result == 0) {
                cout << "\nGAME DRAW!" << endl;
                break;
            }

            currentPlayer = 3 - currentPlayer; // Switch player
        }

        char again;
        cout << "Do you want to play again? (y/n): ";
        cin >> again;
        
        if (tolower(again) == 'y') {
            resetBoard();
            drawBoard();
            playGame();
        }
    }
};

int main() {
    cout << "\n\t\t\t\t\t********TIC-TAC-TOE-GAME********\n\t\t\t\t\t\tFOR 2 PLAYERS\n\n\n";
    TicTacToe game;
    game.drawBoard();
    game.playGame();
    return 0;
}
