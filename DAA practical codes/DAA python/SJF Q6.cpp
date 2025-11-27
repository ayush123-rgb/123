/*
---------------------------------------------------------
     VEHICLE WAITING TIME (ONLY ARRIVAL TIME INPUT)
---------------------------------------------------------

ALGORITHM:
1. Take arrival times from user.
2. Sort vehicles by arrival time.
3. The first vehicle has waiting time = 0.
4. For every next vehicle:
       waiting = (finish time of previous vehicle) - arrival time
       if waiting < 0 → set waiting = 0 (no waiting)
5. Sum all waiting times.

---------------------------------------------------------
SAMPLE INPUT:
Enter number of vehicles: 4
Enter arrival times:
0
3
7
10

SAMPLE OUTPUT:
Vehicle 0 arrival = 0 wait = 0
Vehicle 1 arrival = 3 wait = 0
Vehicle 2 arrival = 7 wait = 0
Vehicle 3 arrival = 10 wait = 0
Total waiting time = 0
---------------------------------------------------------
*/

#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of vehicles: ";
    cin >> n;

    int arr[50], id[50];

    cout << "Enter arrival times:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        id[i] = i;
    }

    // sort by arrival time
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[i]) {
                int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
                int t2 = id[i]; id[i] = id[j]; id[j] = t2;
            }
        }
    }

    int total_wait = 0;
    int finish_time = arr[0];

    cout << "\nVehicle Processing Order:\n";

    cout << "Vehicle " << id[0] << " arrival = " << arr[0] 
         << " wait = 0\n";

    for (int i = 1; i < n; i++) {
        int wait = finish_time - arr[i];
        if (wait < 0) wait = 0;

        total_wait += wait;

        cout << "Vehicle " << id[i]
             << " arrival = " << arr[i]
             << " wait = " << wait << "\n";

        finish_time = arr[i];
    }

    cout << "\nTotal waiting time = " << total_wait << endl;

    return 0;
}
