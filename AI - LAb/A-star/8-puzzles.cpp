#include <iostream>
#include <vector>
#include <algorithm>

// Define a class Node to represent each state of the puzzle
class Node
{
public:
    std::vector<std::vector<char>> data; // The puzzle state
    int level;                           // The depth of the node in the search tree
    int fval;                            // The total cost of the node (f-value)

    Node(std::vector<std::vector<char>> data, int level, int fval)
    {
        this->data = data;
        this->level = level;
        this->fval = fval;
    }

    std::vector<Node> generate_child();                                                                         // Method to generate child nodes
    std::vector<std::vector<char>> shuffle(std::vector<std::vector<char>> puz, int x1, int y1, int x2, int y2); // Method to shuffle the puzzle state
    std::vector<std::vector<char>> copy(std::vector<std::vector<char>> root);                                   // Method to copy the puzzle state
    std::pair<int, int> find(std::vector<std::vector<char>> puz, char x);                                       // Method to find the position of a character in the puzzle
};

// Generate child nodes by moving the blank space in different directions
std::vector<Node> Node::generate_child()
{
    std::vector<Node> children;
    auto blank_pos = find(data, '_');
    int x = blank_pos.first;
    int y = blank_pos.second;
    std::vector<std::pair<int, int>> val_list = {{x, y - 1}, {x, y + 1}, {x - 1, y}, {x + 1, y}};
    for (auto i : val_list)
    {
        auto child_data = shuffle(data, x, y, i.first, i.second);
        if (!child_data.empty())
        {
            Node child_node(child_data, level + 1, 0);
            children.push_back(child_node);
        }
    }
    return children;
}

// Shuffle the puzzle state by swapping two elements
std::vector<std::vector<char>> Node::shuffle(std::vector<std::vector<char>> puz, int x1, int y1, int x2, int y2)
{
    if (x2 >= 0 && x2 < puz.size() && y2 >= 0 && y2 < puz.size())
    {
        std::vector<std::vector<char>> temp_puz = puz;
        char temp = temp_puz[x2][y2];
        temp_puz[x2][y2] = temp_puz[x1][y1];
        temp_puz[x1][y1] = temp;
        return temp_puz;
    }
    else
    {
        return {};
    }
}

// Copy the puzzle state
std::vector<std::vector<char>> Node::copy(std::vector<std::vector<char>> root)
{
    std::vector<std::vector<char>> temp;
    for (auto i : root)
    {
        temp.push_back(i);
    }
    return temp;
}

// Find the position of a character in the puzzle
std::pair<int, int> Node::find(std::vector<std::vector<char>> puz, char x)
{
    for (size_t i = 0; i < puz.size(); ++i)
    {
        for (size_t j = 0; j < puz[i].size(); ++j)
        {
            if (puz[i][j] == x)
            {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

// Define a class Puzzle to represent the puzzle solving process
class Puzzle
{
public:
    int n;                    // The size of the puzzle (n x n)
    std::vector<Node> open;   // The open list of nodes
    std::vector<Node> closed; // The closed list of nodes

    Puzzle(int size)
    {
        n = size;
        open = std::vector<Node>();
        closed = std::vector<Node>();
    }

    std::vector<std::vector<char>> accept();                                          // Method to accept the puzzle input from the user
    int f(Node start, std::vector<std::vector<char>> goal);                           // Method to calculate the total cost of a node
    int h(std::vector<std::vector<char>> start, std::vector<std::vector<char>> goal); // Method to calculate the heuristic cost of a node
    void process();                                                                   // Method to solve the puzzle
};

// Accept the puzzle input from the user
std::vector<std::vector<char>> Puzzle::accept()
{
    std::vector<std::vector<char>> puz;
    for (int i = 0; i < n; ++i)
    {
        std::vector<char> temp;
        std::string input;
        std::getline(std::cin, input);
        for (char c : input)
        {
            if (c != ' ')
            {
                temp.push_back(c);
            }
        }
        puz.push_back(temp);
    }
    return puz;
}

// Calculate the total cost of a node
int Puzzle::f(Node start, std::vector<std::vector<char>> goal)
{
    return h(start.data, goal) + start.level;
}

// Calculate the heuristic cost of a node (number of misplaced tiles)
int Puzzle::h(std::vector<std::vector<char>> start, std::vector<std::vector<char>> goal)
{
    int temp = 0;
    for (size_t i = 0; i < start.size(); ++i)
    {
        for (size_t j = 0; j < start[i].size(); ++j)
        {
            if (start[i][j] != goal[i][j] && start[i][j] != '_')
            {
                temp += 1;
            }
        }
    }
    return temp;
}

// Solve the puzzle using A* algorithm
void Puzzle::process()
{
    std::cout << "Enter the start state matrix \n";
    std::vector<std::vector<char>> start = accept();
    std::cout << "Enter the goal state matrix \n";
    std::vector<std::vector<char>> goal = accept();

    Node start_node(start, 0, 0);
    start_node.fval = f(start_node, goal);
    open.push_back(start_node);
    std::cout << "\n\n";
    while (true)
    {
        Node cur = open[0];
        std::cout << "\n";
        std::cout << "  | \n";
        std::cout << "  | \n";
        std::cout << " \\'/ \n";
        for (auto i : cur.data)
        {
            for (auto j : i)
            {
                std::cout << j << " ";
            }
            std::cout << "\n";
        }
        if (h(cur.data, goal) == 0)
        {
            break;
        }
        for (auto i : cur.generate_child())
        {
            i.fval = f(i, goal);
            open.push_back(i);
        }
        closed.push_back(cur);
        open.erase(open.begin());

        std::sort(open.begin(), open.end(), [](Node const &a, Node const &b)
                  { return a.fval < b.fval; });
    }
}

int main()
{
    Puzzle puz(3); // Create a puzzle of size 3x3
    puz.process(); // Solve the puzzle
    return 0;
}
