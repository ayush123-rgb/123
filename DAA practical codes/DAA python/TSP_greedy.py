# Greedy TSP (Nearest Neighbor Heuristic)
# Very easy version

def tsp_greedy(dist, start=0):
    n = len(dist)
    visited = [False] * n
    path = [start]
    visited[start] = True
    total_cost = 0
    current = start

    for _ in range(n - 1):
        next_city = -1
        min_dist = float('inf')

        # find nearest unvisited city
        for city in range(n):
            if not visited[city] and dist[current][city] < min_dist:
                min_dist = dist[current][city]
                next_city = city

        path.append(next_city)
        visited[next_city] = True
        total_cost += min_dist
        current = next_city

    # return to starting city
    total_cost += dist[current][start]
    path.append(start)

    return total_cost, path


# INPUT
n = int(input("Enter number of cities: "))
print("Enter distance matrix:")
dist = [list(map(int, input().split())) for _ in range(n)]

cost, path = tsp_greedy(dist)
print("Greedy Tour Cost:", cost)
print("Path:", path)

'''
use this test case
4
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0
---------
1. Take the starting city (default = 0).
2. Mark the starting city as visited and add it to the path.
3. Set current city = start.

4. Repeat (n – 1) times:
      a. Among all unvisited cities, find the city with the minimum
         distance from the current city.
      b. Move to that nearest city.
      c. Mark that city as visited.
      d. Add its distance to the total cost.
      e. Add that city to the path.

5. After all cities are visited:
      a. Add the distance from the last city back to the starting city.
      b. Append the starting city to the path to complete the tour.

6. Return the total cost and the final path.
---------------
time complexity: O(n²)
-------
space complexity: O(n)

'''