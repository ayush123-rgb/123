# Traveling Salesman Problem using DP + Bitmasking
# Easy version WITH PATH reconstruction (fixed)

INF = 10**9

def tsp_dp(dist):
    n = len(dist)
    if n == 0:
        return 0, []

    # dp[mask][i] = min cost to reach city i with visited set = mask
    dp = [[INF] * n for _ in range(1 << n)]
    parent = [[-1] * n for _ in range(1 << n)]   # to store path

    dp[1][0] = 0   # start from city 0, mask with only city 0 visited

    for mask in range(1 << n):
        for last in range(n):
            # skip states where 'last' isn't actually in mask or state unreachable
            if (mask & (1 << last)) == 0 or dp[mask][last] == INF:
                continue

            # try to go to next city
            for nxt in range(n):
                if (mask & (1 << nxt)) == 0:        # nxt not visited
                    new_mask = mask | (1 << nxt)
                    new_cost = dp[mask][last] + dist[last][nxt]

                    if new_cost < dp[new_mask][nxt]:
                        dp[new_mask][nxt] = new_cost
                        parent[new_mask][nxt] = last

    # close the tour (return to 0)
    full_mask = (1 << n) - 1
    final_cost = INF
    last_city = -1

    for last in range(n):
        if dp[full_mask][last] == INF:
            continue
        cost = dp[full_mask][last] + dist[last][0]
        if cost < final_cost:
            final_cost = cost
            last_city = last

    # if no tour found (shouldn't happen for fully connected graphs)
    if last_city == -1:
        return None, []

    # Reconstruct path: we will build reversed path (last -> ... -> 0)
    path_rev = []
    mask = full_mask
    cur = last_city

    while cur != -1:
        path_rev.append(cur)
        prev = parent[mask][cur]
        mask = mask ^ (1 << cur)   # remove cur from mask
        cur = prev

    # Now path_rev is [last, ..., 0]
    path_rev.reverse()          # becomes [0, ..., last]
    path_rev.append(0)          # close the tour by returning to start

    return final_cost, path_rev


# INPUT (easy)
n = int(input("Enter number of cities: "))
print("Enter distance matrix row by row:")
dist = [list(map(int, input().split())) for _ in range(n)]

cost, path = tsp_dp(dist)
if cost is None:
    print("No valid tour found.")
else:
    print("Minimum travelling cost:", cost)
    print("Path:", path)


'''
use this test case
4
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0
---------
Algorithm: 
1. Read number of cities n and the distance matrix.
2. Create a DP table dp[2^n][n], where:
      dp[mask][i] = minimum cost to reach city i after visiting cities in mask.
3. Initialize dp[1][0] = 0 (start at city 0).
4. For each mask from 0 to 2^n - 1:
       For each city 'last' in mask:
            For each city 'next' not in mask:
                Update dp[new_mask][next] by:
                   dp[new_mask][next] = min(
                       dp[new_mask][next],
                       dp[mask][last] + dist[last][next]
                   )
5. After filling DP table:
       For every last city:
            Add the cost to return from last → 0.
6. Minimum of these is the final TSP tour cost.
-------
time complexity: 
O(n^2 * 2^n)

Reason:
- There are 2^n masks
- For each mask we try n cities as last
- For each we try n possible next cities
----------
space complexity:
O(n * 2^n)

Reason:
- DP table of size [2^n][n]
-----------
'''