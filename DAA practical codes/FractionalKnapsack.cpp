#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int value, weight;
};

bool cmp(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}

double fractionalKnapsack(int W, vector<Item>& items) {
    sort(items.begin(), items.end(), cmp);

    double totalValue = 0.0;

    for (auto &it : items) {
        if (W >= it.weight) {
            totalValue += it.value;
            W -= it.weight;
        } else {
            totalValue += it.value * ((double)W / it.weight);
            break;
        }
    }
    return totalValue;
}

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;

    vector<Item> items(n);
    cout << "Enter value and weight of each item:\n";
    for (int i = 0; i < n; i++) {
        cin >> items[i].value >> items[i].weight;
    }

    cout << "Enter maximum capacity of knapsack: ";
    cin >> W;

    cout << "Maximum value: " << fractionalKnapsack(W, items) << endl;
    return 0;
}

/*
3
60 10
100 20
120 30
50
*/

/*
Time Complexity
Sorting items by value/weight ratio → O(n log n)
Iterating through items → O(n)
Total:O(nlogn)

Space Complexity
Storing items in a vector → O(n)
No other significant extra space.
O(n)​
*/