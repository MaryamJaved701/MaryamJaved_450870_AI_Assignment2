#include <bits/stdc++.h>
using namespace std;

#define N 3

//This defines a structure Node to represent a node in the search tree. Each node contains a pointer to its parent, the puzzle matrix mat, the position of the empty cell (x, y), the cost, and the level in the search tree.

struct Node
{
    Node* parent; //member variable in the Node struct, and it represents a pointer to the parent node in the search tree
    int mat[N][N];
    int x, y;
    int cost;
    int level;
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

// New node

Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent)
{
    Node* node = new Node; //declares a pointer to a Node object named node. The new Node dynamically allocates memory for a new Node object on the heap. The pointer node is then assigned the memory address of the newly created Node object.
    node->parent = parent; //sets the parent member variable of the newly created Node object to the value of the parent parameter. This is typically done when creating a new node in a tree or graph structure to establish a connection between the current node and its parent.
    
    //Nested loops (for loops) are used to copy the puzzle matrix elements from the input matrix to the new node's matrix. This ensures that the new node's matrix represents the current state of the puzzle.
	for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
        node->mat[i][j] = mat[i][j];
    }
    }

	//Swap the values of the empty cell and the cell being moved to
    int temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;
    
    
    node->cost = INT_MAX; // Initialize the cost of the node to a max. This will be updated later
    node->level = level; //depth of the node in the tree
    
    //new positions of the empty cell
	node->x = newX;  
    node->y = newY;
    return node;
}

int calculateCost(int mat[N][N], int final[N][N])
{
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (mat[i][j] && mat[i][j] != final[i][j]) // if the value in the matrix is non-zero and is not the same as that in the final matrix then count it as misplaced tile
                count++;
    return count;
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
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level); //return the node with a lower total cost i-e higher priority
    }
};

//Possible Moves
int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };

void solve(int initial[N][N], int x, int y, int final[N][N])
{
    priority_queue<Node*, std::vector<Node*>, comp> pq; //A priority queue (pq) is created to store Node pointers. The priority queue uses the custom comparison function comp, which prioritizes nodes based on their total cost and level.

    Node* root = newNode(initial, x, y, x, y, 0, NULL); //calls new node function to get the initial state
    root->cost = calculateCost(initial, final); //cost of the root node is calculated using the calculateCost function, comparing the initial state with the final state
    pq.push(root); //pushed to the priority queue

    while (!pq.empty()) //continue search until the priority queue is empty
    {
        Node* min = pq.top(); // Get the node with the minimum cost from the priority queue
        pq.pop(); 

        if (min->cost == 0)	//if the cost is zero, goal is reached so print the path of the goal state
        {
            printPath(min);
            return;
        }

		//Generate child nodes by moving empty tile in possible directions
        for (int i = 0; i < 4; i++) //four possible movements of the tile
        {
            if (isSafe(min->x + row[i], min->y + col[i])) //potential new position after a move in the ith direction i-e the position of the popped node plus that through iteration
            {
                Node* child = newNode(min->mat, min->x, min->y, min->x + row[i], min->y + col[i], min->level + 1, min);
                child->cost = calculateCost(child->mat, final);
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
