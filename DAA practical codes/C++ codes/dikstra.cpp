/*
---------------------------------------------------------
              DIJKSTRA'S ALGORITHM (C++)
---------------------------------------------------------

ALGORITHM:
1. Initialize distance of all nodes to infinity except source = 0.
2. Mark all nodes unvisited.
3. Repeat n-1 times:
      a. Pick the unvisited node with minimum distance.
      b. Mark it visited.
      c. Update its neighbors' distances.
4. Print all distances.

PSEUDOCODE:
dist[] = INF
dist[src] = 0
visited[] = false

repeat n-1 times:
    u = minimum distance unvisited node
    visited[u] = true
    for each neighbor v:
        if dist[u] + weight < dist[v]:
            dist[v] = dist[u] + weight

---------------------------------------------------------
SAMPLE INPUT:
Enter number of nodes: 5
Enter number of edges: 6
Enter edges (u v w):
0 1 2
0 2 4
1 2 1
1 3 7
2 4 3
3 4 2
Enter source node: 0

SAMPLE OUTPUT:
Distance from source to Node 0 = 0
Distance from source to Node 1 = 2
Distance from source to Node 2 = 3
Distance from source to Node 3 = 9
Distance from source to Node 4 = 6
---------------------------------------------------------
*/

#include <iostream>
using namespace std;

int main() {
    int n, e;
    
    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    int graph[100][100];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    cout << "Enter edges (u v w):" << endl;
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
        graph[v][u] = w;
    }

    int src;
    cout << "Enter source node: ";
    cin >> src;

    int dist[100], visited[100];
    for (int i = 0; i < n; i++) {
        dist[i] = 999999;
        visited[i] = 0;
    }

    dist[src] = 0;

    for (int c = 0; c < n - 1; c++) {
        int u = -1;
        for (int i = 0; i < n; i++)
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;

        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !visited[v]) {
                if (dist[u] + graph[u][v] < dist[v])
                    dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    cout << "\n--- Shortest Distances ---\n";
    for (int i = 0; i < n; i++)
        cout << "Distance from source to Node " << i << " = " << dist[i] << endl;

    return 0;
}
