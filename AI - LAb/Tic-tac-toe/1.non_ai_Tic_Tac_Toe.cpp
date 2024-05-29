#include <iostream>
#include <string>

#define GRID_SIZE 9

using namespace std;

void printGame(char gameGrid[]);
void inputToSlot(char gameGrid[], int slot, char choice);
void initialiseGame(char gameGrid[]);
bool isFull(char gameGrid[]);
bool isEmpty(char input);
bool checkWon(char gameGrid[]);
bool rowWon(char gameGrid[]);
bool columnWon(char gameGrid[]);
bool diagonalWon(char gameGrid[]);

int main(int argc, const char * argv[])
{
    char gameGrid[GRID_SIZE];
    initialiseGame(gameGrid);
    int currentTurn = 0;

    cout << "Tic Tac Toe by Bryan Lean" << endl << endl;
    printGame(gameGrid);
    cout << endl;

    while (!isFull(gameGrid)) {
        int slotChoice;
        currentTurn += 1;
        bool isP2 (currentTurn % 2 == 0);

        // Prompt
        if (isP2) {
            cout << "Player 2 turn..." << endl << "Insert to slot > ";
        } else {
            cout << "Player 1 turn..." << endl << "Insert to slot > ";
        }
        cin >> slotChoice;

        while (!isEmpty(gameGrid[slotChoice])) {
            cout << "Slot occupied. Please select another slot > ";
            cin >> slotChoice;
        }

        // Insert
        if (isP2) {
            gameGrid[slotChoice] = 'o';
        } else {
            gameGrid[slotChoice] = 'x';
        }

        // Print
        printGame(gameGrid);
        cout << endl;

        // Check Winner
        if (checkWon(gameGrid)) {
            if (isP2) {
                cout << "Player 2 won the game.";
            } else {
                cout << "Player 1 won the game.";
            }

            break;
        } 

    }

    if (!checkWon(gameGrid)) {
        cout << "Draw.";
    }


}

void initialiseGame(char gameGrid[]) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        gameGrid[i] = ' ';
    }
}

void printGame(char gameGrid[]) {
    cout << "+---+---+---+" << endl;
    for (int i = 0; i < GRID_SIZE; ++i) {
        cout << "| " << gameGrid[i] << " ";
        if ((i+1) % 3 == 0 && i != 0) {
            cout << "|" << endl;
            cout << "+---+---+---+" << endl;
        }
    }
}

void inputToSlot(char gameGrid[], int slot, char choice) {
    gameGrid[slot] = choice;

}

bool isFull(char gameGrid[]) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        if (gameGrid[i] == ' ') {
            return false;
        }
    }

    return true;
}

bool isEmpty(char input) {
    if (input == ' '){
        return true;
    }
    return false;
}

bool checkWon(char gameGrid[]) {
    if (rowWon(gameGrid)) {
        return true;
    } else if (columnWon(gameGrid)) {
        return true;
    } else if (diagonalWon(gameGrid)) {
        return true;
    }

    return false;
}

bool rowWon(char gameGrid[]) {
    for (int i = 0; i < GRID_SIZE; i += 3) {
        char firstInRow = gameGrid[i];
        char secondInRow = gameGrid[i + 1];
        char thirdInRow = gameGrid[i + 2];

        if (!isEmpty(firstInRow) && !isEmpty(secondInRow) && !isEmpty(thirdInRow)) {
            if (firstInRow == secondInRow && firstInRow == thirdInRow) {
                return true;
            }
        }
    }

    return false;
}

bool columnWon(char gameGrid[]) {
    for (int i = 0; i < 3; ++i) {
        char firstInColumn = gameGrid[i];
        char secondInColumn = gameGrid[i + 3];
        char thirdInColumn = gameGrid[i + 6];

        if (!isEmpty(firstInColumn) && !isEmpty(secondInColumn) && !isEmpty(thirdInColumn)) {
            if (firstInColumn == secondInColumn && firstInColumn == thirdInColumn) {
                return true;
            }
        }

    }

    return false;
}

bool diagonalWon(char gameGrid[]) {
    char center = gameGrid[4];
    if (!isEmpty(center) && !isEmpty(gameGrid[0]) && !isEmpty(gameGrid[8])) {
        if (center == gameGrid[0] && center == gameGrid[8]) {
            return true;
        }
    } else if (!isEmpty(center) && !isEmpty(gameGrid[2]) && !isEmpty(gameGrid[6])) {
        if (center == gameGrid[2] && center == gameGrid[6]) {
            return true;
        }
    }

    return false;

}


/*
This C++ program is a simple implementation of the Tic Tac Toe game. Let's go through each part of the code:

Global Constants:

GRID_SIZE: Defines the size of the game grid, which is set to 9 for a 3x3 Tic Tac Toe board.
Function Declarations:

Several functions are declared with specific purposes, such as initializing the game, printing the game grid, handling user inputs, and checking for winning conditions.
Main Function (main()):

The main function initializes the game grid, prints the initial game state, and starts a loop to handle player turns until the game is over.
Inside the loop, it prompts the current player for their move, validates the input, updates the game grid, prints the updated game state, and checks for a winning condition or a draw.
Game Initialization (initialiseGame()):

Initializes the game grid with empty spaces.
Printing the Game Grid (printGame()):

Prints the current game state with the grid layout.
Player Input Validation (isEmpty()):

Checks if a slot in the game grid is empty.
Winning Condition Checks (checkWon(), rowWon(), columnWon(), diagonalWon()):

These functions check for winning conditions by examining rows, columns, and diagonals of the game grid.
Explanation:

The program provides a basic implementation of the Tic Tac Toe game where two players take turns marking empty spaces on a 3x3 grid.
It ensures that the game grid is correctly updated after each move and checks for winning conditions or a draw.
The winning conditions are determined by checking if any row, column, or diagonal has three consecutive marks by the same player.
Overall, the program demonstrates a simple but complete implementation of the classic Tic Tac Toe game in C++.
*/