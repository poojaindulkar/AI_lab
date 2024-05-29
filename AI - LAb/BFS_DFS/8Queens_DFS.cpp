#include <iostream>
#include <vector>

using namespace std;

// Structure to represent a state in the search space
struct State {
    vector<int> queens; // Column positions of queens in each row

    State(int n) : queens(n, -1) {}

    // Check if placing a queen at (row, col) is safe
    bool isSafe(int row, int col) const {
        for (int prevRow = 0; prevRow < row; ++prevRow) {
            int prevCol = queens[prevRow];

            // Check if the queen in the previous row attacks the current position
            if (prevCol == col || abs(prevCol - col) == abs(prevRow - row)) {
                return false;
            }
        }

        return true;
    }
};

// Function to print the chessboard
void printChessboard(const State& state) {
    for (int row = 0; row < state.queens.size(); ++row) {
        for (int col = 0; col < state.queens.size(); ++col) {
            if (state.queens[row] == col) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

// Depth-First Search to solve the 8-Queens Problem
bool dfs(int row, int n, State& current) {
    // If all queens are placed, print the solution
    if (row == n) {
        cout << "Solution:\n";
        printChessboard(current);
        return true;
    }

    // Try placing a queen in the current row at all possible positions
    for (int col = 0; col < n; ++col) {
        if (current.isSafe(row, col)) {
            current.queens[row] = col;

            // Recursively try placing queens in the next row
            if (dfs(row + 1, n, current)) {
                return true;
            }

            // Backtrack if placing a queen at (row, col) doesn't lead to a solution
            current.queens[row] = -1;
        }
    }

    // No solution found for the current configuration
    return false;
}

int main() {
    int n = 8; // Board size
    State initial(n);

    if (!dfs(0, n, initial)) {
        cout << "No solution found.\n";
    }

    return 0;
}
