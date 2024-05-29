#include<iostream>
#include<vector>
#include<queue>
#include<map>
using namespace std;

int isGoal(vector<vector<int>> start, vector<vector<int>> goal) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (start[i][j] != goal[i][j]) return 0;
        }
    }
    return 1;
}

pair<int,int> empt(vector<vector<int>> temp) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (temp[i][j] == 0) return {i, j};
        }
    }
    return make_pair(-1, -1);
}

void print(vector<vector<int>> temp) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << temp[i][j] << "\t";
        }
        cout << "\n";
    }
    cout << "\n";
}

int isVisited(map<vector<vector<int>>, vector<vector<int>>> &parent, vector<vector<int>> temp) {
    if (parent.find(temp) != parent.end()) return 1;
    return 0;
}

void breadth(vector<vector<int>> start, vector<vector<int>> goal) {
    queue<vector<vector<int>>> q;
    map<vector<vector<int>>, vector<vector<int>>> parent; // Map to store parent-child relationship

    q.push(start);
    parent[start] = start; // Start node has itself as parent
    vector<vector<int>> dir = {{1, 0}, {0, -1}, {0, 1}, {-1, 0}};

    while (!q.empty()) {
        vector<vector<int>> temp = q.front();
        q.pop();
        
        pair<int, int> mt = empt(temp);
        for (auto i : dir) {
            if (mt.first - i[0] >= 0 && mt.first - i[0] < 3 && mt.second - i[1] >= 0 && mt.second - i[1] < 3) {
                vector<vector<int>> new_temp = temp;
                swap(new_temp[mt.first][mt.second], new_temp[mt.first - i[0]][mt.second - i[1]]);
           

                if (!isVisited(parent, new_temp)) {
                    q.push(new_temp);
                    parent[new_temp] = temp;
                    if (isGoal(new_temp, goal)) {
                        vector<vector<int>> path = new_temp;
                        while (path != start) {
                            print(path);
                            path = parent[path];
                        }
                        return;
                    }
                }
            }
        }
    }
}

int main() {
    vector<vector<int>> start = {{1, 2, 3}, {5, 6, 0}, {7, 8, 4}};
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    breadth(start, goal);
    return 0;
}
