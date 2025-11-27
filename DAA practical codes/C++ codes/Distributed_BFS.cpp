#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Simulates distributed BFS using K workers
void distributedBFS(int start, vector<vector<int>>& graph, int workers) {
    int n = graph.size();
    vector<bool> visited(n, false);

    queue<int> frontier;   // current BFS level
    visited[start] = true;
    frontier.push(start);

    cout << "Distributed BFS Order: ";

    while (!frontier.empty()) {
        vector<int> nodes;

        // Extract full frontier
        while (!frontier.empty()) {
            nodes.push_back(frontier.front());
            frontier.pop();
        }

        // Split frontier across workers
        int W = workers;
        int chunk = (nodes.size() + W - 1) / W;

        vector<int> nextLevel;

        for (int w = 0; w < W; w++) {
            int left = w * chunk;
            int right = min((w + 1) * chunk, (int)nodes.size());

            for (int i = left; i < right; i++) {
                int u = nodes[i];
                cout << u << " ";

                for (int v : graph[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        nextLevel.push_back(v);
                    }
                }
            }
        }

        // Push next-level nodes into frontier
        for (int x : nextLevel) frontier.push(x);
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

    int workers;
    cout << "Enter number of distributed workers: ";
    cin >> workers;

    distributedBFS(start, graph, workers);
}

/*
5
6
0 1
0 2
1 3
1 4
2 4
3 4
0
2
*/

/*Pseudocode:
DistributedBFS(start, K):
    mark start visited
    frontier = {start}

    while frontier not empty:
        split frontier into K parts
        nextFrontier = empty list

        for each worker w in 1..K:
            for each node u in worker's part:
                print u
                for each neighbor v of u:
                    if v not visited:
                        mark visited
                        add v to nextFrontier

        frontier = nextFrontier
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