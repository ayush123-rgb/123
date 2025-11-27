#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Greedy Coin Change Function
int coin_change(const vector<int> &coins, int target, vector<int> &chosen) {
    vector<int> sortedCoins = coins;
    sort(sortedCoins.rbegin(), sortedCoins.rend());  // sort in descending order

    int sum = 0;
    int count = 0;

    for (int coin : sortedCoins) {
        while (sum + coin <= target) {
            sum += coin;
            chosen.push_back(coin);
            count++;
        }
        if (sum == target) break;
    }

    if (sum != target) {
        chosen.clear();
        return -1;  // no exact solution possible
    }

    return count;
}

int main() {
    cout << "===== Coin Change Calculator =====\n\n";

    int n, target;
    cout << "Enter number of coin denominations: ";
    cin >> n;

    vector<int> coins(n);
    cout << "Enter coin values:\n";
    for (int i = 0; i < n; i++) {
        cout << "Coin " << i + 1 << ": ";
        cin >> coins[i];
    }

    cout << "\nEnter target amount: ";
    cin >> target;

    vector<int> chosen;
    int result = coin_change(coins, target, chosen);

    cout << "\n----------------------------------\n";
    if (result == -1) {
        cout << "It is NOT possible to form the target using given coins.\n";
    } else {
        cout << "Minimum number of coins = " << result << endl;
        cout << "Coins used: ";
        for (int c : chosen) cout << c << " ";
        cout << endl;
    }
    cout << "----------------------------------\n";

    return 0;
}


/*
======================================================
⏳ TIME & SPACE COMPLEXITY
------------------------------------------------------
Time Complexity:
    Sorting coins: O(n log n)
    Greedy selection loop: O(n + k)
    (k = number of selected coins)
    Total: O(n log n)

Space Complexity:
    Extra vector for storing selection: O(n)

======================================================
📌 ALGORITHM (Steps)
------------------------------------------------------
1. Read number of coins and target amount.
2. Store all coin denominations in a vector.
3. Sort the coin values in descending order.
4. Initialize sum = 0 and count = 0.
5. For each coin in sorted list:
       While coin can be added without exceeding target:
            Increase sum by coin
            Add coin to result list
            Increment count
       If sum becomes equal to target, stop.
6. If sum != target, return -1 (change not possible).
7. Otherwise, return count and list of coins.

======================================================
🧾 PSEUDOCODE
------------------------------------------------------
FUNCTION coin_change(coins, target):
    sort coins in descending order
    sum = 0
    count = 0
    chosen = empty list

    FOR each coin in coins:
        WHILE sum + coin <= target:
            sum = sum + coin
            add coin to chosen
            count = count + 1
        IF sum == target:
            BREAK

    IF sum != target:
        return -1
    return count, chosen
======================================================
*/
