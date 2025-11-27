#include <iostream>
using namespace std;

#define N 4  // Number of vertices

bool isSafe(int v, bool graph[N][N], int color[], int c) {
    for (int i = 0; i < N; i++)
        if (graph[v][i] && color[i] == c)
            return false;
    return true;
}

bool graphColoringUtil(bool graph[N][N], int m, int color[], int v) {
    if (v == N)
        return true;  // All vertices are colored

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, graph, color, c)) {
            color[v] = c;
            if (graphColoringUtil(graph, m, color, v + 1))
                return true;
            color[v] = 0; // BACKTRACK
        }
    }
    return false;
}

bool graphColoring(bool graph[N][N], int m) {
    int color[N] = {0};

    if (!graphColoringUtil(graph, m, color, 0)) {
        cout << "No solution exists" << endl;
        return false;
    }

    cout << "Assigned colors: ";
    for (int i = 0; i < N; i++)
        cout << color[i] << " ";
    cout << endl;
    return true;
}

int main() {
    bool graph[N][N] = {
        {0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {1, 0, 1, 0}
    };

    int m = 3; // Number of colors
    graphColoring(graph, m);

    return 0;
}


/*pseudocode
GRAPH_COLORING(graph, m, n):
    color[n] = {0}
    if solve(0, graph, color, m, n):
        print color[]
    else:
        print "No solution"

solve(v, graph, color, m, n):
    if v == n:
        return True
    for c in 1 to m:
        if isSafe(v, graph, color, c, n):
            color[v] = c
            if solve(v + 1, graph, color, m, n):
                return True
            color[v] = 0  // BACKTRACK
    return False

isSafe(v, graph, color, c, n):
    for i in 0 to n-1:
        if graph[v][i] == 1 and color[i] == c:
            return False
    return True
*/

/*
| Type                 | Complexity | Explanation                                     |
| -------------------- | ---------- | ----------------------------------------------- |
| **Time Complexity**  | **O(mⁿ)**  | Each vertex can have up to `m` color choices    |
| **Space Complexity** | **O(n)**   | For storing the color array and recursion stack |
*/

/*Python code
N = 4

def is_safe(v, graph, color, c):
    for i in range(N):
        if graph[v][i] == 1 and color[i] == c:
            return False
    return True

def graph_coloring_util(graph, m, color, v):
    if v == N:
        print("Solution:", color)
        return True

    for c in range(1, m + 1):
        if is_safe(v, graph, color, c):
            color[v] = c
            if graph_coloring_util(graph, m, color, v + 1):
                return True
            color[v] = 0  # BACKTRACK
    return False

def graph_coloring(graph, m):
    color = [0] * N
    if not graph_coloring_util(graph, m, color, 0):
        print("No solution exists")

graph = [
    [0, 1, 1, 1],
    [1, 0, 1, 0],
    [1, 1, 0, 1],
    [1, 0, 1, 0]
]

m = 3
graph_coloring(graph, m)
*/