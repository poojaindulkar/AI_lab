#include <iostream>
#include <vector>

using namespace std;

const int N = 8; 

// Function to check if placing a queen at (row, col) is safe
bool isSafe(vector<vector<int>>& board, int row, int col) {
    //queens in the same column
    for (int i = 0; i < row; ++i)
        if (board[i][col])
            return false;

    //  upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
        if (board[i][j])
            return false;

    // upper right diagonal
    for (int i = row, j = col; i >= 0 && j < N; --i, ++j)
        if (board[i][j])
            return false;

    return true;
}

bool solveNQueens(vector<vector<int>>& board, int row) {
    if (row == N) { // all queens are placed
        // Print the solution
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j)
                cout << board[i][j] << " ";
            cout << endl;
        }
        return true;
    }

    for (int col = 0; col < N; ++col) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1; // Place the queen

            // Recur to place rest of the queens
            if (solveNQueens(board, row + 1))
                return true;

            // If  doesn't lead to a solution, backtrack
            board[row][col] = 0;
        }
    }

    return false; 
}

int main() {
    vector<vector<int>> board(N, vector<int>(N, 0)); // Initialize chessboard

    if (!solveNQueens(board, 0)) {
        cout << "Solution does not exist.";
    }

    return 0;
}

