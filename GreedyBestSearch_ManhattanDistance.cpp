#include <bits/stdc++.h>
using namespace std;

#define N 3

struct Node {
    Node* parent;
    int mat[N][N];
    int x, y;
    int cost;
    int level;
};

int printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
    return 0;
}

Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
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
    return node;
}

int calculateCost(int mat[N][N], int final[N][N]) {
    int totalManhattanDistance = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] != 0) {
                for (int k = 0; k < N; k++) {
                    for (int l = 0; l < N; l++) {
                        if (mat[i][j] == final[k][l]) {
                            totalManhattanDistance += abs(i - k) + abs(j - l);
                        }
                    }
                }
            }
        }   
	}
    return totalManhattanDistance;

}

int isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void printPath(Node* root) {
    if (root == NULL)
        return;
    printPath(root->parent);
    printMatrix(root->mat);
    printf("\n");
}

struct comp {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->cost > rhs->cost;
    }
};

int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };

void solve(int initial[N][N], int x, int y, int final[N][N]) {
    priority_queue<Node*, vector<Node*>, comp> pq;

    Node* root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(initial, final);
    pq.push(root);

    while (!pq.empty()) {
        Node* min = pq.top();
        pq.pop();

        if (min->cost == 0) {
            printPath(min);
            return;
        }

        for (int i = 0; i < 4; i++) {
            if (isSafe(min->x + row[i], min->y + col[i])) {
                Node* child = newNode(min->mat, min->x, min->y, min->x + row[i], min->y + col[i], min->level + 1, min);
                child->cost = calculateCost(child->mat, final);
                pq.push(child);
            }
        }
    }
}

int main() {
     int initial[N][N] = {
        {2,8,3},
        {1,6,4},
        {7,0,5}
    };

    int final[N][N] = {
        {1,2,3},
        {8,0,4},
        {7,6,5}
    };

    int x = 2, y = 1;

    solve(initial, x, y, final);

    return 0;
}

