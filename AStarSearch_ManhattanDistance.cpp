#include <bits/stdc++.h>
using namespace std;

#define N 3

//This defines a structure Node to represent a node in the search tree. Each node contains a pointer to its parent, the puzzle matrix mat, the position of the empty cell (x, y), the cost, and the level in the search tree.

struct Node
{
    Node* parent;
    int mat[N][N];
    int x, y;
    int cost;
    int level;
    int manhattanDistance; // Added member variable for the Manhattan distance heuristic
};


//Prints a given matrix

int printMatrix(int mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
    return 0;
}

//Manhattan Distance calculation
int calculateManhattanDistance(int mat[N][N], int final[N][N])
{
    int distance = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] != 0) {
                int goalX, goalY;
                goalX = (mat[i][j] - 1) / N;
                goalY = (mat[i][j] - 1) % N;
                distance += abs(i - goalX) + abs(j - goalY);
            }
        }
    }
    return distance;
}



//check if a given position (x, y) is within the bounds of the puzzle matrix
int isSafe(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void printPath(Node* root)
{
    if (root == NULL) //it means we have reached the end of the path and the function returns without further recursion
        return;
    printPath(root->parent); //recursively calls printPath on the parent of the current node (root)
    printMatrix(root->mat); //prints the puzzle matrix of the current node (root)
    printf("\n");
}

//comparison function for the priority queue used. It compares nodes based on their total cost and level
struct comp
{
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return (lhs->cost + lhs->level + lhs->manhattanDistance) > (rhs->cost + rhs->level + rhs->manhattanDistance);
    }
};

// New node

Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent,int final[N][N])
{
    Node* node = new Node;
    node->parent = parent;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            node->mat[i][j] = mat[i][j];
        }
    }

    int temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;

    node->cost = INT_MAX;
    node->level = level;
    node->x = newX;
    node->y = newY;

    node->manhattanDistance = calculateManhattanDistance(node->mat,final);

    return node;
}

int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };

void solve(int initial[N][N], int x, int y, int final[N][N])
{
    priority_queue<Node*, std::vector<Node*>, comp> pq;

    Node* root = newNode(initial, x, y, x, y, 0, NULL,final);
    root->cost = 0;
    root->manhattanDistance = calculateManhattanDistance(root->mat, final); // Calculate the initial Manhattan distance
    pq.push(root);

    while (!pq.empty())
    {
        Node* min = pq.top();
        pq.pop();

        if (min->manhattanDistance == 0)
        {
            printPath(min);
            return;
        }

        for (int i = 0; i < 4; i++)
        {
            if (isSafe(min->x + row[i], min->y + col[i]))
            {
                Node* child = newNode(min->mat, min->x, min->y, min->x + row[i], min->y + col[i], min->level + 1, min,final);
                child->cost = min->cost + 1;
                child->manhattanDistance = calculateManhattanDistance(child->mat, final); // Update the Manhattan distance
                pq.push(child);
            }
        }
    }
}


int main()
{
    int initial[N][N] = {
        {5,0,8},
        {4,2,1},
        {7,3,6}
    };

    int final[N][N] = {
        {1,2,3},
        {4,5,6},
        {7,8,0}
    };

    int x = 0, y = 1;

    solve(initial, x, y, final);

    return 0;
}
