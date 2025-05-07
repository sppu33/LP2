#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// structure to represent edge in a graph
struct Edge {
    int src, dest, weight;
};

// function to compare two edges based on their weights
bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

// function to find the parent node of the vertex in the disjoint-set data structure
int findParent(vector<int>& parent, int u) {
    if (parent[u] != u) {
        parent[u] = findParent(parent, parent[u]);
    }
    return parent[u];
}

// function to perform union operation on disjoint sets
void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
    int xroot = findParent(parent, x);
    int yroot = findParent(parent, y);

    if (rank[xroot] < rank[yroot]) {
        parent[xroot] = yroot;
    }
    else if (rank[xroot] > rank[yroot]) {
        parent[yroot] = xroot;
    }
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

vector<Edge> KruskalsMST(vector<Edge>& edges, int V) {
    vector<Edge> result;
    // vector<int> parent(V);
    // vector<int> rank(V, 0);

    vector<int> parent(V + 1);  // to handle 1-based indexing
    vector<int> rank(V + 1, 0);


    sort(edges.begin(), edges.end(), compareEdges);

    for (int i = 0; i < V; i++) {
        parent[i] = i;
    }

    int i = 0;
    while (result.size() < V - 1 && i < edges.size()) {
        Edge next_edge = edges[i++];
        int x = findParent(parent, next_edge.src);
        int y = findParent(parent, next_edge.dest);

        if (x != y) {
            result.push_back(next_edge);
            unionSets(parent, rank, x, y);
        }
    }

    return result;
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);
    cout << "Enter each edge as: src dest weight\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    // vector<Edge> mst = KruskalsMST(edges, V);
    
    // for 1 based indexing:
    vector<Edge> mst = KruskalsMST(edges, V + 1);


    cout << "\nEdges in the constructed MST:\n";
    int totwt=0;
    for (Edge edge : mst) {
        totwt+=edge.weight;
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
    }
    cout<<"\n Total weight of MST is : "<<totwt<<endl;
    return 0;
}
