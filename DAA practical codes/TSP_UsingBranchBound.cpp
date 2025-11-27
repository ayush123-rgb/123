#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

struct Node {
    vector<int> path;
    vector<vector<int>> mat;
    int bound;
    int level;

    bool operator<(Node const& other) const { 
        return bound > other.bound; // for min-heap
    }
};

int reduceMatrix(vector<vector<int>> &mat) {
    int n = mat.size();
    int cost = 0;

    // Row reduction
    for (int i = 0; i < n; ++i) {
        int rowmin = INF;
        for (int j = 0; j < n; ++j)
            rowmin = min(rowmin, mat[i][j]);

        if (rowmin == INF || rowmin == 0) continue;
        cost += rowmin;

        for (int j = 0; j < n; ++j)
            if (mat[i][j] < INF) mat[i][j] -= rowmin;
    }

    // Column reduction
    for (int j = 0; j < n; ++j) {
        int colmin = INF;
        for (int i = 0; i < n; ++i)
            colmin = min(colmin, mat[i][j]);

        if (colmin == INF || colmin == 0) continue;
        cost += colmin;

        for (int i = 0; i < n; ++i)
            if (mat[i][j] < INF) mat[i][j] -= colmin;
    }

    return cost;
}

pair<int, vector<int>> tspBranchAndBound(const vector<vector<int>> &cost) {
    int n = cost.size();
    vector<vector<int>> mat0 = cost;

    int b0 = reduceMatrix(mat0);

    Node root;
    root.path = {0};
    root.mat = mat0;
    root.bound = b0;
    root.level = 0;

    priority_queue<Node> pq;
    pq.push(root);

    int bestCost = INF;
    vector<int> bestPath;

    while (!pq.empty()) {
        Node node = pq.top(); 
        pq.pop();

        if (node.bound >= bestCost) continue;

        int u = node.path.back();

        if (node.level == n - 1) {
            int full = 0;
            for (size_t i = 0; i + 1 < node.path.size(); ++i)
                full += cost[node.path[i]][node.path[i + 1]];
            full += cost[node.path.back()][0]; 

            if (full < bestCost) {
                bestCost = full;
                bestPath = node.path;
                bestPath.push_back(0);
            }
            continue;
        }

        for (int v = 0; v < n; ++v) {
            if (find(node.path.begin(), node.path.end(), v) != node.path.end())
                continue;

            vector<vector<int>> childMat = node.mat;

            // Block row u and column v
            for (int j = 0; j < n; ++j)
                childMat[u][j] = INF;
            for (int i = 0; i < n; ++i)
                childMat[i][v] = INF;

            childMat[v][0] = INF;

            int add = reduceMatrix(childMat);
            int newBound = node.bound + cost[u][v] + add;

            if (newBound < bestCost) {
                Node child;
                child.path = node.path;
                child.path.push_back(v);
                child.mat = move(childMat);
                child.bound = newBound;
                child.level = node.level + 1;

                pq.push(child);
            }
        }
    }

    return {bestCost, bestPath};
}

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    vector<vector<int>> cost(n, vector<int>(n));

    cout << "\nEnter cost matrix (use -1 for INF / no edge):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
            if (cost[i][j] == -1) cost[i][j] = INF;
        }
    }

    auto res = tspBranchAndBound(cost);

    cout << "\nBest cost: " << res.first << "\nPath: ";
    for (int x : res.second) cout << x << " ";
    cout << "\n";

    return 0;
}


/*
example input:
4
-1 20 42 25
20 -1 30 34
42 30 -1 10
25 34 10 -1
*/

/*Pseudocode
TSP_BnB(cost, n):
    bestCost = +INF
    bestPath = []
    root = reduceMatrix(copy(cost))
    root.path = [0]
    root.bound = root.reductionCost
    root.level = 0
    PQ = min-heap keyed by bound
    PQ.push(root)

    while PQ not empty:
        node = PQ.pop()
        if node.bound >= bestCost: continue
        u = node.path.last
        if node.level == n-1:
            // complete path, add return edge
            total = node.bound + cost[u][0]
            if total < bestCost:
                bestCost = total
                bestPath = node.path + [0]
            continue

        for each city v not in node.path:
            newMat = copy(node.reducedMatrix)
            // cost from any to v's column/row set to INF per standard reduction after selecting u->v
            applyEdgeSelectionReduction(newMat, u, v)
            reductionCost = reduceMatrix(newMat) // returns reduction cost and updated matrix
            childBound = node.bound + cost[u][v] + reductionCost
            if childBound < bestCost:
                push child with updated matrix, path = node.path + [v], bound = childBound, level = node.level+1
    return bestCost, bestPath
*/

/*
Complexity
Worst-case Time: O(n!) (exponential). Branch & Bound prunes many nodes in practice but worst-case remains factorial.
Space: O(n × n × nodes_in_queue) for storing reduced matrices; if you optimize to store only changes, you can reduce per-node memory.*/