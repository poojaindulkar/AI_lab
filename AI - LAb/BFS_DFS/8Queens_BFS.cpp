#include <iostream>
#include <vector>
#include <queue>

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

// Breadth-First Search to solve the 8-Queens Problem
bool solveQueens(int n) {
    queue<State> q;
    q.push(State(n));

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        int row = 0; // The row to place the next queen

        // Find the next row without a queen
        while (row < n && current.queens[row] != -1) {
            ++row;
        }

        // If all queens are placed, print the solution
        if (row == n) {
            cout << "Solution:\n";
            printChessboard(current);
            return true;
        }

        // Try placing a queen in the current row at all possible positions
        for (int col = 0; col < n; ++col) {
            if (current.isSafe(row, col)) {
                State nextState = current;
                nextState.queens[row] = col;
                q.push(nextState);
            }
        }
    }

    // No solution found
    cout << "No solution found.\n";
    return false;
}

int main() {
    int n = 8; // Board size
    solveQueens(n);

    return 0;
}
