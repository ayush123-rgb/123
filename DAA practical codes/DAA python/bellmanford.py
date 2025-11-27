def bellman_ford():
    # Input
    V = int(input("Enter number of vertices: "))
    E = int(input("Enter number of edges: "))

    edges = []
    print("Enter edges as: u v w")
    for _ in range(E):
        u, v, w = map(int, input().split())
        edges.append((u, v, w))

    source = int(input("Enter source vertex: "))

    # Step 1: Initialize distances
    INF = float('inf')
    dist = [INF] * V
    dist[source] = 0

    # Step 2: Relax all edges V-1 times
    for _ in range(V - 1):
        for u, v, w in edges:
            if dist[u] != INF and dist[u] + w < dist[v]:
                dist[v] = dist[u] + w

    # Step 3: Check for negative cycles
    for u, v, w in edges:
        if dist[u] != INF and dist[u] + w < dist[v]:
            print("Graph contains a negative weight cycle.")
            return

    # Step 4: Print results
    print("\nVertex\tDistance from Source")
    for i in range(V):
        print(i, "\t", "INF" if dist[i] == INF else dist[i])


'''
Algorithm: Bellman–Ford Shortest Path

1. Read number of vertices V and edges E.
2. Read each edge as (u, v, weight) and store in a list.
3. Read source vertex S.
4. Create a dist[] array of size V and set all values to ∞.
5. Set dist[S] = 0.
6. Repeat V − 1 times:
       For every edge (u, v, w):
           If dist[u] + w < dist[v]:
               Update dist[v] = dist[u] + w.
7. Check for negative weight cycles:
       For every edge (u, v, w):
           If dist[u] + w < dist[v]:
               Report negative cycle and stop.
8. Print all distances from source.
-----------------------
Time complexity: 
Relax edges V−1 times:  O(V × E)
Negative-cycle check:   O(E)

Total:                  O(VE)
---------------------------
space complexity:
Distance array:   O(V)
Edges storage:    O(E)

Total:            O(V + E)
'''