#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>  // For std::find

struct State {
    int missionariesLeft;
    int cannibalsLeft;
    int missionariesRight;
    int cannibalsRight;
    bool boatOnLeft;

    State(int ml, int cl, int mr, int cr, bool boat) :
        missionariesLeft(ml), cannibalsLeft(cl), missionariesRight(mr), cannibalsRight(cr), boatOnLeft(boat) {}

    bool isGoal() const {
        return missionariesLeft == 0 && cannibalsLeft == 0;
    }

    bool isValid() const {
        if (missionariesLeft < 0 || missionariesRight < 0 || cannibalsLeft < 0 || cannibalsRight < 0)
            return false;
        if ((missionariesLeft > 0 && missionariesLeft < cannibalsLeft) ||
            (missionariesRight > 0 && missionariesRight < cannibalsRight))
            return false;
        return true;
    }

    bool operator==(const State& other) const {
        return missionariesLeft == other.missionariesLeft &&
               cannibalsLeft == other.cannibalsLeft &&
               missionariesRight == other.missionariesRight &&
               cannibalsRight == other.cannibalsRight &&
               boatOnLeft == other.boatOnLeft;
    }
};

void printSolution(const std::vector<State>& solution) {
    for (const auto& state : solution) {
        std::cout << "Left: M" << state.missionariesLeft << " C" << state.cannibalsLeft
                  << " | Right: M" << state.missionariesRight << " C" << state.cannibalsRight
                  << " | Boat on " << (state.boatOnLeft ? "Left" : "Right") << " side\n";
    }
}

bool iterativeDFS(State initialState) {
    std::stack<std::pair<State, std::vector<State>>> stack;
    stack.push({initialState, {}});

    while (!stack.empty()) {
        auto [currentState, path] = stack.top();
        stack.pop();

        if (currentState.isGoal()) {
            path.push_back(currentState);
            printSolution(path);
            return true;
        }

        if (std::find(path.begin(), path.end(), currentState) != path.end())
            continue;

        path.push_back(currentState);

        std::vector<State> possibleMoves;
        if (currentState.boatOnLeft) {
            possibleMoves.push_back(State(currentState.missionariesLeft - 2, currentState.cannibalsLeft, currentState.missionariesRight + 2, currentState.cannibalsRight, false));
            possibleMoves.push_back(State(currentState.missionariesLeft, currentState.cannibalsLeft - 2, currentState.missionariesRight, currentState.cannibalsRight + 2, false));
            possibleMoves.push_back(State(currentState.missionariesLeft - 1, currentState.cannibalsLeft - 1, currentState.missionariesRight + 1, currentState.cannibalsRight + 1, false));
            possibleMoves.push_back(State(currentState.missionariesLeft - 1, currentState.cannibalsLeft, currentState.missionariesRight + 1, currentState.cannibalsRight, false));
            possibleMoves.push_back(State(currentState.missionariesLeft, currentState.cannibalsLeft - 1, currentState.missionariesRight, currentState.cannibalsRight + 1, false));
        } else {
            possibleMoves.push_back(State(currentState.missionariesLeft + 2, currentState.cannibalsLeft, currentState.missionariesRight - 2, currentState.cannibalsRight, true));
            possibleMoves.push_back(State(currentState.missionariesLeft, currentState.cannibalsLeft + 2, currentState.missionariesRight, currentState.cannibalsRight - 2, true));
            possibleMoves.push_back(State(currentState.missionariesLeft + 1, currentState.cannibalsLeft + 1, currentState.missionariesRight - 1, currentState.cannibalsRight - 1, true));
            possibleMoves.push_back(State(currentState.missionariesLeft + 1, currentState.cannibalsLeft, currentState.missionariesRight - 1, currentState.cannibalsRight, true));
            possibleMoves.push_back(State(currentState.missionariesLeft, currentState.cannibalsLeft + 1, currentState.missionariesRight, currentState.cannibalsRight - 1, true));
        }

        for (const auto& move : possibleMoves) {
            if (move.isValid() && std::find(path.begin(), path.end(), move) == path.end()) {
                stack.push({move, path});
            }
        }
    }

    std::cout << "No solution found.\n";
    return false;
}

int main() {
    State initialState(3, 3, 0, 0, true);
    iterativeDFS(initialState);
    return 0;
}
/*This C++ code implements the Cannibals and Missionaries problem using an Iterative Depth-First Search (DFS) algorithm. Let's break down the code and discuss the theory behind it:

Header inclusion:

The code includes necessary header files for input-output operations (iostream) and data structures (vector, stack, algorithm).
State Representation (Struct State):

The State struct represents a state in the Cannibals and Missionaries problem. It includes attributes such as the number of missionaries and cannibals on each side of the river, the boat's position, and methods to check whether the state is a goal state and whether it's valid.
Printing Solution (printSolution):

The printSolution function prints the sequence of states leading to a solution.
Iterative Depth-First Search (iterativeDFS):

The iterativeDFS function performs an iterative depth-first search to find a solution to the problem.
It uses a stack to keep track of states to be explored and their respective paths.
At each iteration, it pops a state from the stack, checks if it's a goal state, and if not, generates possible moves and adds them to the stack if they are valid and not already visited in the current path.
Main Function (main):

In the main function, an initial state is created with three missionaries and three cannibals on the left side of the river and the boat on the left side.
The iterativeDFS function is called with the initial state to find a solution.
Theory Behind the Approach:

Depth-First Search (DFS): DFS is a search algorithm that explores as far as possible along a branch before backtracking. In this code, DFS is used to explore the state space of the problem, moving from one state to another until a goal state is reached.

Iterative Approach: Instead of a recursive implementation of DFS, this code uses an iterative approach to handle deep recursion levels that may occur in larger problem instances. It uses a stack to simulate the recursive calls of the DFS algorithm.

State Representation and Validity Checking: Each state is represented by the State struct, which encapsulates the state's attributes and methods to check its validity and whether it's a goal state. This representation allows efficient exploration of the state space while ensuring that only valid states are considered.

Backtracking: If the algorithm encounters a dead-end (i.e., no valid moves from a state), it backtracks by popping states from the stack until a state with unexplored moves is found.

Overall, the code efficiently explores the state space of the Cannibals and Missionaries problem using an iterative DFS algorithm, ensuring that only valid states are considered in the search process.





*/