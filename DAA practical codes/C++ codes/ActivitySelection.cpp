/*Pseudocode:
function activitySelection(start[], finish[], n):
    sort activities by finish time
    result = [first activity]
    last_finish = finish[0]

    for i = 1 to n-1:
        if start[i] >= last_finish:
            result.append(activity[i])
            last_finish = finish[i]
    return result
*/

// Code
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Activity {
    int start, finish;
};

bool cmp(Activity a, Activity b) {
    return a.finish < b.finish;
}

void activitySelection(vector<Activity>& activities) {
    sort(activities.begin(), activities.end(), cmp);

    cout << "Selected Activities: ";
    int last_finish = activities[0].finish;
    cout << "(" << activities[0].start << "," << activities[0].finish << ") ";

    for (int i = 1; i < activities.size(); i++) {
        if (activities[i].start >= last_finish) {
            cout << "(" << activities[i].start << "," << activities[i].finish << ") ";
            last_finish = activities[i].finish;
        }
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of activities: ";
    cin >> n;

    vector<Activity> activities(n);

    cout << "Enter start and finish time for each activity:\n";
    for (int i = 0; i < n; i++) {
        cin >> activities[i].start >> activities[i].finish;
    }

    activitySelection(activities);
    return 0;
}


/*INput:
7
1 3
2 4
3 5
0 6
5 7
8 9
5 9
*/

/*Time Complexity
1. Sorting:
sort() takes O(n log n)
2. Selecting Activities:
The loop runs once → O(n)
Total: O(n log n)+O(n)=O(n log n)
	​
SC= O(n)​
*/