#include <bits/stdc++.h>
using namespace std;

struct Item {
    int weight, profit;
    double ratio;
};

struct Node {
    int level, profit, weight;
    double bound;
};

bool cmp(Item a, Item b) {
    return a.ratio > b.ratio;
}

// Compute upper bound on profit
double bound(Node u, int n, int W, vector<Item>& items) {
    if (u.weight >= W)
        return 0;

    double profit_bound = u.profit;
    int j = u.level;
    int totweight = u.weight;

    while ((j < n) && (totweight + items[j].weight <= W)) {
        totweight += items[j].weight;
        profit_bound += items[j].profit;
        j++;
    }

    if (j < n)
        profit_bound += (W - totweight) * items[j].ratio;

    return profit_bound;
}

int knapsack(int W, vector<Item>& items, int n) {
    sort(items.begin(), items.end(), cmp);

    queue<Node> Q;
    Node u, v;
    u.level = -1;
    u.profit = u.weight = 0;
    double maxProfit = 0;
    u.bound = bound(u, n, W, items);
    Q.push(u);

    while (!Q.empty()) {
        u = Q.front();
        Q.pop();

        if (u.level == n - 1)
            continue;

        v.level = u.level + 1;

        // Include next item
        v.weight = u.weight + items[v.level].weight;
        v.profit = u.profit + items[v.level].profit;

        if (v.weight <= W && v.profit > maxProfit)
            maxProfit = v.profit;

        v.bound = bound(v, n, W, items);
        if (v.bound > maxProfit)
            Q.push(v);

        // Exclude next item
        v.weight = u.weight;
        v.profit = u.profit;
        v.bound = bound(v, n, W, items);
        if (v.bound > maxProfit)
            Q.push(v);
    }

    return maxProfit;
}

int main() {
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items(n);

    cout << "Enter weight and profit of each item:\n";
    for (int i = 0; i < n; i++) {
        cin >> items[i].weight >> items[i].profit;
        items[i].ratio = (double)items[i].profit / items[i].weight;
    }

    cout << "Enter knapsack capacity W: ";
    cin >> W;

    cout << "Maximum Profit = " << knapsack(W, items, n);

    return 0;
}


/*Pseudocode
KNAPSACK_BnB(weights, profits, n, W):
    Sort items by profit/weight ratio
    Initialize maxProfit = 0
    Create root node with level = 0, profit = 0, weight = 0
    root.bound = getBound(root)
    Push root to priority queue

    while queue not empty:
        node = queue.pop()
        if node.bound > maxProfit:
            // Left child - include next item
            child.weight = node.weight + w[node.level]
            child.profit = node.profit + p[node.level]
            child.level = node.level + 1
            if child.weight <= W and child.profit > maxProfit:
                maxProfit = child.profit
            child.bound = getBound(child)
            if child.bound > maxProfit:
                queue.push(child)

            // Right child - exclude next item
            child.weight = node.weight
            child.profit = node.profit
            child.level = node.level + 1
            child.bound = getBound(child)
            if child.bound > maxProfit:
                queue.push(child)
    return maxProfit
*/

/*| Type                 | Complexity             | Explanation                                |
| -------------------- | ---------------------- | ------------------------------------------ |
| **Time Complexity**  | `O(2^n)` in worst case | But much faster in practice due to pruning |
| **Space Complexity** | `O(n)`                 | Due to recursion/queue and state storage   |
*/