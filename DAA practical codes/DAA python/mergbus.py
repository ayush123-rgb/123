"""
---------------------------------------------------------
      MERGE SORT - BUS TICKET PRICE SORTING
---------------------------------------------------------

SAMPLE INPUT:
Enter number of ticket prices: 5
Enter ticket prices: 120 45 60 30 250

SAMPLE OUTPUT:
Sorted ticket prices (cheapest first):
30 45 60 120 250
---------------------------------------------------------
"""

def merge(arr, l, m, r):
    left = arr[l:m+1]
    right = arr[m+1:r+1]

    i = j = 0
    k = l

    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            arr[k] = left[i]
            i += 1
        else:
            arr[k] = right[j]
            j += 1
        k += 1

    while i < len(left):
        arr[k] = left[i]
        i += 1
        k += 1

    while j < len(right):
        arr[k] = right[j]
        j += 1
        k += 1

def mergeSort(arr, l, r):
    if l < r:
        m = (l + r) // 2
        mergeSort(arr, l, m)
        mergeSort(arr, m + 1, r)
        merge(arr, l, m, r)

print("Enter number of ticket prices:", end=" ")
n = int(input())

print("Enter ticket prices:", end=" ")
data = list(map(int, input().split()))

mergeSort(data, 0, n - 1)

print("\nSorted ticket prices (cheapest first):")
for x in data:
    print(x, end=" ")
