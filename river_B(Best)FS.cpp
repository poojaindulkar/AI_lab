#include <iostream>
#include <vector>
#include <queue>
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

struct CompareStates {
    bool operator()(const State& a, const State& b) const {
        // Heuristic: prioritize states with fewer missionaries and cannibals on the left bank
        return a.missionariesLeft + a.cannibalsLeft > b.missionariesLeft + b.cannibalsLeft;
    }
};

void printSolution(const std::vector<State>& solution) {
    for (const auto& state : solution) {
        std::cout << "Left: M" << state.missionariesLeft << " C" << state.cannibalsLeft
                  << " | Right: M" << state.missionariesRight << " C" << state.cannibalsRight
                  << " | Boat on " << (state.boatOnLeft ? "Left" : "Right") << " side\n";
    }
}

bool bestFirstSearch(State initialState) {
    std::priority_queue<State, std::vector<State>, CompareStates> pq;
    pq.push(initialState);

    while (!pq.empty()) {
        State currentState = pq.top();
        pq.pop();

        if (currentState.isGoal()) {
            // Reconstruct path
            std::vector<State> path;
            while (!pq.empty()) {
                path.push_back(currentState);
                currentState = pq.top();
                pq.pop();
            }
            path.push_back(initialState);
            std::reverse(path.begin(), path.end());

            printSolution(path);
            return true;
        }

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
            if (move.isValid()) {
                pq.push(move);
            }
        }
    }

    std::cout << "No solution found.\n";
    return false;
}

int main() {
    State initialState(3, 3, 0, 0, true);
    bestFirstSearch(initialState);
    return 0;
}
