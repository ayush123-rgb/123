# TSP using Branch and Bound (Very Easy Version)
import math

def tsp_branch_and_bound(dist):
    n = len(dist)
    best_cost = math.inf
    best_path = []

    visited = [False] * n
    visited[0] = True
    path = [0]

    def bnb(curr_city, count, curr_cost):
        nonlocal best_cost, best_path

        # If all cities visited → close the tour
        if count == n:
            total_cost = curr_cost + dist[curr_city][0]  # return to start
            if total_cost < best_cost:
                best_cost = total_cost
                best_path = path[:] + [0]
            return

        # Branch: try all next cities
        for nxt in range(n):
            if not visited[nxt]:
                new_cost = curr_cost + dist[curr_city][nxt]

                # Bound: prune if cost already exceeds best known
                if new_cost >= best_cost:
                    continue

                visited[nxt] = True
                path.append(nxt)

                bnb(nxt, count + 1, new_cost)

                # Backtrack
                visited[nxt] = False
                path.pop()

    bnb(0, 1, 0)
    return best_cost, best_path


# INPUT
n = int(input("Enter number of cities: "))
print("Enter distance matrix:")
dist = [list(map(int, input().split())) for _ in range(n)]

cost, path = tsp_branch_and_bound(dist)
print("Branch & Bound Tour Cost:", cost)
print("Path:", path)

'''
use this test case
4
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0
--------------
algorithm:
1. Start from city 0. Mark it visited and add it to the path.

2. Use a recursive function:
      bnb(currentCity, countVisited, currentCost)

3. If countVisited == n:
       - Add cost to return to city 0.
       - Update bestCost and bestPath if this tour is better.
       - Return.

4. Else:
       For each unvisited city:
           a. Calculate newCost = currentCost + distance.
           b. IF newCost >= bestCost: prune this branch.
           c. Otherwise:
                  - Mark the city visited
                  - Add city to path
                  - Recurse (bnb)
                  - Backtrack (unvisit, pop path)

5. After exploring all branches, return bestCost and bestPath.
--------------
Worst Case: O(n!)
Best Case (with good pruning): Much faster
--------------
O(n)

Reason:
- visited array → O(n)
- path array → O(n)
- recursion depth → O(n)

'''