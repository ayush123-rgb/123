"""
---------------------------------------------------------
              DIJKSTRA'S ALGORITHM (PYTHON)
---------------------------------------------------------

ALGORITHM:
1. Set all distances = infinity except source = 0.
2. Mark all nodes unvisited.
3. Repeat n-1 times:
      - Pick unvisited node with smallest distance.
      - Mark it visited.
      - Update neighbor distances.
4. Print final distances.

PSEUDOCODE:
dist[] = INF
dist[src] = 0
visited[] = false

repeat n-1 times:
    u = unvisited node with minimum dist
    visited[u] = true
    for each neighbor v:
        if dist[u] + weight < dist[v]:
            dist[v] = dist[u] + weight

---------------------------------------------------------
SAMPLE INPUT:
Enter number of nodes: 5
Enter number of edges: 6
Enter edge (u v w): 0 1 2
Enter edge (u v w): 0 2 4
Enter edge (u v w): 1 2 1
Enter edge (u v w): 1 3 7
Enter edge (u v w): 2 4 3
Enter edge (u v w): 3 4 2
Enter source node: 0

SAMPLE OUTPUT:
Distance to Node 0 = 0
Distance to Node 1 = 2
Distance to Node 2 = 3
Distance to Node 3 = 9
Distance to Node 4 = 6
---------------------------------------------------------
"""

print("Enter number of nodes:", end=" ")
n = int(input())

print("Enter number of edges:", end=" ")
e = int(input())

graph = []
for i in range(n):
    row = []
    for j in range(n):
        row.append(0)
    graph.append(row)

for i in range(e):
    print("Enter edge (u v w):", end=" ")
    u, v, w = map(int, input().split())
    graph[u][v] = w
    graph[v][u] = w

print("Enter source node:", end=" ")
src = int(input())

dist = []
vis = []
for i in range(n):
    dist.append(999999)
    vis.append(0)

dist[src] = 0

for _ in range(n - 1):
    u = -1
    for i in range(n):
        if vis[i] == 0 and (u == -1 or dist[i] < dist[u]):
            u = i

    vis[u] = 1

    for v in range(n):
        if graph[u][v] != 0 and vis[v] == 0:
            if dist[u] + graph[u][v] < dist[v]:
                dist[v] = dist[u] + graph[u][v]

print("\n--- Shortest Distances ---")
for i in range(n):
    print("Distance to Node", i, "=", dist[i])
