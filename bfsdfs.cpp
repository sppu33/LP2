#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class Graph {
public:
    unordered_map<string, vector<string>> adj;
    unordered_set<string> visited;

    void addEdge(const string& u, const string& v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected
    }

    void display() {
        cout << "\nGraph adjacency list:\n";
        for (auto& pair : adj) {
            cout << pair.first << ": ";
            for (auto& neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    void dfs(const string& node) {
        visited.insert(node);
        cout << node << " ";

        for (const string& neighbor : adj[node]) {
            if (visited.find(neighbor) == visited.end()) {
                dfs(neighbor);
            }
        }
    }

    void bfs(const string& start) {
        unordered_set<string> visited;
        queue<string> q;

        visited.insert(start);
        q.push(start);

        while (!q.empty()) {
            string current = q.front();
            q.pop();
            cout << current << " ";

            for (const string& neighbor : adj[current]) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
    }
};

int main() {
    Graph g;
    int choice;
    string node1, node2, startNode;

    // Initial edges
    // g.addEdge("A", "B");
    // g.addEdge("A", "C");
    // g.addEdge("B", "D");
    // g.addEdge("B", "E");
    // g.addEdge("C", "F");
    // g.addEdge("E", "F");

    // g.addEdge( "Katraj" , "PICT" ) ;
    // g.addEdge( "Bharti" , "Katraj" ) ; 
    // g.addEdge( "Bharti" , "PICT" ) ;
    // g.addEdge( "Katraj" , "SKNCOE" ) ; 
    // g.addEdge( "PICT" , "SKNCOE" ) ;
    // g.addEdge( "SKNCOE" , "Temple" ) ; 
    // g.addEdge( "Temple" , "Katraj" ) ; 
    // g.addEdge( "Temple" , "Kondhwa" ) ; 

    do {
        cout << "\n----- Graph Menu -----\n";
        cout << "1. Print Graph\n";
        cout << "2. BFS Traversal\n";
        cout << "3. DFS Traversal\n";
        cout << "4. Add Edge\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                g.display();
                break;

            case 2:
                cout << "Enter the start node of BFS: ";
                cin >> startNode;
                g.bfs(startNode);
                cout << endl;
                break;

            case 3:
                cout << "Enter the start node of DFS: ";
                cin >> startNode;
                g.visited.clear(); // Clear visited before DFS
                g.dfs(startNode);
                cout << endl;
                break;

            case 4:
                cout << "Enter source node: ";
                cin >> node1;
                cout << "Enter destination node: ";
                cin >> node2;
                g.addEdge(node1, node2);
                cout << "Edge added from " << node1 << " to " << node2 << ".\n";
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
