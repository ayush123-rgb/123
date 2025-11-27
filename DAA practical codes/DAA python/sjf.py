"""
---------------------------------------------------------
     VEHICLE WAITING TIME (ONLY ARRIVAL TIME INPUT)
---------------------------------------------------------

ALGORITHM:
1. Read arrival times only.
2. Sort vehicles by arrival time.
3. First vehicle waits 0.
4. Next vehicle waiting = previous finish - arrival
   If negative, set waiting = 0.
5. Add all waiting times.
---------------------------------------------------------
"""

print("Enter number of vehicles:", end=" ")
n = int(input())

arrival = []
index = []

print("Enter arrival times:")
for i in range(n):
    a = int(input())
    arrival.append(a)
    index.append(i)

# sort by arrival time
for i in range(n):
    for j in range(i + 1, n):
        if arrival[j] < arrival[i]:
            arrival[i], arrival[j] = arrival[j], arrival[i]
            index[i], index[j] = index[j], index[i]

print("\nVehicle Processing Order:")
total_wait = 0
finish = arrival[0]

print("Vehicle", index[0], "arrival =", arrival[0], "wait = 0")

for i in range(1, n):
    wait = finish - arrival[i]
    if wait < 0:
        wait = 0

    total_wait += wait

    print("Vehicle", index[i], 
          "arrival =", arrival[i], 
          "wait =", wait)

    finish = arrival[i]

print("\nTotal waiting time =", total_wait)
