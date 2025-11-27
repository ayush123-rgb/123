from collections import deque

def centralized_bfs(start, graph):
    n = len(graph)
    visited = [False] * n
    q = deque()

    visited[start] = True
    q.append(start)

    print("Centralized BFS Order:", end=" ")

    while q:
        u = q.popleft()
        print(u, end=" ")

        for v in graph[u]:
            if not visited[v]:
                visited[v] = True
                q.append(v)

    print()  # newline


def main():
    # Input
    n = int(input("Enter number of nodes: "))
    e = int(input("Enter number of edges: "))

    # Create adjacency list
    graph = [[] for _ in range(n)]

    print("Enter edges (u v):")
    for _ in range(e):
        u, v = map(int, input().split())
        graph[u].append(v)
        graph[v].append(u)  # undirected graph

    start = int(input("Enter start node: "))

    centralized_bfs(start, graph)


if __name__ == "__main__":
    main()


'''
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
-----------
Pseudocode: 
/*Pseudocode
Centralized_BFS(start):
    create visited array of size N, initialize False
    mark visited[start] = True

    create queue Q
    enqueue(start)

    while Q is not empty:
        u = dequeue(Q)
        print u

        for each neighbor v in graph[u]:
            if visited[v] == False:
                mark visited[v] = True
                enqueue(v)
*/
---------------
/*Time Complexity

Centralized BFS:
O(V + E)

Reason:
- Each vertex is visited once → O(V)
- Each edge is checked once (undirected) → O(E)
*/
---------------------
/*Space Complexity

Centralized BFS:
O(V + E)

Reason:
- Adjacency list takes O(V + E)
- Visited array takes O(V)
- Queue takes up to O(V) in worst case
*/
'''
