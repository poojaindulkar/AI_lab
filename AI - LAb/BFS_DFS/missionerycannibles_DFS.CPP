#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

struct State {
    int missionariesLeft;
    int cannibalsLeft;
    int boat; // 1 for left, 0 for right
    int missionariesRight;
    int cannibalsRight;
    
    bool operator<(const State& other) const {
        if (missionariesLeft != other.missionariesLeft)
            return missionariesLeft < other.missionariesLeft;
        if (cannibalsLeft != other.cannibalsLeft)
            return cannibalsLeft < other.cannibalsLeft;
        if (boat != other.boat)
            return boat < other.boat;
        if (missionariesRight != other.missionariesRight)
            return missionariesRight < other.missionariesRight;
        return cannibalsRight < other.cannibalsRight;
    }
};

bool isValid(int missionaries, int cannibals) {
    if (missionaries < 0 || cannibals < 0) return false;
    if (missionaries > 3 || cannibals > 3) return false;
    if (missionaries < cannibals && missionaries > 0) return false;
    if (3 - missionaries < 3 - cannibals && 3 - missionaries > 0) return false;
    return true;
}


bool isStateValid(const State& state) {
    return isValid(state.missionariesLeft, state.cannibalsLeft) &&
           isValid(state.missionariesRight, state.cannibalsRight);
}


bool isStateGoal(const State& state) {
    return (state.missionariesLeft==0 && state.cannibalsLeft==0) &&
           (state.missionariesRight==3 && state.cannibalsRight==3) &&
           state.boat == 0;
}
void printState(const State& state) {
    cout << "(" << state.missionariesLeft << "," << state.cannibalsLeft << ")";
    cout << " - " << (state.boat ? "Left" : "Right") << " - ";
    cout << "(" << state.missionariesRight << "," << state.cannibalsRight << ")" << endl;
}

bool dfs(State& currentState, set<State>& explored, vector<State>& path) {
    path.push_back(currentState);
    explored.insert(currentState);

    if (isStateGoal(currentState)) {
        return true;
    }

    for (int i = 0; i <= 2; ++i) {
        for (int j = 0; j <= 2; ++j) {
            if (i + j >= 1 && i + j <= 2) {
                State nextState;
                if (currentState.boat == 1) {
                    nextState = {currentState.missionariesLeft - i,
                                 currentState.cannibalsLeft - j,
                                 0,
                                 currentState.missionariesRight + i,
                                 currentState.cannibalsRight + j};
                } else {
                    nextState = {currentState.missionariesLeft + i,
                                 currentState.cannibalsLeft + j,
                                 1,
                                 currentState.missionariesRight - i,
                                 currentState.cannibalsRight - j};
                }
                if (isStateValid(nextState) && explored.find(nextState) == explored.end()) {
                    if (dfs(nextState, explored, path)) {
                        return true;
                    }
                }
            }
        }
    }

    path.pop_back(); // If no valid path found, backtrack
    return false;
}

vector<State> solve() {
    set<State> explored;
    vector<State> path;
    State initialState = {3, 3, 1, 0, 0};
    
    if (dfs(initialState, explored, path)) {
        cout << "Solution Path:" << endl;
        for (const auto& state : path) {
            printState(state);
        }
        return path;
    } else {
        cout << "No solution found!" << endl;
        return {};
    }
}

int main() {
    solve();
    return 0;
}
