#include <iostream>
#include <stack>
#include <vector>
#include <unordered_set>
#include <tuple>

using namespace std;

typedef tuple<int, int, int> State; // (M_left, C_left, Boat_side)

struct StateHash {
    size_t operator()(const State& state) const {
        return get<0>(state) * 100 + get<1>(state) * 10 + get<2>(state);
    }
};

bool isValidState(int M_left, int C_left) {
    int M_right = 3 - M_left;
    int C_right = 3 - C_left;
    if (M_left < 0 || M_right < 0 || C_left < 0 || C_right < 0)
        return false;
    if ((M_left > 0 && M_left < C_left) || (M_right > 0 && M_right < C_right))
        return false;
    return true;
}

bool dfs(State initialState, vector<State>& path) {
    stack<State> s;
    unordered_set<State, StateHash> visited;
    s.push(initialState);
    
    while (!s.empty()) {
        State current = s.top();
        s.pop();
        
        if (visited.count(current))
            continue;
        
        visited.insert(current);
        path.push_back(current);
        
        if (get<0>(current) == 0 && get<1>(current) == 0 && get<2>(current) == 1) {
            return true; // Goal state reached
        }
        
        int M_left = get<0>(current);
        int C_left = get<1>(current);
        int boat = get<2>(current);
        
        vector<State> nextStates;
        if (boat == 0) { // Boat on the left bank
            nextStates = {
                {M_left - 2, C_left, 1}, {M_left - 1, C_left - 1, 1}, {M_left, C_left - 2, 1},
                {M_left - 1, C_left, 1}, {M_left, C_left - 1, 1}
            };
        } else { // Boat on the right bank
            nextStates = {
                {M_left + 2, C_left, 0}, {M_left + 1, C_left + 1, 0}, {M_left, C_left + 2, 0},
                {M_left + 1, C_left, 0}, {M_left, C_left + 1, 0}
            };
        }
        
        for (State next : nextStates) {
            if (isValidState(get<0>(next), get<1>(next)) && !visited.count(next)) {
                s.push(next);
            }
        }
    }
    
    path.pop_back();
    return false;
}

int main() {
    State initialState = make_tuple(3, 3, 0);
    vector<State> path;
    
    if (dfs(initialState, path)) {
        cout << "Solution found!\n";
        for (const State& state : path) {
            cout << "(" << get<0>(state) << ", " << get<1>(state) << ", " << (get<2>(state) == 0 ? "left" : "right") << ")\n";
        }
    } else {
        cout << "No solution found.\n";
    }
    
    return 0;
}
