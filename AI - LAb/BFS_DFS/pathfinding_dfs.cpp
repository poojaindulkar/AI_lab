#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct Node{
    int vertex;
    Node* next;

    Node(int v) : vertex(v), next(nullptr) {}
};

struct Graph{
    int V;
    vector<Node*> adjlist;

    Graph(int v) : V(v), adjlist(v,nullptr) {}
};


void printGraph(Graph* g) {
    for (int i = 0; i < g->V; ++i) {
        cout << "Vertex " << i << " ->";
        Node* temp = g->adjlist[i];
        while (temp) {
            cout << " " << temp->vertex;
            temp = temp->next;
        }
        cout << endl;
    }
}
void addEdge(Graph *g, int u, int v){
    Node* newNode = new Node(v);
    newNode->next = g->adjlist[u];
    g->adjlist[u] = newNode;

    newNode = new Node(u);
    newNode->next = g->adjlist[v];
    g->adjlist[v] = newNode;
}

int dfs (Graph * g, int v, int goal, vector<int> &visited){
    visited[v]=1;
    if(v == goal) return 1; 
    cout << v << " ";
    Node* temp = g->adjlist[v];
    while(temp!= nullptr){
        if(!visited[temp->vertex]){
            if(dfs(g,temp->vertex,goal, visited)) return 1;
        }
        temp = temp->next;
    }
    return 0;
}
int main(){
    int V=5;

    Graph *graph = new Graph(V);

    addEdge(graph, 0,1);
    addEdge(graph, 2,4);
    addEdge(graph, 3,1);
    addEdge(graph, 0,4);
    addEdge(graph, 3,2);
    addEdge(graph, 4,1);
    addEdge(graph, 0,3);

    int start = 0;
    int goal = 2;
    vector<int> visited(V,0);
    if(!dfs(graph,start,goal,visited)) cout<<"Nopath";
    printGraph(graph);
}

















