#include <bits/stdc++.h>
using namespace std;
#define N 3  // 3x3 matrix for 8 puzzle

// Directions for moving the blank space (down, left, up, right)
int drow[] = {1, 0, -1, 0};
int dcol[] = {0, -1, 0, 1};

// Node structure representing each state in the puzzle
struct Node {
    Node* parent;      // Pointer to parent node (to trace the path)
    int mat[N][N];     // 3x3 puzzle matrix
    int g;             // Cost from start to current node
    int h;             // Heuristic cost to goal
    int x, y;          // Coordinates of the blank (zero) tile
};

// Print the current puzzle matrix along with g, h, f values
void printMatrix(int mat[N][N], int g, int h) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
    cout << "g: " << g << " "
         << "h: " << h << " "
         << "f: " << g + h << endl;
}

// Creates a new Node by swapping the blank tile to a new position
Node* newNode(int mat[N][N], int x, int y, int nx, int ny, int g, Node* parent) {
    Node* node = new Node;
    node->parent = parent;

    // Copy previous matrix state to new node
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            node->mat[i][j] = mat[i][j];
        }
    }

    // Swap the blank tile with the new tile
    swap(node->mat[x][y], node->mat[nx][ny]);

    node->g = g;
    node->h = INT_MAX; // Will be set after creating the node
    node->x = nx;
    node->y = ny;

    return node;
}

// Heuristic function: counts number of misplaced tiles
int heuristic(int initial[N][N], int final[N][N]) {
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (initial[i][j] != 0 && initial[i][j] != final[i][j]) {
                cnt++; // Increment if tile is misplaced (ignoring blank)
            }
        }
    }
    return cnt;
}

// Checks if (x, y) is within matrix bounds
bool isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Recursively prints the full path from start to goal
void printPath(Node* root) {
    if (root == nullptr) return;
    printPath(root->parent);
    printMatrix(root->mat, root->g, root->h);
    cout << endl;
}

// Custom comparator to prioritize lower f = g + h
struct comp {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return (lhs->g + lhs->h) > (rhs->g + rhs->h); // Min heap
    }
};

// A* Search algorithm for solving the 8 puzzle
void Solve(int start[N][N], int x, int y, int goal[N][N]) {
    int cnt = 0;
    // Min heap priority queue for A*
    priority_queue<Node*, vector<Node*>, comp> pq;

    // Create root node from start state
    Node* root = newNode(start, x, y, x, y, 0, nullptr);
    root->h = heuristic(start, goal);
    pq.push(root);

    // Loop until goal state is found
    while (!pq.empty()) {
        Node* m = pq.top();
        pq.pop();

        // Goal reached
        if (m->h == 0) {
            cout << "This puzzle is solved in : " << cnt << " moves\n";
            printPath(m);
            return;
        }

        cnt++;

        // Try all 4 directions for the blank tile
        for (int i = 0; i < 4; i++) {
            int dx = m->x + drow[i];
            int dy = m->y + dcol[i];

            if (isSafe(dx, dy)) {
                // Create a new node by moving the blank tile
                Node* child = newNode(m->mat, m->x, m->y, dx, dy, m->g + 1, m);
                // Calculate heuristic
                child->h = heuristic(child->mat, goal);
                // Push the child into the priority queue
                pq.push(child);
            }
        }
    }
}

// Driver code
int main() {
    int start[N][N];
    int goal[N][N];
    int x = -1, y = -1;

    cout << "Enter the start state: \n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> start[i][j];
            if (start[i][j] == 0) {
                x = i;
                y = j; // Store the position of blank tile
            }
        }
    }

    cout << "\nEnter the goal state: \n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> goal[i][j];
        }
    }

    // Start solving the puzzle
    Solve(start, x, y, goal);
    return 0;
}
