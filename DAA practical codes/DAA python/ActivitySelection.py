def activity_selection():
    # Input
    n = int(input("Enter number of activities: "))
    
    activities = []
    print("Enter start and finish times:")
    for _ in range(n):
        s, f = map(int, input().split())
        activities.append((s, f))

    # Step 1: Sort by finish time
    activities.sort(key=lambda x: x[1])

    # Step 2: Select activities greedily
    selected = []
    last_finish = -1

    for s, f in activities:
        if s >= last_finish:
            selected.append((s, f))
            last_finish = f

    # Output
    print("Selected Activities:")
    for s, f in selected:
        print(f"({s}, {f})", end=" ")
    print()


'''
Algorithm: Activity Selection (Greedy)

1. Read n activities, each with (start, finish).
2. Sort all activities in increasing order of finish time.
3. Select the first activity and set last_finish = its finish time.
4. For every remaining activity:
       If activity.start >= last_finish:
            Select the activity
            Update last_finish = activity.finish
5. Output all selected activities.
---------------------------------------
Time complexity: 
Sorting activities:   O(n log n)
Selecting activities: O(n)

Total:                O(n log n)
----------------------------------
Space Complexity:
Storing activities:    O(n)
Selected list:         O(n)

Total:                 O(n)

'''