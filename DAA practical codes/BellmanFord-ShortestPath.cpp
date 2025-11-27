#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;  // from, to, weight
};

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    vector<Edge> edges(E);

    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    int source;
    cout << "Enter source vertex: ";
    cin >> source;

    // Step 1: Initialize distances
    vector<int> dist(V, INT_MAX);
    dist[source] = 0;

    // Step 2: Relax edges (V - 1) times
    for (int i = 1; i <= V - 1; i++) {
        for (auto &e : edges) {
            if (dist[e.u] != INT_MAX && dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }

    // Step 3: Check for negative weight cycles
    for (auto &e : edges) {
        if (dist[e.u] != INT_MAX && dist[e.u] + e.w < dist[e.v]) {
            cout << "Graph contains a negative weight cycle.\n";
            return 0;
        }
    }

    // Step 4: Print result
    cout << "\nVertex\tDistance from Source\n";
    for (int i = 0; i < V; i++) {
        cout << i << "\t\t";
        if (dist[i] == INT_MAX)
            cout << "INF\n";
        else
            cout << dist[i] << "\n";
    }

    return 0;
}


/*
Pseudocode
BellmanFord(G, source):
    1. Initialize distance[] to ∞ for all vertices except source
       distance[source] = 0

    2. Repeat (V - 1) times:
          For each edge (u, v) with weight w in G:
              if distance[u] + w < distance[v]:
                  distance[v] = distance[u] + w

    3. For each edge (u, v) with weight w in G:
          if distance[u] + w < distance[v]:
              print("Graph contains a negative weight cycle")
              return

    4. Return distance[]

Time complexity
| Aspect               | Complexity   | Explanation                                             |
| -------------------- | ------------ | ------------------------------------------------------- |
| **Time Complexity**  | **O(V × E)** | Each of the **V − 1** iterations checks all **E edges** |
| **Space Complexity** | **O(V)**     | To store the `distance` array                           |

*/
