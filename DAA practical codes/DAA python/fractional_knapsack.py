def fractional_knapsack(capacity, values, weights):
    # Create list of (value, weight, ratio)
    items = []
    for v, w in zip(values, weights):
        items.append((v, w, v / w))

    # Sort by ratio (value/weight) in descending order
    items.sort(key=lambda x: x[2], reverse=True)

    total_value = 0.0

    for v, w, ratio in items:
        if capacity == 0:
            break

        # Take full item
        if w <= capacity:
            total_value += v
            capacity -= w
        else:  
            # Take fractional part
            total_value += ratio * capacity
            capacity = 0

    return total_value


# --------------------- USER INPUT -----------------------
n = int(input("Enter number of items: "))

values = []
weights = []

print("Enter value and weight of each item:")
for _ in range(n):
    v, w = map(int, input().split())
    values.append(v)
    weights.append(w)

capacity = int(input("Enter maximum capacity of knapsack: "))

result = fractional_knapsack(capacity, values, weights)
print("Maximum value:", result)


'''
Time Complexity
Sorting items by value/weight ratio → O(n log n)
Iterating through items → O(n)
Total:O(nlogn)
-----------------
Space Complexity
Storing items in a vector → O(n)
No other significant extra space.
O(n)​
'''