from collections import deque

def distributed_bfs(start, graph, workers):
    n = len(graph)
    visited = [False] * n

    # current frontier (BFS level)
    frontier = deque()
    visited[start] = True
    frontier.append(start)

    print("Distributed BFS Order:", end=" ")

    while frontier:
        # Take the entire frontier for this level
        nodes = []
        while frontier:
            nodes.append(frontier.popleft())

        # Split nodes across workers
        W = workers
        chunk = (len(nodes) + W - 1) // W  # ceiling division

        next_level = []

        # Each worker gets a chunk
        for w in range(W):
            left = w * chunk
            right = min((w + 1) * chunk, len(nodes))

            for i in range(left, right):
                u = nodes[i]
                print(u, end=" ")

                # Explore neighbors
                for v in graph[u]:
                    if not visited[v]:
                        visited[v] = True
                        next_level.append(v)

        # Prepare next frontier
        for v in next_level:
            frontier.append(v)

    print()  # newline


def main():
    # Input
    n = int(input("Enter number of nodes: "))
    e = int(input("Enter number of edges: "))

    # Adjacency list
    graph = [[] for _ in range(n)]

    print("Enter edges (u v):")
    for _ in range(e):
        u, v = map(int, input().split())
        graph[u].append(v)
        graph[v].append(u)  # undirected

    start = int(input("Enter start node: "))
    workers = int(input("Enter number of distributed workers: "))

    distributed_bfs(start, graph, workers)


if __name__ == "__main__":
    main()

'''
/*Pseudocode:
DistributedBFS(start, K):
    mark start visited
    frontier = {start}

    while frontier not empty:
        take all nodes in frontier into a list
        split this list into K equal parts (chunks)
        nextFrontier = empty list

        for each worker w from 1 to K:
            for each node u in worker's assigned chunk:
                print u
                for each neighbor v of u:
                    if v not visited:
                        mark visited
                        add v to nextFrontier

        frontier = nextFrontier
*/
-------------------
/*3. Time Complexity Comparison

Centralized BFS:
O(V + E)

Distributed BFS (K workers):
Each BFS level processed parallelly:

O((V + E) / K)

Speedup (ideal case):
Speedup = K
*/
-------------------------
/*Space Complexity

Both centralized and distributed store:
Adjacency list + visited array = O(V + E)

Distributed BFS extra:
Local chunk buffers for K workers = O(K)

Total:
O(V + E + K)
*/

'''