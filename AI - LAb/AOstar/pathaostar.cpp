#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>

struct Node {
    int id;
    std::vector<std::pair<Node*, int>> neighbors; // Pair of neighbor node and the cost to reach it
};

void addEdge(Node* src, Node* dest, int cost) {
    src->neighbors.push_back({dest, cost});
}

struct SearchNode {
    Node* node;
    int g; // Cost to reach this node
    int h; // Heuristic cost to goal
    int f; // Total cost (g + h)
    SearchNode* parent;
    std::vector<SearchNode*> children;

    SearchNode(Node* n, int g_cost, int h_cost, SearchNode* p = nullptr) 
        : node(n), g(g_cost), h(h_cost), f(g_cost + h_cost), parent(p) {}
};

int heuristic(Node* node, Node* goal) {
    // Define your heuristic function here. For simplicity, we'll return 0.
    // In a real-world scenario, this would estimate the cost from node to goal.
    return 0;
}

void aoStar(Node* start, Node* goal) {
    std::unordered_map<Node*, SearchNode*> openList;
    std::unordered_map<Node*, SearchNode*> closedList;

    SearchNode* startNode = new SearchNode(start, 0, heuristic(start, goal));
    openList[start] = startNode;

    while (!openList.empty()) {
        // Select the node with the lowest f value
        auto current = std::min_element(openList.begin(), openList.end(),
            [](const auto& a, const auto& b) {
                return a.second->f < b.second->f;
            });
        
        SearchNode* currentNode = current->second;
        openList.erase(current);

        if (currentNode->node == goal) {
            // Goal reached, reconstruct the path
            std::vector<Node*> path;
            while (currentNode) {
                path.push_back(currentNode->node);
                currentNode = currentNode->parent;
            }
            std::cout << "Path found: ";
            for (auto it = path.rbegin(); it != path.rend(); ++it) {
                std::cout << (*it)->id << " ";
            }
            std::cout << std::endl;
            return;
        }

        closedList[currentNode->node] = currentNode;

        for (auto& neighbor : currentNode->node->neighbors) {
            Node* neighborNode = neighbor.first;
            int cost = neighbor.second;

            if (closedList.find(neighborNode) != closedList.end())
                continue;

            int tentative_g = currentNode->g + cost;
            bool inOpenList = openList.find(neighborNode) != openList.end();
            SearchNode* neighborSearchNode = inOpenList ? openList[neighborNode] : new SearchNode(neighborNode, tentative_g, heuristic(neighborNode, goal), currentNode);

            if (!inOpenList || tentative_g < neighborSearchNode->g) {
                neighborSearchNode->g = tentative_g;
                neighborSearchNode->f = tentative_g + neighborSearchNode->h;
                neighborSearchNode->parent = currentNode;
                
                if (!inOpenList)
                    openList[neighborNode] = neighborSearchNode;
            }
        }
    }

    std::cout << "Path not found." << std::endl;
}

int main() {
    // Create nodes
    Node node1 {1, {}};
    Node node2 {2, {}};
    Node node3 {3, {}};
    Node node4 {4, {}};
    Node node5 {5, {}};

    // Create graph
    addEdge(&node1, &node2, 1);
    addEdge(&node1, &node3, 4);
    addEdge(&node2, &node4, 2);
    addEdge(&node2, &node5, 7);
    addEdge(&node3, &node5, 3);
    addEdge(&node4, &node5, 1);

    Node* start = &node1;
    Node* goal = &node5;

    // Perform AO* search
    aoStar(start, goal);

    return 0;
}
