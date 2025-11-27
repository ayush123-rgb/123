#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void centralizedBFS(int start, vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "Centralized BFS Order: ";

    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << " ";

        for (int v : graph[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << endl;
}

int main() {
    int n, e;
    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter number of edges: ";
    cin >> e;

    vector<vector<int>> graph(n);

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int start;
    cout << "Enter start node: ";
    cin >> start;

    centralizedBFS(start, graph);
}


/*Example input:
5
6
0 1
0 2
1 3
1 4
2 4
3 4
0
*/

/*Pseudocode
CentralizedBFS(start):
    mark start visited
    queue Q
    enqueue start

    while Q not empty:
        u = dequeue Q
        print u

        for each neighbor v of u:
            if v not visited:
                mark visited
                enqueue v
*/

/*3. Time Complexity Comparison
Centralized BFS
𝑂(𝑉+𝐸)

Distributed BFS (K workers)
Each BFS level processed in parallel:

𝑂((𝑉+𝐸)/K)

Speedup:
Speedup=𝐾(ideal)
*/
/*

Space Complexity
Both store adjacency list + visited:
O(V+E)

Distributed BFS extra:
Local buffers per worker: O(K)
Total: O(V+E+K)*/