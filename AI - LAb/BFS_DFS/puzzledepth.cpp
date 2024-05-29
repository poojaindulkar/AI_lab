#include<iostream>
#include<vector>
#include<stack>
#include<map>
using namespace std;

pair<int,int> mt(vector<vector<int>> temp){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(temp[i][j]==0) return {i,j};
        }
    }
    return {-1,-1};
}
int visited(vector<vector<int>> temp,  map<vector<vector<int>>, vector<vector<int>>> parent){
    return parent.find(temp) != parent.end();
}
int isGoal(vector<vector<int>> start, vector<vector<int>> goal) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (start[i][j] != goal[i][j]) return 0;
        }
    }
    return 1;
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
void depth(vector<vector<int>> start, vector<vector<int>> goal){
    stack<vector<vector<int>>> s;
    map<vector<vector<int>>, vector<vector<int>>> parent;
    s.push(start);
    vector<vector<int>> dir={{0, -1}, {-1, 0}, {0, 1}, {1, 0}}; 
    while(!s.empty()){
        
        vector<vector<int>> temp = s.top();
        s.pop();
        if (isGoal(temp, goal))
        {
            vector<vector<int>> path = temp;
            while (path != start) {
                print(path);
                path = parent[path];
            }
            print(start);
            return;
        }
        pair<int,int> empt = mt(temp);
        int x = empt.first;
        int y = empt.second;
        for (auto i: dir)
        {
            if((x+i[0])>=0 && (x+i[0])<3 && (y+i[1])>=0 && (y+i[1])<3){
                vector<vector<int>> temp_temp=temp;
                swap(temp_temp[x][y],temp_temp[x+i[0]][y+i[1]]);
              
                if(!visited(temp_temp,parent)){
                    s.push(temp_temp);
                    parent[temp_temp]=temp;
                }
            }
        }    
    }
    cout << "No solution found!\n";
} // Added this closing brace

int main() {
  vector<vector<int>> start = {{1, 2, 3}, {4,5,6}, {0,7, 8}};
    vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    depth(start, goal);
    return 0;
}
