#include <iostream>
#include <vector>

using namespace std;

// Function to check if a queen can be placed at a given position
bool isSafe(int row, int col, const vector<int>& board) {
    for (int i = 0; i < row; ++i) {
        // Check if there is a queen in the same column or diagonal
        if (board[i] == col || abs(board[i] - col) == row - i) {
            return false;
        }
    }
    return true;
}

// Recursive function to solve N-Queens using backtracking
bool solveNQueens(int row, int n, vector<int>& board) {
    if (row == n) {
        // All queens are successfully placed
        return true;
    }

    for (int col = 0; col < n; ++col) {
        if (isSafe(row, col, board)) {
            // Place the queen at this position
            board[row] = col;

            // Recur to place the rest of the queens
            if (solveNQueens(row + 1, n, board)) {
                return true;
            }

            // If placing queen at board[row][col] doesn't lead to a solution
            // then remove queen from board[row][col]
            board[row] = -1;
        }
    }
    // No solution exists for this configuration
    return false;
}

// Function to print the N-Queens board
void printBoard(const vector<int>& board) {
    int n = board.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (board[i] == j) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of queens (N): ";
    cin >> n;

    vector<int> board(n, -1); // Initialize the board with -1

    if (solveNQueens(0, n, board)) {
        cout << "Solution found:\n";
        printBoard(board);
    } else {
        cout << "No solution exists for N = " << n << endl;
    }

    return 0;
}
