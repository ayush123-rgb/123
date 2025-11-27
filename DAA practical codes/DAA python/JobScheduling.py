def job_scheduling():
    # Input
    n = int(input("Enter number of jobs: "))

    jobs = []
    print("Enter job_id deadline profit:")
    for _ in range(n):
        j_id, d, p = map(int, input().split())
        jobs.append((p, d, j_id))   # store as (profit, deadline, id)

    # Step 1: Sort jobs by profit descending
    jobs.sort(reverse=True)

    # Step 2: Find maximum deadline
    max_deadline = max(d for _, d, _ in jobs)

    # Step 3: Create slots (1-based indexing)
    slot = [-1] * (max_deadline + 1)

    total_profit = 0

    # Step 4: Greedy scheduling
    for profit, deadline, job_id in jobs:
        # Try to schedule at latest possible time
        for t in range(deadline, 0, -1):
            if slot[t] == -1:
                slot[t] = job_id
                total_profit += profit
                break

    print("Maximum Profit:", total_profit)


'''
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
'''

