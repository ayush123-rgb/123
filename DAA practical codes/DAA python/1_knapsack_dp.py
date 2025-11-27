def knapsack_dp(values, weights, capacity):
    n = len(values)

    dp = [[0] * (capacity + 1) for _ in range(n + 1)]

    for i in range(1, n + 1):
        for w in range(1, capacity + 1):
            if weights[i - 1] <= w:
                include = values[i - 1] + dp[i - 1][w - weights[i - 1]]
                exclude = dp[i - 1][w]
                dp[i][w] = max(include, exclude)
            else:
                dp[i][w] = dp[i - 1][w]

    selected_items = []
    w = capacity

    for i in range(n, 0, -1):
    
        if dp[i][w] == dp[i - 1][w]:
            continue
        else:
            
            selected_items.append(i) 
            w -= weights[i - 1]

    selected_items.reverse()  

    return dp[n][capacity], selected_items


print("0/1 Knapsack Using DP (With Item Selection)")

n = int(input("Enter number of items: "))

values = []
weights = []

print("\nEnter value and weight for each item:")
for i in range(n):
    v = int(input(f"Value of item {i+1}: "))
    w = int(input(f"Weight of item {i+1}: "))
    values.append(v)
    weights.append(w)

capacity = int(input("\nEnter knapsack capacity: "))

max_value, items = knapsack_dp(values, weights, capacity)

print("\nMaximum value you can carry =", max_value)
print("Items selected =", items)


'''
Dynamic Programming (0/1 Knapsack):
Algorithm:
1. Create dp[n+1][W+1].
2. Initialize first row and column to 0.
3. For i=1..n:
      For w=1..W:
         If weights[i-1] ≤ w:
            dp[i][w] = max(values[i-1] + dp[i-1][w - weights[i-1]], dp[i-1][w])
         Else:
            dp[i][w] = dp[i-1][w]
4. Answer = dp[n][W].

Time Complexity: O(nW)
Space Complexity: O(nW)
'''