/*PseudoCode:
function jobScheduling(jobs, n):
    sort jobs by profit descending
    maxDeadline = max(jobs.deadline)
    create slots[1..maxDeadline] = empty
    totalProfit = 0

    for job in jobs:
        for t = job.deadline downto 1:
            if slot[t] empty:
                slot[t] = job
                totalProfit += job.profit
                break
    return totalProfit
*/


// code
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job {
    int id, deadline, profit;
};

bool cmp(Job a, Job b) {
    return a.profit > b.profit;
}

int jobScheduling(vector<Job>& jobs) {
    sort(jobs.begin(), jobs.end(), cmp);

    int maxDeadline = 0;
    for (auto &j : jobs)
        maxDeadline = max(maxDeadline, j.deadline);

    vector<int> slot(maxDeadline + 1, -1);
    int totalProfit = 0;

    for (auto &j : jobs) {
        for (int t = j.deadline; t > 0; t--) {
            if (slot[t] == -1) {
                slot[t] = j.id;
                totalProfit += j.profit;
                break;
            }
        }
    }
    return totalProfit;
}

int main() {
    int n;
    cout << "Enter number of jobs: ";
    cin >> n;

    vector<Job> jobs(n);
    cout << "Enter job ID, deadline and profit for each job:\n";
    for (int i = 0; i < n; i++)
        cin >> jobs[i].id >> jobs[i].deadline >> jobs[i].profit;

    cout << "Maximum Profit: " << jobScheduling(jobs) << endl;
    return 0;
}

/*
5
1 2 100
2 1 19
3 2 27
4 1 25
5 3 15
*/

/*📌 Time Complexity
Sorting jobs by profit → O(n log n)
Scheduling jobs (nested loop worst case) → O(n × d), where d = maximum deadline

Total Time Complexity:O(nlogn+n⋅d)

📌 Space Complexity
Job array → O(n)
Slot array → O(d)

O(n+d)*/