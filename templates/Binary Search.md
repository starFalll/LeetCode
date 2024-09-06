# Binary Search

最大化最小值/最小化最大值，一般用二分解决。

即二分查找满足条件的最小/最大值，这类题，二分的值是用遍历求得，而不是取某个元素的值。

例题：
[719. Find K-th Smallest Pair Distance](https://leetcode.com/problems/find-k-th-smallest-pair-distance/)
[2616. Minimize the Maximum Difference of Pairs](https://leetcode.com/problems/minimize-the-maximum-difference-of-pairs/)

[2812. Find the Safest Path in a Grid](https://leetcode.com/problems/find-the-safest-path-in-a-grid/)

**对于unordered array，要使用二分查找, 可以采用mid和mid+1/mid-1比大小来判断方向。** for example: [162. Find Peak Element](https://leetcode.com/problems/find-peak-element/)

循环退出条件：

只要有一个为等于mid，则用low<high，否则用low<=high

```
1. while (low <= high)
high = mid-1;
low = mid+1;

2. while(low < high)
high = mid/ low = mid
```

