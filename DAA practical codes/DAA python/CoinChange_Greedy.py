def greedy_change():
    # Input
    n = int(input("Enter number of denominations: "))

    print("Enter denominations:")
    denom = list(map(int, input().split()))

    print("Enter available counts for each denomination:")
    count = list(map(int, input().split()))

    target = int(input("Enter target amount: "))

    # Make pairs and sort by denomination from big to small
    coins = []
    for i in range(n):
        coins.append([denom[i], count[i]])   # [value, available]

    coins.sort(reverse=True)  # sort by value descending

    used = []                 # to store how many we take for each coin
    remaining = target

    # Greedy selection
    for value, available in coins:
        can_take = remaining // value       # max possible for this coin
        take = min(can_take, available)     # but limited by availability
        used.append(take)
        remaining -= take * value

    # Output
    print("\n--- GREEDY RESULT ---")
    if remaining == 0:
        print("Change is possible!")
        total = 0
        for i in range(n):
            print(f"Coin {coins[i][0]}: used {used[i]}")
            total += used[i]
        print("Total coins used:", total)
    else:
        print("Greedy FAILED. Cannot make exact change.")

    # Greedy failure example
    print("\n--- Example where Greedy Fails ---")
    print("Denominations: 1 3 4")
    print("Counts: 10 10 10")
    print("Target: 6")
    print("Greedy gives 4 + 1 + 1 = 3 coins")
    print("Optimal is 3 + 3 = 2 coins")


# Run
greedy_change()


'''
Algorithm: Greedy Change with Limited Coins

1. Read the number of denominations n.

2. Read the list of denominations.
   Read the list of available counts for each denomination.

3. Read the target amount.

4. Create a list of pairs (denomination, count).

5. Sort this list in descending order of denomination value.

6. Initialize:
      used = empty list
      remaining = target

7. For each coin (value, available) in the sorted list:
       a. Calculate can_take = remaining // value
       b. take = min(can_take, available)
       c. Append take to used
       d. remaining = remaining - (take * value)

8. If remaining == 0:
       Output that change is possible and print the coins used.
   Else:
       Output that greedy failed to make exact change.

9. End.
-------
Time Complexity:

1. Sorting the denominations:       O(n log n)
2. Greedy iteration over coins:     O(n)

Total Time Complexity = O(n log n)
---------
Space Complexity:

1. Storing denominations and counts:     O(n)
2. Storing coin pairs:                   O(n)
3. Used array:                           O(n)

Total Space Complexity = O(n)
'''

