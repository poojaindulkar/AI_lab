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

bool depthLimitedDFS(State currentState, std::vector<State>& path, int depthLimit) {
    if (currentState.isGoal()) {
        path.push_back(currentState);
        return true;
    }
    if (depthLimit <= 0) return false;

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
            path.push_back(currentState);
            if (depthLimitedDFS(move, path, depthLimit - 1)) return true;
            path.pop_back();
        }
    }
    return false;
}

void solveCannibalsMissionaries() {
    State initialState(3, 3, 0, 0, true);
    std::vector<State> path;
    int depthLimit = 20;  // Increase if necessary

    if (depthLimitedDFS(initialState, path, depthLimit)) {
        printSolution(path);
    } else {
        std::cout << "No solution found within depth limit.\n";
    }
}

int main() {
    solveCannibalsMissionaries();
    return 0;
}
