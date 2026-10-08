#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Definition for a pair: (weight, vertex)
typedef pair<int, int> iPair;

class Graph {
    int V; // Number of vertices
    vector<vector<iPair>> adj; // Adjacency list: adj[u] stores pairs of (v, weight)

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // Function to add an undirected weighted edge
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    // Function to find and print the Minimum Spanning Tree (MST)
    void primMST() {
        // Priority queue to store key values and vertex indices. 
        // Sorted by the first element of the pair (the edge weight).
        priority_queue<iPair, vector<iPair>, greater<iPair>> pq;

        int src = 0; // Choose vertex 0 as the starting root node

        // Vectors to track MST construction
        vector<int> key(V, INT_MAX);    // Minimum weight edge to include vertex i
        vector<int> parent(V, -1);      // Array to store the parent of vertex i in MST
        vector<bool> inMST(V, false);   // True if vertex i is included in MST

        // Initialize the source vertex
        pq.push({0, src});
        key[src] = 0;

        int totalWeight = 0;

        while (!pq.empty()) {
            // Extract the vertex with the minimum key value
            int u = pq.top().second;
            pq.pop();

            // If the vertex is already in the MST, skip it
            if (inMST[u]) continue;

            // Include vertex in MST
            inMST[u] = true;
            if (parent[u] != -1) {
                totalWeight += key[u];
            }

            // Traverse all adjacent vertices of u
            for (auto const& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                // If v is not in MST and the weight of (u, v) is smaller than current key of v
                if (!inMST[v] && key[v] > weight) {
                    // Update key of v
                    key[v] = weight;
                    pq.push({key[v], v});
                    parent[v] = u;
                }
            }
        }

        // Print the constructed MST edges and total cost
        cout << "Edges in the Minimum Spanning Tree:\n";
        cout << "Edge \tWeight\n";
        for (int i = 1; i < V; ++i) {
            if (parent[i] != -1) {
                cout << parent[i] << " - " << i << " \t" << key[i] << "\n";
            }
        }
        cout << "\nTotal Weight of MST: " << totalWeight << endl;
    }
};

int main() {
    // Create a graph with 9 vertices (0 to 8)
    int V = 9;
    Graph g(V);

    // Adding edges (u, v, weight)
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);

    // Run Prim's algorithm
    g.primMST();

    return 0;
}
