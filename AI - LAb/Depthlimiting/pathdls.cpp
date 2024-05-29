#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

// Node structure for the graph
struct Node {
    int id;
    std::vector<Node*> neighbors;
};

// Depth-limited search function for pathfinding
bool depthLimitedSearch(Node* start, Node* goal, int depthLimit, std::vector<int>& path) {
    if (start == nullptr) return false;
    if (start->id == goal->id) {
        path.push_back(start->id);
        return true;
    }
    if (depthLimit <= 0) return false;
    
    for (Node* neighbor : start->neighbors) {
        if (depthLimitedSearch(neighbor, goal, depthLimit - 1, path)) {
            path.push_back(start->id);
            return true;
        }
    }
    return false;
}

// Helper function to add an edge between two nodes
void addEdge(Node* src, Node* dest) {
    src->neighbors.push_back(dest);
}

int main() {
    // Create nodes
    Node node1 {1, {}};
    Node node2 {2, {}};
    Node node3 {3, {}};
    Node node4 {4, {}};
    Node node5 {5, {}};

    // Create graph
    addEdge(&node1, &node2);
    addEdge(&node1, &node3);
    addEdge(&node2, &node4);
    addEdge(&node2, &node5);
    addEdge(&node3, &node5);
    addEdge(&node4, &node5);

    Node* start = &node1;
    Node* goal = &node5;
    int depthLimit = 2;
    std::vector<int> path;

    // Perform depth-limited search for pathfinding
    if (depthLimitedSearch(start, goal, depthLimit, path)) {
        std::cout << "Path found within depth limit " << depthLimit << ": ";
        for (auto it = path.rbegin(); it != path.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Path not found within depth limit " << depthLimit << std::endl;
    }

    return 0;
}
