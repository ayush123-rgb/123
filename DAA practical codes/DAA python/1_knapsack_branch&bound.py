class Node:
    def __init__(self, level, value, weight, items):
        self.level = level      # which item index
        self.value = value
        self.weight = weight
        self.items = items      # list of selected item indices


# Compute the upper bound (best possible value from this node)
def bound(node, values, weights, capacity):
    if node.weight >= capacity:
        return 0   # cannot add anything

    total_value = node.value
    total_weight = node.weight
    n = len(values)

    i = node.level + 1

    # Add full items greedily
    while i < n and total_weight + weights[i] <= capacity:
        total_weight += weights[i]
        total_value += values[i]
        i += 1

    # Add fraction of next item (for bound only)
    if i < n:
        total_value += (capacity - total_weight) * (values[i] / weights[i])

    return total_value


def knapsack_branch_and_bound(values, weights, capacity):
    n = len(values)

    # Sort items by value/weight ratio (best first)
    ratio_items = sorted(
        list(range(n)),
        key=lambda i: values[i] / weights[i],
        reverse=True
    )

    # Reorder values and weights
    values = [values[i] for i in ratio_items]
    weights = [weights[i] for i in ratio_items]

    # BFS queue
    from collections import deque
    Q = deque()

    # Start with root node
    root = Node(level=-1, value=0, weight=0, items=[])
    Q.append(root)

    max_value = 0
    best_items = []

    while Q:
        node = Q.popleft()

        # Next level = try next item
        next_level = node.level + 1
        if next_level >= n:
            continue

        # -----------------------------
        # 1) Include the next item
        # -----------------------------
        include_value = node.value + values[next_level]
        include_weight = node.weight + weights[next_level]
        include_items = node.items + [next_level]

        if include_weight <= capacity:
            if include_value > max_value:
                max_value = include_value
                best_items = include_items

            new_node = Node(next_level, include_value, include_weight, include_items)

            # Check bound before adding to queue
            if bound(new_node, values, weights, capacity) > max_value:
                Q.append(new_node)

        # -----------------------------
        # 2) Exclude the next item
        # -----------------------------
        exclude_node = Node(next_level, node.value, node.weight, node.items)

        if bound(exclude_node, values, weights, capacity) > max_value:
            Q.append(exclude_node)

    # Convert sorted indices back to original indices
    selected_original_indices = [ratio_items[i] + 1 for i in best_items]

    return max_value, sorted(selected_original_indices)


print("🔹 0/1 Knapsack Using Branch & Bound")

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

max_value, items = knapsack_branch_and_bound(values, weights, capacity)

print("\nMaximum value =", max_value)
print("Items selected =", items)


'''
Branch and Bound (0/1 Knapsack):
Algorithm:
1. Sort items by value/weight ratio.
2. Create root node (level=-1, profit=0, weight=0, bound computed).
3. Push root into queue.
4. While queue not empty:
      Pop node v.
      Create left child (include item). Update max_profit if valid. If bound > max_profit, push.
      Create right child (exclude item). If bound > max_profit, push.
5. Final max_profit is optimal.

Time Complexity: Best O(n log n), Worst O(2^n)
Space Complexity: Average O(n), Worst O(2^n)
'''