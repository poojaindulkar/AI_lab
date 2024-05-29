#include<iostream>
#include<vector>
#include<queue> 
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


void addEdge(Graph *g, int u, int v){
    Node* newNode = new Node(v);
    newNode->next = g->adjlist[u];
    g->adjlist[u] = newNode;

    newNode = new Node(u);
    newNode->next = g->adjlist[v];
    g->adjlist[v] = newNode;
}

void bfs(Graph *graph, int start, int goal){
    queue<int> q;
    vector<int> visited(graph->V,0);
    q.push(start);
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        if (visited[curr]) continue;
        visited[curr] =1;
        cout<<curr<<" ";
        if (curr == goal) return ;
        
        Node *temp = graph->adjlist[curr];

        while (temp != NULL)
        {
            if(!visited[temp->vertex]){
                q.push(temp->vertex);
            }
            temp = temp->next;
        }
        
    }
    
}

int main(){
    Graph * graph = new Graph(5);
    addEdge(graph, 0,1);
    addEdge(graph, 2,4);
    addEdge(graph, 3,1);
    addEdge(graph, 0,4);
    addEdge(graph, 3,2);
    addEdge(graph, 4,1);
    addEdge(graph, 0,3);

    bfs(graph,0,2);
    return 0;
}