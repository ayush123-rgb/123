#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cout << "Enter number of coin denominations: ";// how many different types of coins you have
    cin >> n;

    vector<int> denom(n), count(n);
    cout << "Enter denominations: ";//This means you enter the actual coin values.
    for (int i = 0; i < n; i++) cin >> denom[i];

    cout << "Enter counts available for each denomination: "; //How many coins of each type do you have
    for (int i = 0; i < n; i++) cin >> count[i];

    int target;
    cout << "Enter target amount: ";
    cin >> target;

    // Sort coins in descending order for greedy
    vector<pair<int,int>> coins;
    for (int i = 0; i < n; i++)
        coins.push_back({denom[i], count[i]});

    sort(coins.rbegin(), coins.rend());  // largest to smallest

    vector<int> used(n, 0);
    int remaining = target;

    // Greedy algorithm
    for (int i = 0; i < n; i++) {
        int coin = coins[i].first;
        int avail = coins[i].second;

        int take = min(avail, remaining / coin);  // take as many as possible
        used[i] = take;
        remaining -= take * coin;
    }

    cout << "\n--- GREEDY RESULT ---\n";
    if (remaining == 0) {
        cout << "Change is possible using greedy.\n";
        int totalCoins = 0;

        for (int i = 0; i < n; i++) {
            cout << "Coin " << coins[i].first << ": " << used[i] << " used\n";
            totalCoins += used[i];
        }
        cout << "Total coins used = " << totalCoins << "\n";
    }
    else {
        cout << "Greedy FAILED. Cannot make change with given coins.\n";
    }

    cout << "\n--- TEST CASES TO SEE WHERE GREEDY FAILS ---\n";
    cout << "Try this:\n";
    cout << "Denominations: 1 3 4\nCounts: 10 10 10\nTarget: 6\n";
    cout << "Greedy result: 4 + 1 + 1 (3 coins) but optimal is 3 + 3 (2 coins)\n";

    return 0;
}

/*
input example:
4
25 10 5 1
2 3 5 10
63
*/
/*
⭐ Time Complexity
1. Sorting Step
Sorting the denominations in descending order:O(n log n)
2. Greedy Loop
For each denomination, simple arithmetic and comparisons:O(n)
Total Time Complexity: O(n log n) + O(n) = O(n log n)

Space Complexity
Only a few arrays of size n: O(n)

*/

/*Why Greedy Fails Sometimes
Greedy picks the highest denomination first, which is not always optimal when:
A smaller denomination combination gives fewer coins
Or limited counts restrict greedy's choices
Example (classic failure):
Denominations: 1, 3, 4
Target = 6
Greedy → 4 + 1 + 1 = 3 coins
Optimal → 3 + 3 = 2 coins
*/

/*
Algorithm:
1. Input n (number of denominations)
2. Input the list of denominations D[0..n−1]
3. Input the list of available counts C[0..n−1]
4. Input the target amount T
5. Pair coins as (denomination, count)
6. Sort the coins in descending order of denomination
7. Initialize remaining = T
   Initialize used[i] = 0 for all i
8. For each coin i in sorted order:
        a. coinValue = denomination[i]
        b. maxPossible = remaining / coinValue
        c. take = minimum of (maxPossible, C[i])
        d. used[i] = take
        e. remaining = remaining − take * coinValue
9. If remaining == 0:
        Greedy is feasible
        Output coins used and total count
   Else:
        Greedy fails (cannot make exact change)
10. End
*/