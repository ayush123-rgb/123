# ---------------------------
# Merge Sort Function
# ---------------------------
def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])
    
    return merge(left, right)


def merge(left, right):
    sorted_list = []
    i = j = 0

    # Compare elements of left and right
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            sorted_list.append(left[i])
            i += 1
        else:
            sorted_list.append(right[j])
            j += 1

    # Add remaining elements
    sorted_list.extend(left[i:])
    sorted_list.extend(right[j:])

    return sorted_list


# ---------------------------
# Binary Search Function
# ---------------------------
def binary_search(arr, target):
    low = 0
    high = len(arr) - 1

    while low <= high:
        mid = (low + high) // 2

        if arr[mid] == target:
            return mid  # Found at index mid
        
        elif arr[mid] < target:
            low = mid + 1  # Search right half
        
        else:
            high = mid - 1  # Search left half
    
    return -1  # Not found


# ---------------------------
# Main Program (User Input)
# ---------------------------
print("Enter numbers separated by spaces:")
user_input = input()

# Convert input string to list of integers
arr = list(map(int, user_input.split()))

print("\nSorting using Merge Sort...")
sorted_arr = merge_sort(arr)
print("Sorted Array:", sorted_arr)

# Ask user for number to search
target = int(input("\nEnter a number to search using Binary Search: "))

# Binary search works only on sorted array
index = binary_search(sorted_arr, target)

if index != -1:
    print(f"{target} found at index {index}")
else:
    print(f"{target} not found in the list.")


'''
✅ ALGORITHM (Merge Sort)
1. If array size is 0 or 1, return the array.
2. Divide the array into two halves:
      left = first half
      right = second half
3. Recursively sort the left half.
4. Recursively sort the right half.
5. Merge the two sorted halves:
      - Compare elements from left & right
      - Insert the smaller element into the new list
      - Append remaining elements
6. Return the merged sorted list.
⏳ Time Complexity

Best Case: O(n log n)

Average Case: O(n log n)

Worst Case: O(n log n)
(Merge Sort always divides the list log(n) times and merges n elements.)

📦 Space Complexity

O(n) (extra array used during merging)
-----------
✅ ALGORITHM (Binary Search)
1. Set low = 0 and high = n-1.
2. While low <= high:
      mid = (low + high) // 2
3. If arr[mid] == target:
      return mid
4. If arr[mid] < target:
      search in right half → low = mid + 1
5. Else:
      search in left half → high = mid - 1
6. If loop ends, return -1 (not found)

⏳ Time Complexity

Best Case: O(1)

Average Case: O(log n)

Worst Case: O(log n)

📦 Space Complexity

O(1) (no extra memory used)
'''