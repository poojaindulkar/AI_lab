#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <tuple>

using namespace std;

struct State {
    int missionaries;
    int cannibals;
    int boat;
};

// Convert state to visual representation
string stateToVisual(const State& s) {
    string left_missionaries = string(s.missionaries, 'M');
    string left_cannibals = string(s.cannibals, 'C');
    string boat = s.boat ? "⛵" : "  ";
    string right_missionaries = string(3 - s.missionaries, 'M');
    string right_cannibals = string(3 - s.cannibals, 'C');
    string other_boat = s.boat ? "  " : "⛵";
    return left_missionaries + left_cannibals + boat + " ~~~~ " + other_boat + right_missionaries + right_cannibals;
}

bool isValidState(int m, int c) {
    return (m == 0 || m >= c) && (3 - m == 0 || 3 - m >= 3 - c);
}

bool isGoalState(const State& s) {
    return s.missionaries == 0 && s.cannibals == 0 && s.boat == 0;
}

vector<State> getSuccessors(const State& s) {
    vector<State> successors;
    int m = s.missionaries, c = s.cannibals, b = s.boat;

    vector<pair<int, int>> moves = {{1, 0}, {2, 0}, {0, 1}, {0, 2}, {1, 1}};

    for (auto move : moves) {
        int dm = move.first, dc = move.second;
        if (b == 1) { // boat is on the starting side
            if (m >= dm && c >= dc) {
                State newState = {m - dm, c - dc, 0};
                if (isValidState(newState.missionaries, newState.cannibals)) {
                    successors.push_back(newState);
                }
            }
        } else { // boat is on the other side
            if (3 - m >= dm && 3 - c >= dc) {
                State newState = {m + dm, c + dc, 1};
                if (isValidState(newState.missionaries, newState.cannibals)) {
                    successors.push_back(newState);
                }
            }
        }
    }

    return successors;
}

void printSolution(const vector<State>& path) {
    for (const auto& s : path) {
        cout << stateToVisual(s) << "\n";
    }
}

void bfs() {
    queue<vector<State>> q;
    set<tuple<int, int, int>> visited;

    State start = {3, 3, 1};
    q.push({start});
    visited.insert({start.missionaries, start.cannibals, start.boat});

    while (!q.empty()) {
        vector<State> path = q.front();
        q.pop();

        State current = path.back();
        if (isGoalState(current)) {
            printSolution(path);
            return;
        }

        vector<State> successors = getSuccessors(current);
        for (const State& succ : successors) {
            if (visited.find({succ.missionaries, succ.cannibals, succ.boat}) == visited.end()) {
                visited.insert({succ.missionaries, succ.cannibals, succ.boat});
                vector<State> newPath = path;
                newPath.push_back(succ);
                q.push(newPath);
            }
        }
    }
}

int main() {
    bfs();
    return 0;
}

