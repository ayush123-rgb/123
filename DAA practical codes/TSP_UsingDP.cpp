// TSP(Travelling Salesperson) using DP + Bitmasking

#include <iostream>
#include <vector>
using namespace std;

#define INF 999999

int tsp(int n, vector<vector<int>>& cost) {
    int N = 1 << n; // 2^n
    vector<vector<int>> dp(N, vector<int>(n, INF));
    dp[1][0] = 0; // start from city 0

    for (int mask = 1; mask < N; mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u))) continue; 
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue; 
                int newMask = mask | (1 << v);
                dp[newMask][v] = min(dp[newMask][v], dp[mask][u] + cost[u][v]);
            }
        }
    }

    int ans = INF;
    for (int i = 1; i < n; i++)
        ans = min(ans, dp[(1 << n) - 1][i] + cost[i][0]); // return to start

    return ans;
}

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    vector<vector<int>> cost(n, vector<int>(n));

    cout << "\nEnter cost matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
        }
    }

    cout << "\nMinimum Cost of Traveling Salesperson: " 
         << tsp(n, cost) << endl;

    return 0;
}


/*
Example input:
4
0 20 42 25
20 0 30 34
42 30 0 10
25 34 10 0
*/

/*Pseudocode
TSP(cost, n):
    dp[2^n][n] = INF
    dp[1][0] = 0  // starting from city 0 with only city 0 visited

    for mask from 1 to (1 << n) - 1:
        for u from 0 to n-1:
            if (mask & (1 << u)) == 0:
                continue
            for v from 0 to n-1:
                if (mask & (1 << v)) == 0:
                    newMask = mask | (1 << v)
                    dp[newMask][v] = min(dp[newMask][v], dp[mask][u] + cost[u][v])

    // Return to starting city
    answer = INF
    for i from 1 to n-1:
        answer = min(answer, dp[(1<<n)-1][i] + cost[i][0])

    return answer
*/

/*| Type                 | Complexity     | Explanation                                                                                          |
| -------------------- | -------------- | ---------------------------------------------------------------------------------------------------- |
| **Time Complexity**  | **O(n² × 2ⁿ)** | For every subset of cities (`2ⁿ`), we consider `n` possible last cities and `n` possible next cities |
| **Space Complexity** | **O(n × 2ⁿ)**  | DP table storing cost for each subset–city pair                                                      |
*/


/*
Algo:
1. Let N = 2^n.
2. Create dp[0..N-1][0..n-1], initialize all entries = INF.
3. Set dp[1 << 0][0] = 0.   // mask with only city 0 visited, end at city 0

4. // Build DP over all visited-sets (bitmasks)
   for mask = 1 to N-1:
       for u = 0 to n-1:
           if (mask does not contain u) continue   // u not an end-city for this mask
           // try to go from u to any unvisited v
           for v = 0 to n-1:
               if (mask contains v) continue      // v already visited
               newMask = mask OR (1 << v)
               dp[newMask][v] = min(dp[newMask][v], dp[mask][u] + cost[u][v])

5. // All cities visited mask = N-1. Close the tour by returning to 0
   ans = INF
   for last = 1 to n-1:
       ans = min(ans, dp[N-1][last] + cost[last][0])

6. Return ans
*/