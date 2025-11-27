#include <iostream>
using namespace std;

const int INF = 99999;
const int V = 4;  // fixed number of vertices

void floydWarshall(int graph[V][V]) {
    int dist[V][V];

    // Initialize
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Floyd-Warshall
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print result
    cout << "Shortest distances between every pair of vertices:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
}

int main() {
    int graph[V][V];

    cout << "Enter adjacency matrix (" << V << "x" << V << ") use " << INF << " for INF:\n";

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
        }
    }

    floydWarshall(graph);
    return 0;
}


/*
example input:
0 5 99999 10
99999 0 3 99999
99999 99999 0 1
99999 99999 99999 0
*/


/*PseudoCode
FloydWarshall(dist[][], V):
    for k from 0 to V-1:
        for i from 0 to V-1:
            for j from 0 to V-1:
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]

    print dist[][]
*/

/*| Type                 | Complexity | Explanation                          |
| -------------------- | ---------- | ------------------------------------ |
| **Time Complexity**  | **O(V³)**  | Three nested loops over all vertices |
| **Space Complexity** | **O(V²)**  | To store the distance matrix         |
*/