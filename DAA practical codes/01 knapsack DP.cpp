#include <iostream>
using namespace std;

int knapsack(int values[], int weights[], int n, int W) {
    int dp[n + 1][W + 1];

    // Step 1: Build DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    // Step 2: Find which items are included
    int res = dp[n][W];   // Final maximum value
    int w = W;

    cout << "Maximum Value: " << res << endl;
    cout << "Items included (1-indexed): ";

    for (int i = n; i > 0 && res > 0; i--) {
        if (res == dp[i - 1][w])
            continue;  // Item not included
        else {
            cout << i << " ";  // Item included (1-indexed)
            res -= values[i - 1];
            w -= weights[i - 1];
        }
    }
    cout << endl;

    return dp[n][W];
}

int main() {
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    int values[n], weights[n];

    cout << "Enter values of items:\n";
    for (int i = 0; i < n; i++)
        cin >> values[i];

    cout << "Enter weights of items:\n";
    for (int i = 0; i < n; i++)
        cin >> weights[i];

    cout << "Enter knapsack capacity W: ";
    cin >> W;

    knapsack(values, weights, n, W);

    return 0;
}


/*Pseudocode
0/1_Knapsack(values[], weights[], n, W):
    Create a 2D array dp[n+1][W+1]

    for i from 0 to n:
        for w from 0 to W:
            if i == 0 or w == 0:
                dp[i][w] = 0
            else if weights[i-1] <= w:
                dp[i][w] = max(values[i-1] + dp[i-1][w - weights[i-1]], dp[i-1][w])
            else:
                dp[i][w] = dp[i-1][w]

    return dp[n][W]
*/

/*| Type                 | Complexity   | Explanation                                           |
| -------------------- | ------------ | ----------------------------------------------------- |
| **Time Complexity**  | **O(n × W)** | Two nested loops — one for items and one for capacity |
| **Space Complexity** | **O(n × W)** | DP table of size `(n+1) × (W+1)`                      |
*/


/*
Algo:
1. Create a DP table dp of size (n+1) × (W+1)

2. Fill the DP table:
      For i = 0 to n:
          For w = 0 to W:
              a) If i = 0 or w = 0:
                     dp[i][w] = 0       // no items or zero capacity
              b) Else if weights[i−1] ≤ w:
                     // choose max of including or excluding item i
                     dp[i][w] = max( values[i−1] + dp[i−1][w − weights[i−1]],
                                     dp[i−1][w] )
              c) Else:
                     dp[i][w] = dp[i−1][w]    // item too heavy

3. The final maximum profit = dp[n][W]
4. Return dp[n][W] as the answer.
*/