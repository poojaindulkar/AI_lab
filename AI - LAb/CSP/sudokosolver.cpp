#include <iostream>
#include <vector>
using namespace std;

class SudokuSolver {
public:
    void solveBoard(vector<vector<int>>& board) {
        if (solve(board)) {
            printBoard(board);
        } else {
            cout << "No solution exists." << endl;
        }
    }

    bool solve(vector<vector<int>>& board) {  //O((n^2)^(n∗n)).
        vector<int> emptyCell = findEmptyCell(board);
        int row = emptyCell[0];
        int col = emptyCell[1];

        // If no empty cell is found, the board is solved
        if (row == -1 && col == -1) {
            return true;
        }

        for (int num = 1; num <= 9; num++) {
            if (isValid(board, row, col, num)) {
                board[row][col] = num;

                // Recursive call to solve the next empty cell
                if (solve(board)) {
                    return true;
                }

                // Backtrack if the current solution doesn't lead to a solution
                board[row][col] = 0;
            }
        }

        // No valid number found for the current empty cell
        return false;
    }

    vector<int> findEmptyCell(vector<vector<int>>& board) {
        vector<int> coordinates = { -1, -1 }; // Default value for row and column

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == 0) {
                    coordinates[0] = i; // Row index
                    coordinates[1] = j; // Column index
                    return coordinates;
                }
            }
        }
        return coordinates; // If no empty cell found, return default values
    }

    bool isValidRow(vector<vector<int>>& board, int row, int num) {
        for (int i = 0; i < 9; i++) {
            if (board[row][i] == num) {
                return false;
            }
        }
        return true;
    }

    bool isValidCol(vector<vector<int>>& board, int col, int num) {
        for (int j = 0; j < 9; j++) {
            if (board[j][col] == num) {
                return false;
            }
        }
        return true;
    }

    bool isValidBox(vector<vector<int>>& board, int startRow, int startCol, int num) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i + startRow][j + startCol] == num) {
                    return false;
                }
            }
        }
        return true;
    }

    bool isValid(vector<vector<int>>& board, int row, int col, int num) {
        return isValidRow(board, row, num) && isValidCol(board, col, num)
                && isValidBox(board, row - row % 3, col - col % 3, num);
    }

    void printBoard(vector<vector<int>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    // Example of how to use the solveBoard method
    vector<vector<int>> sudoku_board = {
        { 0, 0, 0, 0, 0, 0, 1, 0, 7 },
        { 8, 9, 0, 0, 0, 0, 0, 2, 0 },
        { 0, 0, 0, 0, 2, 0, 9, 0, 0 },
        { 0, 7, 0, 0, 9, 0, 0, 4, 0 },
        { 0, 0, 0, 2, 8, 0, 5, 9, 1 },
        { 0, 0, 0, 4, 0, 0, 0, 0, 0 },
        { 2, 0, 0, 0, 0, 4, 0, 0, 8 },
        { 0, 8, 0, 3, 5, 0, 0, 0, 0 },
        { 0, 4, 7, 0, 1, 0, 3, 0, 0 }
    };

    SudokuSolver sudokuSolver;
    cout << "-------------------Solve the Sudoku Problem---------------------" << endl;
    cout << "--------------------------Question------------------------------" << endl;
    sudokuSolver.printBoard(sudoku_board);
    cout << "---------------------Solved Board-------------------------" << endl;
    sudokuSolver.solveBoard(sudoku_board);

    return 0;
}