# Sort

## QuickSort

Unstable

Average Time complexity: O(nlogn), worst time complexity: O(n^2)

Space complexity: O(logn)

```c++
#include <iostream>
#include <vector>
using namespace std;
 
int partition(vector<int>& arr,int low,int high)
{
  //choose the pivot
   
  int pivot=arr[high];
  //Index of smaller element and Indicate
  //the right position of pivot found so far
  int i=(low-1);
   
  for(int j=low;j<high;j++)
  {
    //If current element is smaller than the pivot
    if(arr[j]<pivot)
    {
      //Increment index of smaller element
      i++;
      swap(arr[i],arr[j]);
    }
  }
  swap(arr[i+1],arr[high]);
  return (i+1);
}
 
// The Quicksort function Implement
            
void quickSort(vector<int>& arr,int low,int high)
{
  // when low is less than high
  if(low<high)
  {
    // pi is the partition return index of pivot
     
    int pi=partition(arr,low,high);
     
    //Recursion Call
    //smaller element than pivot goes left and
    //higher element goes right
    quickSort(arr,low,pi-1);
    quickSort(arr,pi+1,high);
  }
}
```

## [CountingSort](https://oi-wiki.org/basic/counting-sort/)

![counting sort animate example](https://oi-wiki.org/basic/images/counting-sort-animate.svg)

```c++
// Stable
// Time complexity: O(n+k), k is max_val
// Time complexity: O(n+k)
void CountingSort(vector<int>& nums)
{
    int max_val = *std::max_element(nums.begin(), nums.end());
    vector<int> cnt(max_val+1, 0);
    vector<int> res(nums.size(), 0);
    for (int i = 0; i < nums.size(); i++) cnt[nums[i]]++;
    for (int i = 1; i <= max_val; i++) cnt[i] += cnt[i-1];
    for (int i = nums.size()-1; i >= 0; i--) res[--cnt[nums[i]]] = nums[i];
    swap(nums, res);
}
```

## [Radix Sort](https://oi-wiki.org/basic/radix-sort/)

[164. Maximum Gap](https://leetcode.com/problems/maximum-gap/)

LSD（Least Significant Digit first）Radix Sort:

```c++
// Stable
// Time complexity: O(d⋅(n+k))≈O(n), k radix or base of the digits, d <= 10.
// Space complexity: O(n+k)≈O(n)
void RadixSort(vector<int>& nums) 
{
	vector<int> backup(nums.size(), 0);
	int max_val = *std::max_element(nums.begin(), nums.end());
	int exp = 1; // 1, 10, 100, 1000....
	int radix = 10; // base 10 system;
	while (max_val / exp > 0) {
		vector<int> cnt(radix, 0);
		for (int i = 0; i < nums.size(); i++) {
			cnt[(nums[i]/exp)%10]++;
		}
		for (int i = 1; i < cnt.size(); i++) {
			cnt[i] += cnt[i-1];
		}
		for (int i = nums.size() - 1; i >= 0; i--) {
			backup[--cnt[(nums[i]/exp)%10]] = nums[i];
		}
		nums = backup;
		exp *= 10;
	}
}
```

## Head Sort

Treat the Array as a Complete Binary Tree

Unstable.

Time complexity: O(nlogn)

Space complexiy: O(1)

### Max Heap:

```c++
// To heapify a subtree rooted with node i
// which is an index in arr[].
void heapify(vector<int>& arr, int start, int end){
    int parent = start;

    // left index = 2*start + 1
    int child = 2 * start + 1;


	while (child <= end) {
		// First compare the sizes of the two child nodes and select the largest one
		if (child+1 <= end && arr[child+1] > arr[child]) child++;
		// If the parent node is larger than the child node, 
		// it means the adjustment is complete and the function is exited directly.
		if (arr[parent] > arr[child]) return;
		swap(arr[parent], arr[child]);
    // heapify the affected sub-tree
		parent = child;
		child = parent*2+1;
	}
}

// Main function to do heap sort
void heapSort(vector<int>& arr){
    int n = arr.size();

    // Build heap (rearrange vector)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, i, n-1);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {

        // Move current root to end
        swap(arr[0], arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, 0, i-1);
    }
}
```

