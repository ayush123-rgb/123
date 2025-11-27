
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

pair<int, vector<int>> tspGreedy(vector<vector<int>>& dist, int start = 0) {
    int n = dist.size();
    vector<bool> visited(n, false);
    vector<int> path;
    int total_cost = 0;

    int current = start;
    visited[start] = true;
    path.push_back(start);

    for (int i = 0; i < n - 1; i++) {
        int next_city = -1;
        int min_dist = numeric_limits<int>::max();

        for (int city = 0; city < n; city++) {
            if (!visited[city] && dist[current][city] < min_dist) {
                min_dist = dist[current][city];
                next_city = city;
            }
        }

        path.push_back(next_city);
        visited[next_city] = true;
        total_cost += min_dist;
        current = next_city;
    }

    // return to starting city
    total_cost += dist[current][start];
    path.push_back(start);

    return {total_cost, path};
}

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    vector<vector<int>> dist(n, vector<int>(n));
    cout << "Enter distance matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dist[i][j];

    auto res = tspGreedy(dist);

    cout << "Greedy Tour Cost: " << res.first << endl;
    cout << "Path: ";
    for (int city : res.second)
        cout << city << " ";
    cout << endl;

    return 0;
}


/*
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
*/