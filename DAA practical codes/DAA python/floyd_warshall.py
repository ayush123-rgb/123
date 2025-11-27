INF = 99999
V = 4  # number of vertices

def floyd_warshall(graph):
    # Copy graph into dist matrix
    dist = [row[:] for row in graph]

    # Floyd-Warshall Algorithm
    for k in range(V):
        for i in range(V):
            for j in range(V):
                if dist[i][k] + dist[k][j] < dist[i][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]

    # Print result
    print("Shortest distances between every pair of vertices:")
    for i in range(V):
        for j in range(V):
            print("INF" if dist[i][j] == INF else dist[i][j], end="\t")
        print()


# ---------------- USER INPUT -----------------

graph = []

print(f"Enter adjacency matrix ({V} x {V}) use {INF} for INF:")

for _ in range(V):
    row = list(map(int, input().split()))
    graph.append(row)

floyd_warshall(graph)

'''
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
'''