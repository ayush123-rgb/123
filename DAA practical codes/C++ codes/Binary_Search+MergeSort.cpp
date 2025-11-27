#include <bits/stdc++.h>
using namespace std;

// ---------------- MERGE SORT ----------------

void merge(vector<int>& arr, int low, int mid, int high) {
    vector<int> temp;
    int left = low;
    int right = mid + 1;

    while (left <= mid && right <= high) {
        if (arr[left] < arr[right]) {
            temp.push_back(arr[left]);
            left++;
        } else {
            temp.push_back(arr[right]);
            right++;
        }
    }

    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}

void MS(vector<int>& arr, int low, int high) {
    if (low >= high) return;
    int mid = low + (high - low) / 2;
    MS(arr, low, mid);
    MS(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

void MergeSort(vector<int>& arr) {
    MS(arr, 0, arr.size() - 1);
}

// ---------------- RECURSIVE BINARY SEARCH ----------------

int recursive(vector<int>& nums, int low, int high, int target) {
    if (low > high) return -1;
    int mid = (low + high) / 2;

    if (nums[mid] == target)
        return mid;
    else if (target > nums[mid])
        return recursive(nums, mid + 1, high, target);
    else
        return recursive(nums, low, mid - 1, target);
}

int BSRM(vector<int>& nums, int target) {
    return recursive(nums, 0, nums.size() - 1, target);
}

// ---------------- MAIN FUNCTION ----------------

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int target;
    cin >> target;

    // Sorting
    MergeSort(arr);

    cout << "After Sorting: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    // Binary Search (Recursive)
    int index = BSRM(arr, target);

    if (index != -1)
        cout << "Element found at index: " << index << endl;
    else
        cout << "Element not found." << endl;

    return 0;
}


/*
Merge Sort: O(n log n)
Binary Search: O(log n)
Overall: O(n log n) (since sorting dominates)*/