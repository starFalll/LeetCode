# Leetcode 题解

## 数组

### 26.Remove Duplicates from Sorted Array

Given a sorted array *nums*, remove the duplicates [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm) such that each element appear only *once* and return the new length.

Do not allocate extra space for another array, you must do this by **modifying the input array in-place** with O(1) extra memory.

#### 代码1

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        auto it1 = nums.begin()+1;
        auto it2 = nums.begin();
        for(;it1<nums.end();it1++){
            if(*it1!=*it2){
                it2=it1;
            }
            else{
                nums.erase(it1);
                it1=it2;
            }
        }
        
        return nums.size();
        
    }
};
```

#### 代码2

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty())
            return 0;
        int index = 0;
        for(int i=1;i<nums.size();i++){
            if(nums[i] != nums[index])
                nums[++index]=nums[i];
        }
        return index+1;
        
    }
};
```

#### 代码3

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        return distance(nums.begin(),unique(nums.begin(),nums.end()));
    }
};
```

### 80.Remove Duplicates from Sorted Array II

Given a sorted array *nums*, remove the duplicates [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm) such that duplicates appeared at most *twice* and return the new length.

Do not allocate extra space for another array, you must do this by **modifying the input array in-place** with O(1) extra memory.

#### 代码1

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty())
            return 0;
        int index=0;
        bool flag=false;//判断是否重复两次
        for(int i=1;i<nums.size();i++){
            if(index!=i&&nums[index]==nums[i]&&!flag){//重复但没到两次
                nums[++index]=nums[i];
                flag=true;
            }
            else if(index!=i&&nums[index]!=nums[i]){//新的不重复数
                nums[++index]=nums[i];
                flag=false;
            }
        }
        
        return index+1;
        
    }
};
```

#### 代码2 

比上面的代码更简洁，并且拓展性更好，即将下面的2变为n，则可以重复n次

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) return nums.size();

        int index = 2;
        for (int i = 2; i < nums.size(); i++){
            if (nums[i] != nums[index - 2])//和index的前面第二个不重复，说明不存在三个重复的
                nums[index++] = nums[i];
        }

        return index;
    }
};
```



### 33.Search in Rotated Sorted Array

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., `[0,1,2,4,5,6,7]` might become `[4,5,6,7,0,1,2]`).

You are given a target value to search. If found in the array return its index, otherwise return `-1`.

You may assume no duplicate exists in the array.

Your algorithm's runtime complexity must be in the order of *O*(log *n*).

#### 代码1

```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.size()==0)
            return -1;
        if(nums.size()==1){
            if(nums[0]==target)
                return 0;
            return -1;
        }
        int low=0,high=nums.size()-1;
        while(low<=high){
            int mid = low + (high -low)/2;
            if(target==nums[mid]){
                return mid;
            }

            else if(nums[mid]>=nums[low]){/*中间的数为大数，例4,5,6,7,0,1,2，这里要有等号，因为是向下取整*/
                if(target<nums[mid]&&target>=nums[low])/*这种情况下low~mid为递增数列，又因为是大数，所以看左边这截*/
                    high=mid-1;
                else{
                    low=mid+1;
                }
            }
            else{//中间的数为小数，例5,6,7,0,1,2,4
                if(target>nums[mid]&&target<=nums[high])/*这种情况下mid~high为递增数列，又因为小数，所以看右边这截*/
                    low=mid+1;
                else{
                    high=mid-1;
                }
            }
            
        }
        return -1;
    }
};
```



### 81.Search in Rotated Sorted Array II

Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.

(i.e., `[0,0,1,2,2,5,6]` might become `[2,5,6,0,0,1,2]`).

You are given a target value to search. If found in the array return `true`, otherwise return `false`.

**Follow up:**

- This is a follow up problem to [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/description/), where `nums` may contain duplicates.
- Would this affect the run-time complexity? How and why?

#### 代码

```c++
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        if(nums.empty())
            return false;
        int low=0,high=nums.size()-1;
        while(low<=high){
            int mid = low+(high-low)/2;
            if(nums[mid]==target)
                return true;
            else if(nums[mid]>nums[low]){
                if(target<nums[mid]&&target>=nums[low]){
                    high=mid-1;
                }
                else{
                    low=mid+1;
                }
            }
            else if(nums[mid]<nums[low]){
                if(target>nums[mid]&&target<=nums[high])
                    low=mid+1;
                else{
                    high=mid-1;
                }
            }
            else{//nums[mid]==nums[low]
                low++; /*这里要low++而不是high=mid-1是因为取整是向下的，可能会溢出，例1,3,1,1,1目标是3，mid为2，low为0,如果是采用high=mid-1，则high=1，新的mid=0，low=0，这时候又会跳到这个else条件中，high=mid-1=-1溢出了，而采用low++则结果正确*/
            }
        }
        return false;
    }
};
```

### 4.Median of Two Sorted Arrays

There are two sorted arrays **nums1** and **nums2** of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

#### 解析

这是一道非常经典的题。这题更通用的形式是，给定两个已经排序好的数组，找到两者所有元素中第`k`大的元素。

`O(m+n)`的解法比较直观，直接merge两个数组，然后求第`k`大的元素。

不过我们仅仅需要第`k`大的元素，是不需要“排序”这么昂贵的操作的。可以用一个计数器，记录当前已经找到第`m`大的元素了。同时我们使用两个指针`pA`和`pB`，分别指向A和B数组的第一个元素，使用类似于merge sort的原理，如果数组A当前元素小，那么`pA++`，同时`m++`；如果数组B当前元素小，那么`pB++`，同时`m++`。最终当`m`等于`k`的时候，就得到了我们的答案，`O(k)`时间，`O(1)`空间。但是，当`k`很接近`m+n`的时候，这个方法还是`O(m+n)`的。

有没有更好的方案呢？我们可以考虑从`k`入手。如果我们每次都能够删除一个一定在第`k`大元素之前的元素，那么我们需要进行`k`次。但是如果每次我们都删除一半呢？由于A和B都是有序的，我们应该充分利用这里面的信息，类似于二分查找，也是充分利用了“有序”。

假设A和B的元素个数都大于`k/2`，我们将A的第`k/2`个元素（即`A[k/2-1]`）和B的第`k/2`个元素（即`B[k/2-1]`）进行比较，有以下三种情况（为了简化这里先假设`k`为偶数，所得到的结论对于`k`是奇数也是成立的）：

- `A[k/2-1] == B[k/2-1]`
- `A[k/2-1] > B[k/2-1]`
- `A[k/2-1] < B[k/2-1]`

如果`A[k/2-1] < B[k/2-1]`，意味着`A[0]`到`A[k/2-1]`的肯定在A∪B的top k元素的范围内，换句话说，`A[k/2-1]`不可能大于A∪B的第`k`大元素。留给读者证明。

因此，我们可以放心的删除A数组的这`k/2`个元素。同理，当`A[k/2-1] > B[k/2-1]`时，可以删除B数组的`k/2`个元素。

当`A[k/2-1] == B[k/2-1]`时，说明找到了第`k`大的元素，直接返回`A[k/2-1]`或`B[k/2-1]`即可。

因此，我们可以写一个递归函数。那么函数什么时候应该终止呢？

- 当A或B是空时，直接返回`B[k-1]`或`A[k-1]`；
- 当`k=1`时，返回`min(A[0], B[0])`；
- 当`A[k/2-1] == B[k/2-1]`时，返回`A[k/2-1]`或`B[k/2-1]`

#### 代码

```c++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m=nums1.size();
        int n=nums2.size();
        int total=n+m;
        if(total&0x01)
            return findMedian(nums1.begin(),m,nums2.begin(),n,total/2+1);
        else
            return (findMedian(nums1.begin(),m,nums2.begin(),n,total/2)+findMedian(nums1.begin(),m,nums2.begin(),n,total/2+1))/2.0;
    }
    
    static int findMedian(vector<int>::const_iterator A,int m,vector<int>::const_iterator B,int n,int k)//k是长度，k-1是下标
    {
    	//保证m<=n，目的是第二个if
        if(m>n) return findMedian(B,n,A,m,k);
        if(m==0) return *(B+k-1);
        if(k==1) return min(*A,*B);
        int cuta=min(k/2,m),cutb=k-cuta;
        if(*(A+cuta-1) < *(B+cutb-1)){
            return findMedian(A+cuta,m-cuta,B,n,k-cuta);
        }
        else if(*(A+cuta-1) > *(B+cutb-1))
            return findMedian(A,m,B+cutb,n-cutb,k-cutb);
        else{
            return *(A+cuta-1);
        }
    }
};
```

### 128.Longest Consecutive Sequence

Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

Your algorithm should run in O(*n*) complexity.

**Example:**

```python
Input: [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.
```

#### 解析

如果允许O(nlogn)的复杂度，那么可以先排序，可是本题要求`O(n)`。

由于序列里的元素是无序的，又要求`O(n)`，首先要想到用哈希表。

用一个哈希表存储所有出现过的元素，对每个元素，以该元素为中心，往左右扩张，直到不连续为止，记录下最长的长度。

#### 代码1

```c++
//时间复杂度为O(n)
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int,bool> used;
        for(auto i:nums) used[i]=false;
        
        int lengest=0;
      
        for(auto i:nums){
            if(used[i]) continue;
            int length=1;
            used[i]=true;
          /*unordered_map的find是如果找到指定的键值，则为元素的迭代器;如果在容器中未找到指定的键，则为unordered_map::end，所以用used.find(j)!=used.end()判断key是否在map内*/
            for(int j=i+1;used.find(j)!=used.end();j++){
                length++;
                used[j]=true;
            }
            for(int j=i-1;used.find(j)!=used.end();j--){
                length++;
                used[j]=true;
            }
            lengest=max(lengest,length);
        }
        return lengest;
        
    }
};
```

### 1.Two Sum

Given an array of integers, return **indices** of the two numbers such that they add up to a specific target.

You may assume that each input would have **exactly** one solution, and you may not use the *same* element twice.

#### 解析

方法1：暴力，时间复杂度O(n^2)

方法2：hash表存储每个数对应的下标，时间复杂度O(n)

#### 代码

方法1：很早之前用python写的暴力方法，看看就好

```python
class Solution:
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        
        lens = len(nums)
        i = 0
        a = 0
        b = 0
        while (i < lens):
            tmp = nums[i]
            h = tmp
            first = i + 1
            while (first < lens):
                h += nums[first]
                if (h == target):
                    a = i
                    b = first
                    result = []
                    result.append(a)
                    result.append(b)
                    return result
                first += 1
                h=tmp
            i += 1
```



方法2：hash

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> used;
        vector<int> res;
        for(int i=0;i<nums.size();i++){
            used[nums[i]]=i;
        }
        for(int i=0;i<nums.size();i++){
            int aim=target-nums[i];
            if(used.find(aim)!=used.end()&&used[aim]!=i){
                    res.push_back(i);
                    res.push_back(used[aim]);
                    return res;
                }
            }
        return res;
    }
};
```

### 15.3Sum

Given an array `nums` of *n* integers, are there elements *a*, *b*, *c* in `nums` such that *a* + *b* + *c* = 0? Find all unique triplets in the array which gives the sum of zero.

**Note:**

The solution set must not contain duplicate triplets.

**Example:**

```python
Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
```

#### 解析

先排序，然后a从0循环到n，对于每一次循环 b=a+1,c指向最后一个数，然后b和c不断逼近，即和小于目标值，则b++，和大于目标值，则c--，注意每次找到满足条件的值以后，要避免后面的重复值。

#### 代码

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        if(nums.size()<3)
            return res;
        sort(nums.begin(),nums.end());
        auto last = nums.end();
        const int target=0;
        for(auto i=nums.begin();i<last-2;i++){//i小于last-2是因为最后i指向倒数第三个数
            if(i>nums.begin()&&*i==*(i-1))
                continue;
            auto j=i+1;
            auto k=last-1;
            while(j<k){
                if(*i+*j+*k>target){
                    k--;
                    
                }
                else if(*i+*j+*k<target){
                    j++;
                    
                }
                else{
                    res.push_back({*i,*j,*k});
                    j++;
                    k--;
                    while(*j==*(j-1)&&*k==*(k+1)&&j<k)j++;/*避免后面的重复值，如不加这一句，会有重复值，例[-2,0,0,2,2]，不加这一句结果会是[[-2,0,2],[-2,0,2]]，重复了会报错*/
                    
                    
                }
            }
            
        }
        return res;
    }
};
```

### 16.3Sum Closest

Given an array `nums` of *n* integers and an integer `target`, find three integers in `nums` such that the sum is closest to `target`. Return the sum of the three integers. You may assume that each input would have exactly one solution.

**Example:**

```python
Given array nums = [-1, 2, 1, -4], and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).

```

#### 解析

和上一题差不多思路，只是要考虑最接近的值。

#### 代码

```c++
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int res;
        if(nums.size()<3)
            return res;
        sort(nums.begin(),nums.end());
        auto last=nums.end();
        int min=INT_MAX;
        for(auto i=nums.begin();i<last-2;i++){
            auto j=i+1;
            auto k=last-1;
            while(j<k){
                int tmp=abs(*i+*j+*k-target);
                if(tmp<min){
                    res=*i+*j+*k;
                    min=tmp;
                }
                if(abs(*i+*(j+1)+*k-target)<abs(*i+*j+*(k-1)-target)){
                    j++;
                }
                else{
                    k--;
                }
            }
        }
        return res; 
    }
};
```

### 18.4Sum*

Given an array `nums` of *n* integers and an integer `target`, are there elements *a*, *b*, *c*, and *d* in `nums` such that *a* + *b* + *c* + *d* = `target`? Find all unique quadruplets in the array which gives the sum of `target`.

**Note:**

The solution set must not contain duplicate quadruplets.

#### 分析

如果采用上面几道题的方法时间复杂度为O(n^3)，换成先使用hash缓存任意两个值的和以及它们的下标，然后再找另外两个值，这样可以把时间复杂度降低到O(n^2)

#### 代码1

````c++
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        if(nums.size()<4)
            return res;
        sort(nums.begin(),nums.end());
        unordered_multimap<int,pair<int ,int>> cache;/*pair类似于python中的元组，将2个不同类型的数据打包成一个数据类型*/
        for(int i=0;i<nums.size()-1;i++){
            for(int j=i+1;j<nums.size();j++){
              //map的insert要求pair类型，make_pair自动判断内部数据类型，pair需要手动指定
                cache.insert(make_pair(nums[i]+nums[j],make_pair(i,j)));
            }
            
        }
        for(auto i=cache.begin();i!=cache.end();i++){
            int x= target-i->first;
            auto aim=cache.equal_range(x);//将两个数值为x的pair挑出来
            for(auto j=aim.first;j!=aim.second;j++){//first指向第一个元组，second类似于end
                int a=i->second.first;
                int b=i->second.second;
                int c=j->second.first;
                int d=j->second.second;
                if(a!=c&&a!=d&&b!=c&&b!=d){//下标不能相同，不然会重复
                    vector<int> tmp={nums[a],nums[b],nums[c],nums[d]};
                    sort(tmp.begin(),tmp.end());
                    res.push_back(tmp);
                }
            }
        }
        sort(res.begin(),res.end());
        res.erase(unique(res.begin(),res.end()),res.end());/*去除重复的结果，erase+unique是常用方法*/
        return res;
        
    }
};
````

#### 代码2

和前面几题使用左右靠近的方法差不多，看起来时间复杂度高，但是由于很多情况都是判断不满足就跳过，减少了循环时间，速度比上面的代码1要快很多。

```c++
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        if(nums.size()<4)
            return res;
        sort(nums.begin(),nums.end());
        int len=nums.size();
        for(int i=0;i<len-3;i++){
            if(i>0&&nums[i]==nums[i-1])continue;
            if(nums[i]+nums[i+1]+nums[i+2]+nums[i+3]>target)break;
            if(nums[i]+nums[len-3]+nums[len-2]+nums[len-1]<target)continue;
            for(int j=i+1;j<len-2;j++){
                if(j>i+1&&nums[j]==nums[j-1])continue;
                if(nums[i]+nums[j]+nums[i+2]+nums[i+3]>target)break;
                if(nums[i]+nums[j]+nums[len-2]+nums[len-1]<target)continue;
                int first=j+1,last=len-1;
                while(first<last){
                    if(nums[i]+nums[j]+nums[first]+nums[last]<target){
                        first++;
                    }
                    else if(nums[i]+nums[j]+nums[first]+nums[last]>target){
                        last--;
                    }
                    else{
                        res.push_back({nums[i],nums[j],nums[first],nums[last]});
                        do{first++;}while(nums[first]==nums[first-1]&&first<last);
                        do{last--;}while(nums[last]==nums[last+1]&&first<last);
                    }
                }
            }
        }
        return res;
    }
};
```



### 454.4Sum II

Given four lists A, B, C, D of integer values, compute how many tuples `(i, j, k, l)` there are such that `A[i] + B[j] + C[k] + D[l]` is zero.

To make problem a bit easier, all A, B, C, D have same length of N where 0 ≤ N ≤ 500. All integers are in the range of -228 to 228 - 1 and the result is guaranteed to be at most 231 - 1.

**Example:**

```python
Input:
A = [ 1, 2]
B = [-2,-1]
C = [-1, 2]
D = [ 0, 2]

Output:
2

Explanation:
The two tuples are:
1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0
```

#### 解析

和4Sum中代码一的方法差不多，先用hash缓存A，B中任意两个数的和，但是因为本题只需要得出满足条件的个数而不需要输出具体的下标，所以比上一题的代码一要简洁很多。

#### 代码1（C++）

````c++
class Solution {
public:
    int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
        int res=0;
        unordered_map<int,int> cache;
        unordered_map<int,int> flag;
        for(auto a:A)
            for(auto b:B){
                if(flag.find(a+b)==flag.end()){
                    cache[a+b]=1;
                    flag[a+b]=1;
                }
                else
                    cache[a+b]++;
            }
        for(auto c:C)
            for(auto d:D){
                auto x=cache.find(0-c-d);
                if(x!=cache.end()){
                    res+=x->second;
                }
            }
        return res;
    }
};
````

#### 代码2（Python）

```python
class Solution:
    def fourSumCount(self, A, B, C, D):
        """
        :type A: List[int]
        :type B: List[int]
        :type C: List[int]
        :type D: List[int]
        :rtype: int
        """
        res=0
        cache={}
        flag={}
        for a in A:
            for b in B:
                if a+b not in flag:
                    flag[a+b]=1
                    cache[a+b]=1
                else:
                    cache[a+b]+=1
        
        
        for c in C:
            for d in D:
                tmp=0-c-d
                if tmp in cache:
                    res+=cache[tmp]
        return res
            
```



### 27.Remove Element

Given an array *nums* and a value *val*, remove all instances of that value [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm) and return the new length.

Do not allocate extra space for another array, you must do this by **modifying the input array in-place** with O(1) extra memory.

The order of elements can be changed. It doesn't matter what you leave beyond the new length.

**Example 1:**

```python
Given nums = [3,2,2,3], val = 3,

Your function should return length = 2, with the first two elements of nums being 2.

It doesn't matter what you leave beyond the returned length.
```

**Example 2:**

```python
Given nums = [0,1,2,2,3,0,4,2], val = 2,

Your function should return length = 5, with the first five elements of nums containing 0, 1, 3, 0, and 4.

Note that the order of those five elements can be arbitrary.

It doesn't matter what values are set beyond the returned length.
```

#### 代码

````c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int index=0;
        for(int i=0;i<nums.size();i++){
            if(nums[i]!=val){
                nums[index++]=nums[i];
            }
        }
        return index;
    }
};
````

### 28.Next Permutation

Implement **next permutation**, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

The replacement must be **in-place** and use only constant extra memory.

Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.

`1,2,3` → `1,3,2`
`3,2,1` → `1,2,3`
`1,1,5` → `1,5,1`

#### 解析

遇到这类概念比较抽象的题目，写几个例子通常会帮助理解问题的规律：

7 2 5 2 3 1

7 2 5 3 1 2

7 2 5 3 2 1

7 3 1 2 2 5

由此可知：

**1. 从低位向高位（从右向左）找第一个递减的数：s[i]>s[i-1]。如果不存在，则表明该permutation已经最大，next permutation为当前序列的逆序。**

**2. 在s[i:n-1]中找一个j，使s[j]为大于s[i]的最大数，swap(s[i], s[j])**

**3. 将s[i:n-1]反转。**

#### 代码

```cpp
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        for(int i=nums.size()-1;i>0;i--){
            if(nums[i]>nums[i-1]){
                int j=i;
                while(j<nums.size()&&nums[j]>nums[i-1])
                    j++;
                swap(nums[i-1],nums[--j]);
                reverse(nums.begin()+i,nums.end());
                return;
            }
        }
        reverse(nums.begin(),nums.end());
        return;
    }
    
    void swap(int & a,int &b){
        int tmp=a;
        a=b;
        b=tmp;
    }
};
```

### 60.Permutation Sequence

The set `[1,2,3,...,*n*]` contains a total of *n*! unique permutations.

By listing and labeling all of the permutations in order, we get the following sequence for *n* = 3:

1. `"123"`
2. `"132"`
3. `"213"`
4. `"231"`
5. `"312"`
6. `"321"`

Given *n* and *k*, return the *k*th permutation sequence.

**Note:**

- Given *n* will be between 1 and 9 inclusive.
- Given *k* will be between 1 and *n*! inclusive.

**Example 1:**

```python
Input: n = 3, k = 3
Output: "213"
```

**Example 2:**

```python
Input: n = 4, k = 9
Output: "2314"
```

#### 解析

同样先通过举例来获得更好的理解。以n = 4，k = 9为例：

1234

1243

1324

1342

1423

1432

2134

2143

2314  <= k = 9

2341

2413

2431

3124

3142

3214

3241

3412

3421

4123

4132

4213

4231

4312

4321

最高位可以取{1, 2, 3, 4}，而每个数重复3! = 6次。所以第k=9个permutation的s[0]为{1, 2, 3, 4}中的第9/6+1 = 2个数字s[0] = 2。

而对于以2开头的6个数字而言，k = 9是其中的第k' = 9%(3!) = 3个。而剩下的数字{1, 3, 4}的重复周期为2! = 2次。所以s[1]为{1, 3, 4}中的第k'/(2!)+1 = 2个，即s[1] = 3。

对于以23开头的2个数字而言，k = 9是其中的第k'' = k'%(2!) = 1个。剩下的数字{1, 4}的重复周期为1! = 1次。所以s[2] = 1.

对于以231开头的一个数字而言，k = 9是其中的第k''' = k''/(1!)+1 = 1个。s[3] = 4



这里有另外一种余数为0的情况：n=3，k=4

123

132

213

231

312

321

k= 4/2! 才行，而不是取余数，因为这个时候4%2==0，余数为0

#### 代码

````cpp
class Solution {
public:
    string getPermutation(int n, int k) {
        string res;
        vector<int> minusn(n,1);
        vector<char> ch(n,'0'); 
        for(int i=1;i<n;i++){
            minusn[i]*=minusn[i-1]*i;
        }
        for(int i=0;i<n;i++){
            ch[i]=ch[i]+(i+1);
        }
        for(int i=0;i<n;i++){
            int index=0;
            if(k%minusn[n-i-1]==0){
                index=k/minusn[n-i-1];
                k/=index;
            }
                
            else{
                index=k/minusn[n-i-1]+1;
                k%=minusn[n-i-1];
            }       
            res.push_back(ch[(index-1)]);
            ch.erase(ch.begin()+index-1);
            
        }
        return res;
    }
};
````

###36.Valid Sudoku

Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated **according to the following rules**:

1. Each row must contain the digits `1-9` without repetition.
2. Each column must contain the digits `1-9` without repetition.
3. Each of the 9 `3x3` sub-boxes of the grid must contain the digits `1-9` without repetition.

![img](https://upload.wikimedia.org/wikipedia/commons/thumb/f/ff/Sudoku-by-L2G-20050714.svg/250px-Sudoku-by-L2G-20050714.svg.png)
A partially filled sudoku which is valid.

The Sudoku board could be partially filled, where empty cells are filled with the character `'.'`.

**Example 1:**

```
Input:
[
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: true

```

**Example 2:**

```
Input:
[
  ["8","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
Output: false
Explanation: Same as Example 1, except with the 5 in the top left corner being 
    modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.

```

**Note:**

- A Sudoku board (partially filled) could be valid but is not necessarily solvable.
- Only the filled cells need to be validated according to the mentioned rules.
- The given board contain only digits `1-9` and the character `'.'`.
- The given board size is always `9x9`.

#### 代码

```cpp
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<int> uniq(9,0);
        for(int i=0;i<9;i++){//check row
            for(int j=0;j<9;j++){
                if(board[i][j]>='1'&&board[i][j]<='9'){
                    uniq[board[i][j]-'1']++;
                    if(uniq[board[i][j]-'1']>1)
                        return false;
                }
            }
            returnzero(uniq);
        }
        for(int i=0;i<9;i++){//check column
            for(int j=0;j<9;j++){
                if(board[j][i]>='1'&&board[j][i]<='9'){
                    uniq[board[j][i]-'1']++;
                    if(uniq[board[j][i]-'1']>1)
                        return false;
                }
            }
            returnzero(uniq);
        }
        
        for(int m=0;m<9;m+=3){//check 3*3 box
            for(int k=0;k<9;k+=3){
                for(int i=m;i<m+3;i++){
                    for(int j=k;j<k+3;j++){
                        if(board[i][j]>='1'&&board[i][j]<='9'){
                            uniq[board[i][j]-'1']++;
                            if(uniq[board[i][j]-'1']>1)
                                return false;
                        }
                    }
                    
                }
                returnzero(uniq);
            }
        }
        return true;
        
    }
    void returnzero(vector<int>& a)
    {
        for(int i=0;i<a.size();i++)
            a[i]=0;
    }
};
```

### 48.Rotate Image

You are given an *n* x *n* 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

**Note:**

You have to rotate the image [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm), which means you have to modify the input 2D matrix directly. **DO NOT** allocate another 2D matrix and do the rotation.

**Example 1:**

```
Given input matrix = 
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],

rotate the input matrix in-place such that it becomes:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]

```

**Example 2:**

```
Given input matrix =
[
  [ 5, 1, 9,11],
  [ 2, 4, 8,10],
  [13, 3, 6, 7],
  [15,14,12,16]
], 

rotate the input matrix in-place such that it becomes:
[
  [15,13, 2, 5],
  [14, 3, 4, 1],
  [12, 6, 8, 9],
  [16, 7,10,11]
]
```

#### 代码

```cpp
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        for(int i=0;i<matrix.size()-1;i++){//diagonal exchange
            for(int j=0;j+i<matrix.size()-1;j++){
                swap(matrix[i][j],matrix[matrix.size()-1-j][matrix.size()-1-i]);
            }
        }
        
        for(int i=0;i<matrix.size();i++){//horizontal exchange
            for(int j=0;j<matrix.size()/2;j++){
                swap(matrix[j][i],matrix[matrix.size()-1-j][i]);
            }
        }
        
    }
};
```

### 42.Trapping Rain Water

Given *n* non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

![img](http://www.leetcode.com/static/images/problemset/rainwatertrap.png)
The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped. **Thanks Marcos** for contributing this image!

**Example:**

```
Input: [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
```

#### 解析

对于每个柱子（高为height），找到其左右最高的柱子（left_max,right_max），上面的积水为：max(left_max,right_max)-height.

具体方法：

找到最高的柱子，然后从左到最高和从右到最高依次遍历。

#### 代码

```cpp
class Solution {
public:
    int trap(vector<int>& height) {
        int max=0;
        for(int i=0;i<height.size();i++){
            if(height[i]>height[max])
                max=i;
        }
        int res=0;
        for(int i=0,left=0;i<max;i++){
            if(height[i]>height[left]){
                left=i;
            }
            else{
                res+=height[left]-height[i];
            }
        }
        for(int i=height.size()-1,right=height.size()-1;i>max;i--){
            if(height[i]>height[right]){
                right=i;
            }
            else{
                res+=height[right]-height[i];
            }
        }
        return res;
        
    }
};
```

### 66.Plus One

Given a **non-empty** array of digits representing a non-negative integer, plus one to the integer.

The digits are stored such that the most significant digit is at the head of the list, and each element in the array contain a single digit.

You may assume the integer does not contain any leading zero, except the number 0 itself.

**Example 1:**

```
Input: [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.

```

**Example 2:**

```
Input: [4,3,2,1]
Output: [4,3,2,2]
Explanation: The array represents the integer 4321.
```

#### 代码

```cpp
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        bool flag;
        for(int i=digits.size()-1;i>=0;i--){
            if(i==0){
                if(digits[i]+1>9){
                    digits[i]=(digits[i]+1)%10;
                    digits.insert(digits.begin(),1);
                    break;
                }
                else{
                    digits[i]=digits[i]+1;
                    break;
                }    
            }
            else{
                flag=false;
                if(digits[i]+1>9){
                    flag=true;
                }
                digits[i]=(digits[i]+1)%10;
                if(flag==false)
                    break;
            }
               
        }
        return digits;
    }
};
```

### 70.Climbing Stairs

You are climbing a stair case. It takes *n* steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

**Note:** Given *n* will be a positive integer.

**Example 1:**

```
Input: 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps

```

**Example 2:**

```
Input: 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step
```

#### 解析

[斐波那契数列](https://zh.wikipedia.org/zh/%E6%96%90%E6%B3%A2%E9%82%A3%E5%A5%91%E6%95%B0%E5%88%97) 的一种变体，和[青蛙跳台阶（剑指offer原题）](https://www.nowcoder.com/practice/8c82a5b80378478f9484d87d1c5f12a4?tpId=13&tqId=11161&tPage=1&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking)是一模一样的题。

#### 代码

```cpp
class Solution {
public:
    int climbStairs(int n) {
        if(n<0)
            return -1;
        if(n==0)
            return 0;
        if(n==1)
            return 1;
        int a=1;
        int b=1;
        for(int i=2;i<=n;i++){
            b=a+b;
            a=b-a;
        }
        return b;
    }
};
```



### 89.Gray Code

The gray code is a binary numeral system where two successive values differ in only one bit.

Given a non-negative integer *n* representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.

**Example 1:**

```
Input: 2
Output: [0,1,3,2]
Explanation:
00 - 0
01 - 1
11 - 3
10 - 2

For a given n, a gray code sequence may not be uniquely defined.
For example, [0,2,3,1] is also a valid gray code sequence.

00 - 0
10 - 2
11 - 3
01 - 1

```

**Example 2:**

```
Input: 0
Output: [0]
Explanation: We define the gray code sequence to begin with 0.
             A gray code sequence of n has size = 2n, which for n = 0 the size is 20 = 1.
             Therefore, for n = 0 the gray code sequence is [0].
```

#### 解析

格雷码，维基百科解释[在此](https://zh.wikipedia.org/wiki/%E6%A0%BC%E9%9B%B7%E7%A0%81)。

本题题意为生成n比特的所有格雷码，将其转化为十进制并以列表形式返回。

下面来看看规律：

n=0：0

n=1：0 ，1

n=2：00，01，11，10

n=3：000，001，011，010，110，111，101，100

**推广：n = i的grey code的前一半包括了n = i-1的所有grey code，而后一半则为前一半逆序后加上上2^(i-1)。**

#### 代码

```cpp
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> res;
        if(n<0)
            return res;
        res.push_back(0);
        int k=1;
        for(int i=1;i<=n;i++){
            for(int j=res.size()-1;j>=0;j--)//后一半则为前一半逆序后加上2^(i-1)
                res.push_back(res[j]+k);
            k<<=1;//2^(i-1)
        }
        return res;
        
    }
};
```

### 73.Set Matrix Zeroes

Given a *m* x *n* matrix, if an element is 0, set its entire row and column to 0. Do it [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm).

**Example 1:**

```
Input: 
[
  [1,1,1],
  [1,0,1],
  [1,1,1]
]
Output: 
[
  [1,0,1],
  [0,0,0],
  [1,0,1]
]

```

**Example 2:**

```
Input: 
[
  [0,1,2,0],
  [3,4,5,2],
  [1,3,1,5]
]
Output: 
[
  [0,0,0,0],
  [0,4,5,0],
  [0,3,1,0]
]

```

**Follow up:**

- A straight forward solution using O(*m**n*) space is probably a bad idea.
- A simple improvement uses O(*m* + *n*) space, but still not the best solution.
- Could you devise a constant space solution?

#### 解析

O(1)可以用第一行和第一列来存储，中间有任何一个数为0，则将其对应的第一行和第一列的数设为0即可，此外，在此之前需要分别遍历一次第一行和第一列，用两个布尔常量判断是否需要将第一行和第一列设为0.

#### 代码

````cpp
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if(matrix.empty()|| matrix[0].empty())
            return;
        // find if the 1st row/col needs to be set as zero
        bool row_has_zero=false;
        bool col_has_zero=false;
        int m=matrix.size();
        int n=matrix[0].size();
        for(int i=0;i<m;i++){
            if(matrix[i][0]==0){
                col_has_zero=true;
                break;
            }
        }
        for(int i=0;i<n;i++){
            if(matrix[0][i]==0){
                row_has_zero=true;
                break;
            }
        }
         // use 1st row/col to record whether to set each col/row as zero
        for(int i=1;i<m;i++){
            for(int k=1;k<n;k++){
                if(matrix[i][k]==0){
                    matrix[i][0]=0;
                    matrix[0][k]=0;
                }
            }
        }
        //set as zero
        for(int i=1;i<n;i++){
            if(matrix[0][i]==0)
                for(int k=0;k<m;k++)
                    matrix[k][i]=0;
        }
        for(int i=1;i<m;i++){
            if(matrix[i][0]==0)
                for(int k=0;k<n;k++)
                    matrix[i][k]=0;
        }
        //set 1st row/col as zero
        if(row_has_zero)
            for(int k=0;k<n;k++)
                matrix[0][k]=0;
        if(col_has_zero)
            for(int k=0;k<m;k++)
                matrix[k][0]=0;
        return;
        
    }
};
````

### 134.Gas Station

There are *N* gas stations along a circular route, where the amount of gas at station *i* is `gas[i]`.

You have a car with an unlimited gas tank and it costs `cost[i]` of gas to travel from station *i* to its next station (*i*+1). You begin the journey with an empty tank at one of the gas stations.

Return the starting gas station's index if you can travel around the circuit once in the clockwise direction, otherwise return -1.

**Note:**

- If there exists a solution, it is guaranteed to be unique.
- Both input arrays are non-empty and have the same length.
- Each element in the input arrays is a non-negative integer.

**Example 1:**

```
Input: 
gas  = [1,2,3,4,5]
cost = [3,4,5,1,2]

Output: 3

Explanation:
Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 4. Your tank = 4 - 1 + 5 = 8
Travel to station 0. Your tank = 8 - 2 + 1 = 7
Travel to station 1. Your tank = 7 - 3 + 2 = 6
Travel to station 2. Your tank = 6 - 4 + 3 = 5
Travel to station 3. The cost is 5. Your gas is just enough to travel back to station 3.
Therefore, return 3 as the starting index.

```

**Example 2:**

```
Input: 
gas  = [2,3,4]
cost = [3,4,3]

Output: -1

Explanation:
You can't start at station 0 or 1, as there is not enough gas to travel to the next station.
Let's start at station 2 and fill up with 4 unit of gas. Your tank = 0 + 4 = 4
Travel to station 0. Your tank = 4 - 3 + 2 = 3
Travel to station 1. Your tank = 3 - 3 + 3 = 3
You cannot travel back to station 2, as it requires 4 unit of gas but you only have 3.
Therefore, you can't travel around the circuit once no matter where you start.
```

#### 解析

这题要想清楚不容易，尽管想清楚后代码写起来很简单。

I.  显然当gas[i]<cost[i]时，i不能作为起点。

II. 当对所有加油站求和：sum(gas[i] - cost[i]) <0时，无法环绕一圈。反之，则一定能环绕一圈。

问题是如果可以环绕一圈，如何找起点？

性质1. 对于任意一个加油站i，假如从i出发可以环绕一圈，则i一定可以到达任何一个加油站。显而易见。

性质2. 如果这样的i是唯一的，则必然不存在j!=i， 从j出发可以到达i。

反证法：如果存在这样的j，则必然存在j->i->i的路径，而这个路径会覆盖j->j一周的路径。那么j也将是一个符合条件的起点。与唯一解的限制条件矛盾。

性质3. 假如i是最后的解，则由1可知，从0 ~ i-1出发无法达到i。而从i出发可以到达i+1 ~ n-1。

结合以上三条性质，得出解决的思路：

0. 如果对所有加油站的sum(gas[i] - cost[i])<0，则无解。否则进入1。
1. 从0开始计算sum(gas[i] - cost[i])，当遇到i1使sum<0时，说明从0出发无法到达i1。根据性质1，0不是起始点。而由于从0出发已经到达了1 ~ i1-1。根据性质2，1 ~ i1-1一定不是正确的起始点。又因为gas[i]-cost[i]导致sum小于0，所以i1+1为新的起始点候选。
2. 将sum清0，并从i1出发，假如又遇到i2使sum(gas[i] - cost[i]) < 0 时，说明i1出发无法绕一圈，更具性质1，排除i1。又因为i1+1 ~ i2-1都能从i1出发到达,。根据性质2，它们也必然不是起始点。此时i2+1为起始点的候选。
3. 以此类推，直到遇到ik，使从ik出发可以到达ik+1 ~ n-1。

其中步骤0可以合并到1~3的扫描中，一个pass来得到解。

#### 代码

````cpp
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int start=0,total=0,curnum=0;
        for(int i=0;i<gas.size();i++){
            total+=gas[i]-cost[i];
            curnum+=gas[i]-cost[i];
            if(curnum<0){
                start=i+1;
                curnum=0;
            }
        }
        if(total<0) return -1;
        return start;
    }
};
````

### 135.Candy

There are *N* children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

- Each child must have at least one candy.
- Children with a higher rating get more candies than their neighbors.

What is the minimum candies you must give?

**Example 1:**

```
Input: [1,0,2]
Output: 5
Explanation: You can allocate to the first, second and third child with 2, 1, 2 candies respectively.

```

**Example 2:**

```
Input: [1,2,2]
Output: 4
Explanation: You can allocate to the first, second and third child with 1, 2, 1 candies respectively.
             The third child gets 1 candy because it satisfies the above two conditions.
```

#### 解析

多观察几个输入，我们发现单调递增的序列后一个的candy数是前一个加一；

单调递减的序列，最小的数为1，从最小的数 nums[i] 逆序遍历，前面的数 nums[i-1]=max(nums[i-1],nums[i]+1);

初始的糖果都为1.

#### 代码

```cpp
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n=ratings.size();
        if(n<2)
            return n;
        vector<int> nums(n,1);//init
        int res=0;
        for(int i=1;i<n;i++){
            if(ratings[i-1]<ratings[i])//ascending
                nums[i]=nums[i-1]+1;
        }
        for(int i=n-1;i>0;i--){
            if(ratings[i-1]>ratings[i])//descending
                nums[i-1]=max(nums[i-1],nums[i]+1);
        }
        for(int i=0;i<n;i++)
            res+=nums[i];
        return res;
    }
};
```

### 136.Single Number

Given a **non-empty** array of integers, every element appears *twice* except for one. Find that single one.

**Note:**

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

**Example 1:**

```
Input: [2,2,1]
Output: 1


```

**Example 2:**

```
Input: [4,1,2,1,2]
Output: 4

```

#### 解析

异或即可.

#### 代码

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        if(nums.size()<=0)
            return -1;
        int res=0;
        for(int i=0;i<nums.size();i++){
            res^=nums[i];
        }
        return res;
    }
};
```

### 137.Single Number II

Given a **non-empty** array of integers, every element appears *three* times except for one, which appears exactly once. Find that single one.

**Note:**

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

**Example 1:**

```
Input: [2,2,3,2]
Output: 3

```

**Example 2:**

```
Input: [0,1,0,1,0,1,99]
Output: 99
```

### 解析

由于x^x^x = x，无法直接利用I的方法来解。但可以应用类似的思路，即利用位运算来消除重复3次的数。以一个数组[14 14 14 9]为例，将每个数字以二进制表达：

1110

1110

1110

1001

__\_\_\_

4331    对每一位进行求和

1001    对每一位的和做%3运算，来消去所有重复3次的数

#### 代码

```cpp
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        if(nums.empty())
            return -1;
        int res=0;
        for(int i=31;i>=0;i--){
            int sum=0;
            int mask=1<<i;
            for(int i=0;i<nums.size();i++){
                if(nums[i]&mask)
                    sum++;
            }
            res=(res<<1)+(sum%3);
        }
        return res;
    }
};
```

## 单链表

###2.Add Two Numbers

You are given two **non-empty** linked lists representing two non-negative integers. The digits are stored in **reverse order** and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

**Example:**

```
Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
```

#### 代码

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* res=new ListNode(-1);
        ListNode* ret=res;
        ListNode* p1=l1;
        ListNode* p2=l2;
        int carry=0;
        while(p1!=nullptr||p2!=nullptr||carry){
            if(p1){
                carry+=p1->val;
                p1=p1->next;
            }
            if(p2){
                carry+=p2->val;
                p2=p2->next;
            }
            res->next=new ListNode(carry%10);
            carry/=10;
            res=res->next;
        }
        return ret->next;
    }
};
```

### 445.Add Two Numbers II

You are given two **non-empty** linked lists representing two non-negative integers. The most significant digit comes first and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

**Follow up:**
What if you cannot modify the input lists? In other words, reversing the lists is not allowed.

**Example:**

```
Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7
```

### 解析

逆序，不能反转，所以可以用栈来实现。

#### 代码

````cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* p1=l1;
        ListNode* p2=l2;
        stack<int> s1;
        stack<int> s2;
        stack<int> res;
        while(p1!=nullptr){
            s1.push(p1->val);
            p1=p1->next;
        }
            
        while(p2!=nullptr){
            s2.push(p2->val);
            p2=p2->next;
        }
        int carry=0;
        while(!s1.empty()||!s2.empty()||carry){
            if(!s1.empty()){
                carry+=s1.top();
                s1.pop();
            }
            if(!s2.empty()){
                carry+=s2.top();
                s2.pop();
            }
            res.push(carry%10);
            carry/=10;
        }
        ListNode* ret=new ListNode(-1);
        ListNode* tmp=ret;
        while(!res.empty()){
            tmp->next=new ListNode(res.top());
            tmp=tmp->next;
            res.pop();
        }
        return ret->next;
    }
};
````

### 206.Reverse Linked List

Reverse a singly linked list.

**Example:**

```
Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL

```

**Follow up:**

A linked list can be reversed either iteratively or recursively. Could you implement both?

#### 代码

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* f=nullptr;
        ListNode* s=head;
        ListNode* t=s;
        while(s&&t){
            t=t->next;
            s->next=f;
            f=s;
            s=t;
        }
        return f;
    }
};
```

### 92.Reverse Linked List II

Reverse a linked list from position *m* to *n*. Do it in one-pass.

**Note: **1 ≤ *m* ≤ *n* ≤ length of list.

**Example:**

```
Input: 1->2->3->4->5->NULL, m = 2, n = 4
Output: 1->4->3->2->5->NULL
```

#### 解析

反转整个链表的变种，指定了起点和终点。由于m=1时会变动头节点，所以加入一个add头节点，可以使用静态初始化，运行时间更短。

#### 代码

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if(m==n)
            return head;
        ListNode add{0};
        add.next=head;
        head=&add;
        ListNode* front=head;
        for(int i=0;i<m-1;i++)
            front=front->next;
        ListNode* last=front->next;
        ListNode* first=last->next;
        ListNode* l=first;
        for(int i=m;i<n;i++){
            l=l->next;
            first->next=last;
            last=first;
            first=l;
        }
        
        front->next->next=l;
        front->next=last;
        head=head->next;
        return head;
        
    }
};
```

### 86.Partition List

Given a linked list and a value *x*, partition it such that all nodes less than *x* come before nodes greater than or equal to *x*.

You should preserve the original relative order of the nodes in each of the two partitions.

**Example:**

```
Input: head = 1->4->3->2->5->2, x = 3
Output: 1->2->2->4->3->5
```

#### 解析

将小于x和大于等于x的分成两个链表（less，greater），然后再将 greater 的接在 less 的后面。

#### 代码

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        ListNode less{0};
        ListNode greater{0};
        ListNode* l=&less;
        ListNode* g=&greater;
        ListNode* p=head;
        while(p){
            if(p->val<x){
                l->next=p;
                l=l->next;
            }
            else{
                g->next=p;
                g=g->next;
            }
            p=p->next;
        }
        g->next=nullptr;
        l->next=greater.next;
        return less.next;
        
    }
};
```

### 83.Remove Duplicates from Sorted List

Given a sorted linked list, delete all duplicates such that each element appear only *once*.

**Example 1:**

```
Input: 1->1->2
Output: 1->2

```

**Example 2:**

```
Input: 1->1->2->3->3
Output: 1->2->3
```

#### 代码

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head||!(head->next))
            return head;
        ListNode* front=head;
        ListNode* p=head->next;
        while(p){
            if(p->val==front->val){
                front->next=p->next;
                p=front->next;
            }
            else{
                front=front->next;
                p=p->next;
            }
        }
        return head;
    }
};
```

### 82.Remove Duplicates from Sorted List II

Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only *distinct* numbers from the original list.

**Example 1:**

```
Input: 1->2->3->3->4->4->5
Output: 1->2->5

```

**Example 2:**

```
Input: 1->1->1->2->3
Output: 2->3
```

#### 解析

##### 迭代版

可以设置两个指针p1，p2，p1指向头结点head，p2指向head->next。

1.如果p1==p2，只有可能最前面出现重复，如上面第二个例子所示，这时找到第一个值不同的结点，按照nullptr和正常结点分别处理；

2.在上面的判断结束以后，如果p2->next为nullptr，直接返回头结点；

3.在上面两个判断都不成立时候，如果p2所指结点的值和它下一个结点的值一样，则p1不变，往后找，找到第一个不同值的结点，p1下一个结点指向该结点；

4.以上都不满足，则没有重复值。

##### 递归版

比较简单，见代码。

#### 代码

##### 迭代版

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head||!head->next)
            return head;
        ListNode* p1=head;
        ListNode* p2=head->next;
        while(p2){
            if(p1->val==p2->val){
                do{
                    p1=p1->next;
                    p2=p2->next;
                }while(p1&&p2&&p1->val==p2->val);
                if(p2){
                    p1=p2;
                    p2=p2->next;
                    head=p1;
                }
                else{
                    head=p2;
                }
            }
            else if(!p2->next){
                return head;
            }
            else if(p2->val==p2->next->val){
                do{
                    p2=p2->next;
                }while(p2->next&&p2->val==p2->next->val);
                p1->next=p2->next;
                p2=p2->next;
                
            }
            else{
                p1=p2;
                p2=p2->next;
            }
        }
        return head;
    }
};
```

##### 递归版

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head||!head->next)
            return head;
        ListNode* p=head->next;
        if(p->val!=head->val){
            head->next=deleteDuplicates(p);
            return head;
        }
        else{
            while(p&&p->val==head->val)p=p->next;
            return deleteDuplicates(p);
        }
    }
};
```

### 61.Rotate List

Given a linked list, rotate the list to the right by *k* places, where *k* is non-negative.

**Example 1:**

```
Input: 1->2->3->4->5->NULL, k = 2
Output: 4->5->1->2->3->NULL
Explanation:
rotate 1 steps to the right: 5->1->2->3->4->NULL
rotate 2 steps to the right: 4->5->1->2->3->NULL

```

**Example 2:**

```
Input: 0->1->2->NULL, k = 4
Output: 2->0->1->NULL
Explanation:
rotate 1 steps to the right: 2->0->1->NULL
rotate 2 steps to the right: 1->2->0->NULL
rotate 3 steps to the right: 0->1->2->NULL
rotate 4 steps to the right: 2->0->1->NULL
```

#### 解析

先遍历一遍，得到链表长度，然后如果k>len，k%=len，将尾结点下一个结点指向头结点，然后从尾结点向后跑 len-k 个结点再断开即可。

#### 代码

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(!head) return head;
        ListNode* p=head;
        int len=1;
        while(p->next){
            p=p->next;
            len++;
        }
        k%=len;
        p->next=head;
        for(int i=0;i<len-k;i++){
            p=p->next;
        }
        head=p->next;
        p->next=nullptr;
        return head;
    }
};
```

### 19.Remove Nth Node From End of List

Given a linked list, remove the *n*-th node from the end of list and return its head.

**Example:**

```
Given linked list: 1->2->3->4->5, and n = 2.

After removing the second node from the end, the linked list becomes 1->2->3->5.

```

**Note:**

Given *n* will always be valid.

**Follow up:**

Could you do this in one pass?

#### 解析

找到倒数第n个指针，一次遍历实现，可以设置两个指针p1，p2，p2先走n步，然后再一起走，p2指向最后一个结点时，p1->next为需要删除的结点，注意需要删除头结点的特殊情况，依然是新建一个结点放在最前面。

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy{0};
        dummy.next=head;
        ListNode* p1=&dummy;
        ListNode* p2=&dummy;
        
        for(int i=0;i<n;i++)
            p2=p2->next;
        while(p2->next){
            p1=p1->next;
            p2=p2->next;
        }
        ListNode* tmp=p1->next;
        p1->next=p1->next->next;
        delete tmp;
        return dummy.next;
    }
};
```

### 24.Swap Nodes in Pairs

Given a linked list, swap every two adjacent nodes and return its head.

**Example:**

```
Given 1->2->3->4, you should return the list as 2->1->4->3.
```

**Note:**

- Your algorithm should use only constant extra space.
- You may **not** modify the values in the list's nodes, only nodes itself may be changed.

####解析

链表可以有奇数个结点。

#### 代码

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head||!head->next)
            return head;
        ListNode* p=head;
        ListNode* tmp=nullptr;
        head=p->next;
        while(p&&p->next){
            tmp=p->next->next;
            p->next->next=p;
            p->next=tmp;
            if(p->next&&p->next->next){
                p->next=p->next->next;
            }
            p=tmp;
        }
        return head;
        
    }
};
```

### 25.Reverse Nodes in k-Group

Given a linked list, reverse the nodes of a linked list *k* at a time and return its modified list.

*k* is a positive integer and is less than or equal to the length of the linked list. If the number of nodes is not a multiple of *k* then left-out nodes in the end should remain as it is.


**Example:**

Given this linked list: `1->2->3->4->5`

For *k* = 2, you should return: `2->1->4->3->5`

For *k* = 3, you should return: `3->2->1->4->5`

**Note:**

- Only constant extra memory is allowed.
- You may not alter the values in the list's nodes, only nodes itself may be changed.

#### 解析

递归即可。

#### 代码

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(!head||!head->next||k<2) return head;
        ListNode* next_group=head;
        for(int i=0;i<k;i++){
            if(next_group)
                next_group=next_group->next;
            else
                return head;
        }
        ListNode* new_next_group=reverseKGroup(next_group,k);
        ListNode* prev=nullptr;
        ListNode* cur=head;
        ListNode* Next=head;
        while(cur!=next_group){
            Next=Next->next;
            cur->next=prev?prev:new_next_group;
            prev=cur;
            cur=Next;
        }
        return prev;
        
    }
};
```

### 138.Copy List with Random Pointer

A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.

Return a deep copy of the list.

#### 解析

和《剑指offer》[复杂链表的复制](https://github.com/starFalll/Sword-pointing-to-offer#25%E5%A4%8D%E6%9D%82%E9%93%BE%E8%A1%A8%E7%9A%84%E5%A4%8D%E5%88%B6) 是一样的题。

最简单的解法很显然需要额外的空间，这个额外的空间是由 `hash table` 的维护造成的。因为当我们访问一个结点时可能它的 random 指针指向的结点还没有访问过，结点还没有创建，所以需要用 `hash table` 的额外线性空间维护。

但我们可以通过链表原来结构中的 `next` 指针来替代 `hash table` 做哈希。假设有如下链表：

```
|------------|
|            v
1  --> 2 --> 3 --> 4

```

节点1的 random 指向了3。首先我们可以通过 next 遍历链表，依次拷贝主节点，并将其添加到原节点后面，如下：

```

1  --> 1' --> 2 --> 2' --> 3 --> 3' --> 4 --> 4'

```

调整新的节点的 random 指针，对于上面例子来说，我们需要将1'的 random 指向3'，其实也就是原先 random 指针的next节点。

```
|--------------------------|
|                          v
1  --> 1' --> 2 --> 2' --> 3 --> 3' --> 4 --> 4'
       |                         ^
       |-------------------------|

```

最后，拆分链表，就可以得到深度拷贝的链表了。

总结起来，实际我们对链表进行了三次扫描，第一次扫描对每个结点进行复制，然后把复制出来的新节点接在原结点的 next 指针上，也就是让链表变成一个重复链表，就是新旧更替；第二次扫描中我们把旧结点的随机指针赋给新节点的随机指针，因为新结点都跟在旧结点的下一个，所以赋值比较简单，就是 `node->next->random = node->random->next`，其中 `node->next` 就是新结点，因为第一次扫描我们就是把新结点接在旧结点后面。现在我们把结点的随机指针都接好了，最后一次扫描我们把链表拆成两个，第一个还原原链表，而第二个就是我们要求的复制链表。因为现在链表是旧新更替，只要把每隔两个结点分别相连，对链表进行分割即可。

#### 代码

```cpp
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if(!head) return nullptr;
        for(RandomListNode* cur=head;cur!=nullptr;){
            RandomListNode* node=new RandomListNode(cur->label);
            node->next=cur->next;
            cur->next=node;
            cur=node->next;
        }
        for(RandomListNode* cur=head;cur!=nullptr;){
            if(cur->random)
                cur->next->random=cur->random->next;
            cur=cur->next->next;
        }
        RandomListNode* new_head=head->next;
        RandomListNode* res=new_head;
        RandomListNode* cur=head;
        while(cur){
            cur->next=new_head->next;
            cur=cur->next;
            if(cur){
                new_head->next=cur->next;    
            }
            new_head=new_head->next;
        }
        return res;
        
    }
};
```

### 141.Linked List Cycle

Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space?

#### 解析

如果一个指针走一步，一个指针走两步，两个指针开始指向的结点不同，若干步以后两个指针指向同一个结点，说明存在循环。遇到有任意一个指针指向nullptr说明不存在循环。

#### 代码

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(!head) return false;
        ListNode* p1=head;
        ListNode* p2=head->next;
        while(p2&&p2->next&&p2->next->next&&p1){
            if(p1==p2)
                return true;
            p1=p1->next;
            p2=p2->next->next;
        }
        return false;
    }
};
```

### 142.Linked List Cycle II

Given a linked list, return the node where the cycle begins. If there is no cycle, return `null`.

**Note:** Do not modify the linked list.

**Follow up**:
Can you solve it without using extra space?

#### 解析

和《剑指offer》[链表中环的入口结点](https://github.com/starFalll/Sword-pointing-to-offer#55%E9%93%BE%E8%A1%A8%E4%B8%AD%E7%8E%AF%E7%9A%84%E5%85%A5%E5%8F%A3%E7%BB%93%E7%82%B9) 是一样的题。

找是否成环可以看 141.Linked List Cycle 题。找到环以后绕环一圈即为环的大小n。

然后又是两个指针指向头结点，第一个指针先走n步，然后两个指针一起走，相遇即是入口结点。

#### 代码

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        int n=0;
        if(hasCycle(head,n)==false) return nullptr;
        ListNode* p1=head;
        ListNode* p2=p1;
        for(int i=0;i<n;i++){
            p2=p2->next;
        }
        while(p1!=p2){
            p1=p1->next;
            p2=p2->next;
        }
        return p1;
    }
    
    bool hasCycle(ListNode *head,int& n) {
        if(!head) return false;
        ListNode* p1=head;
        ListNode* p2=head->next;
        while(p2&&p2->next&&p2->next->next&&p1){
            if(p1==p2){
                n=1;
                while(p2->next!=p1){
                    n++;
                    p2=p2->next;
                }
                return true;
            }
            p1=p1->next;
            p2=p2->next->next;
        }
        return false;
    }
};
```

### 143.Reorder List

Given a singly linked list *L*: *L*0→*L*1→…→*L**n*-1→*L*n,
reorder it to: *L*0→*L**n*→*L*1→*L**n*-1→*L*2→*L**n*-2→…

You may **not** modify the values in the list's nodes, only nodes itself may be changed.

**Example 1:**

```
Given 1->2->3->4, reorder it to 1->4->2->3.
```

**Example 2:**

```
Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
```

#### 解析

找到中间结点，断开，将后半截链表反转，再顺序拼接。

#### 代码

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    void reorderList(ListNode* head) {
        if(!head||!head->next) return;
        int n=0;
        ListNode* p=head;
        while(p){
            p=p->next;
            n++;
        }
        p=head;
        for(int i=0;i<n/2;i++){
            p=p->next;
        }
        ListNode* p1=p;
        ListNode* flag=p;
        ListNode* p2=nullptr;
        while(p1){
            p=p->next;
            p1->next=p2;
            p2=p1;
            p1=p;
        }
        p=head;
        while(p->next!=flag){
            ListNode* tmp=p->next;
            p->next=p2;
            p2=p2->next;
            p->next->next=tmp;
            p=tmp;
        }
        p->next=p2;
        
    }
};
```

### 146.LRU Cache

Design and implement a data structure for [Least Recently Used (LRU) cache](https://en.wikipedia.org/wiki/Cache_replacement_policies#LRU). It should support the following operations: `get` and `put`.

`get(key)` - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
`put(key, value)` - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

**Follow up:**
Could you do both operations in **O(1)** time complexity?

**Example:**

```
LRUCache cache = new LRUCache( 2 /* capacity */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
```

#### 解析

为了使查找、插入和删除都有较高的性能，这题的关键是要使用一个双向链表和一个HashMap，因为：

- HashMap保存每个节点的地址，可以基本保证在`O(1)`时间内查找节点
- 双向链表能够在`O(1)`时间内添加和删除节点，单链表则不行

具体实现细节：

- 越靠近链表头部，表示节点上次访问距离现在时间最短，尾部的节点表示最近访问最少
- 访问节点时，如果节点存在，把该节点交换到链表头部，同时更新hash表中该节点的地址
- 插入节点时，如果cache的size达到了上限capacity，则删除尾部节点，同时要在hash表中删除对应的项；新节点插入链表头部

C++的`std::list` 就是个双向链表，且它有个 `splice()`方法，`O(1)`时间，非常好用。

#### 代码

```cpp
class LRUCache {
private:
    struct CacheNode{
        int key;
        int value;
        CacheNode(int k,int v):key(k),value(v){}
    };
    list<CacheNode> cacheList;
    unordered_map<int,list<CacheNode>::iterator> cacheMap;
    int _capacity;
public:
    LRUCache(int capacity) {
        this->_capacity=capacity;
    }
    
    int get(int key) {
        if(cacheMap.find(key)==cacheMap.end()) return -1;
        //put node to list head and update map
        cacheList.splice(cacheList.begin(),cacheList,cacheMap[key]);
        cacheMap[key]=cacheList.begin();
        return cacheMap[key]->value;
    }
    
    void put(int key, int value) {
        if(cacheMap.find(key)==cacheMap.end()){
            if(cacheList.size()==_capacity){
                cacheMap.erase(cacheList.back().key);
                cacheList.pop_back();
            }
            cacheList.push_front(CacheNode(key,value));
            cacheMap[key]=cacheList.begin();
        }
        else{
            cacheMap[key]->value=value;
            cacheList.splice(cacheList.begin(),cacheList,cacheMap[key]);
            cacheMap[key]=cacheList.begin();
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
```

### 460.LFU Cache

Design and implement a data structure for [Least Frequently Used (LFU)](https://en.wikipedia.org/wiki/Least_frequently_used) cache. It should support the following operations: `get` and `put`.

`get(key)` - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
`put(key, value)` - Set or insert the value if the key is not already present. When the cache reaches its capacity, it should invalidate the least frequently used item before inserting a new item. For the purpose of this problem, when there is a tie (i.e., two or more keys that have the same frequency), the least **recently** used key would be evicted.

**Follow up:**
Could you do both operations in **O(1)** time complexity?

**Example:**

```
LFUCache cache = new LFUCache( 2 /* capacity */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.get(3);       // returns 3.
cache.put(4, 4);    // evicts key 1.
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
```

#### 解析

这道题是让我们实现最近不常用页面置换算法LFU (Least Frequently Used), 之前我们做过一道类似的题[LRU Cache](https://github.com/starFalll/LeetCode/blob/master/146.LRU%20Cache.md)，让我们求最近最少使用页面置换算法LRU (Least Recnetly Used)。两种算法虽然名字看起来很相似，但是其实是不同的。顾名思义，LRU算法是首先淘汰最长时间未被使用的页面，而LFU是先淘汰一定时间内被访问次数最少的页面。光说无凭，举个例子来看看，比如说我们的cache的大小为3，然后我们按顺序存入 5，4，5，4，5，7，这时候cache刚好被装满了，因为put进去之前存在的数不会占用额外地方。那么此时我们想再put进去一个8，如果使用LRU算法，应该将4删除，因为4最久未被使用，而如果使用LFU算法，则应该删除7，因为7被使用的次数最少，只使用了一次。相信这个简单的例子可以大概说明二者的区别。

这道题比之前那道LRU的题目还要麻烦一些，因为那道题只要用个list把数字按时间顺序存入，链表底部的位置总是最久未被使用的，每次删除底部的值即可。而这道题不一样，由于需要删除最少次数的数字，那么我们必须要统计每一个key出现的次数，所以我们用一个哈希表m来记录当前数据{key, value}和其出现次数之间的映射，这样还不够，为了方便操作，我们需要把相同频率的key都放到一个list中，那么需要另一个哈希表freq来建立频率和一个里面所有key都是当前频率的list之间的映射。由于题目中要我们在O(1)的时间内完成操作了，为了快速的定位freq中key的位置，我们再用一个哈希表iter来建立key和freq中key的位置之间的映射。最后当然我们还需要两个变量cap和minFreq，分别来保存cache的大小，和当前最小的频率。

为了更好的讲解思路，我们还是用例子来说明吧，我们假设cache的大小为2，假设我们已经按顺序put进去5，4，那么来看一下内部的数据是怎么保存的，由于value的值并不是很重要，为了不影响key和frequence，我们采用value#来标记：

m:

5 -> {value5, 1}

4 -> {value4, 1}

freq:

1 -> {5，4}

iter:

4 -> list.begin() + 1

5 -> list.begin()

这应该不是很难理解，m中5对应的频率为1，4对应的频率为1，然后freq中频率为1的有4和5。iter中是key所在freq中对应链表中的位置的iterator。然后我们的下一步操作是get(5)，下面是get需要做的步骤：

1. 如果m中不存在5，那么返回-1
2. 从freq中频率为1的list中将5删除
3. 将m中5对应的frequence值自增1
4. 将5保存到freq中频率为2的list的末尾
5. 在iter中保存5在freq中频率为2的list中的位置
6. 如果freq中频率为minFreq的list为空，minFreq自增1
7. 返回m中5对应的value值

经过这些步骤后，我们再来看下此时内部数据的值：

m:

5 -> {value5, 2}

4 -> {value4, 1}

freq:

1 -> {4}

2 -> {5}

iter:

4 -> list.begin()

5 -> list.begin()

这应该不是很难理解，m中5对应的频率为2，4对应的频率为1，然后freq中频率为1的只有4，频率为2的只有5。iter中是key所在freq中对应链表中的位置的iterator。然后我们下一步操作是要put进去一个7，下面是put需要做的步骤：

1. 如果调用get(7)返回的结果不是-1，那么在将m中7对应的value更新为当前value，并返回
2. 如果此时m的大小大于了cap，即超过了cache的容量，则：

　　a）在m中移除minFreq对应的list的首元素的纪录，即移除4 -> {value4, 1}

　　b）在iter中清除4对应的纪录，即移除4 -> list.begin()

　　c）在freq中移除minFreq对应的list的首元素，即移除4

3. 在m中建立7的映射，即 7 -> {value7, 1}
4. 在freq中频率为1的list末尾加上7
5. 在iter中保存7在freq中频率为1的list中的位置
6. minFreq重置为1

经过这些步骤后，我们再来看下此时内部数据的值：

m:

5 -> {value5, 2}

7 -> {value7, 1}

freq:

1 -> {7}

2 -> {5}

iter:

7 -> list.begin()

5 -> list.begin()	

#### 代码

```cpp
class LFUCache {
private:
    int _cap;
    int minfrq;
    unordered_map<int,pair<int,int>> m;//key to {value,freq}
    unordered_map<int,list<int>::iterator> miter;//key to list iterator
    unordered_map<int,list<int>> mfrq;//freq to key list
public:
    LFUCache(int capacity) {
        _cap=capacity;
    }
    
    int get(int key) {
        if(m.count(key)==0) return -1;
      	//change key's freq add 1,and move key's position
        mfrq[m[key].second].erase(miter[key]);
        m[key].second++;
        mfrq[m[key].second].push_back(key);
        miter[key]=--mfrq[m[key].second].end();
        if(mfrq[minfrq].size()==0)
            minfrq++;
        return m[key].first;
    }
    
    void put(int key, int value) {
        if(_cap<=0) return;
        int find=get(key);
        if(find!=-1){
            m[key].first=value;
            //there were already move key's position in get operation
            return;
        }
        if(m.size()==_cap){//remove minfrq key
            m.erase(mfrq[minfrq].front());
            miter.erase(mfrq[minfrq].front());
            mfrq[minfrq].pop_front();
        }
        m[key]={value,1};
        mfrq[1].push_back(key);
        miter[key]=--mfrq[1].end();
        minfrq=1;
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache obj = new LFUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
```

## 字符串

### 125.Valid Palindrome

Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

**Note:** For the purpose of this problem, we define empty string as valid palindrome.

**Example 1:**

```
Input: "A man, a plan, a canal: Panama"
Output: true

```

**Example 2:**

```
Input: "race a car"
Output: false
```

#### 代码

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        if(s.size()==0) return true;
        auto head=s.begin();
        auto last=--s.end();
        while(head<last){
            while(!isalnum(*head)&&head<last)head++;
            while(!isalnum(*last)&&head<last)last--;
            if(toupper(*head)!=toupper(*last))
                return false;
            head++;last--;
        }
        return true;
    }
};
```

### 680.Valid Palindrome II

Given a non-empty string `s`, you may delete **at most** one character. Judge whether you can make it a palindrome.

**Example 1:**

```
Input: "aba"
Output: True

```

**Example 2:**

```
Input: "abca"
Output: True
Explanation: You could delete the character 'c'.
```

**Note:**

1. The string will only contain lowercase characters a-z. The maximum length of the string is 50000.

#### 解析

注意左右两边删除一个字母都可以成立的情况，这种情况一般只有一边删除了可以形成回文

#### 代码

```cpp
class Solution {
public:
    bool validPalindrome(string s) {
        if(s.size()==0) return false;
        for(int i=0,j=s.size()-1;i<j;i++,j--){
            if(s[i]!=s[j]){
                int i1=i+1,j1=j,i2=i,j2=j-1;
                while(s[i1]==s[j1]&&i1<j1){
                    i1++;j1--;
                }
                while(s[i2]==s[j2]&&i2<j2){
                    i2++;j2--;
                }
                return i1>=j1||i2>=j2;
            }
        }
        return true;
            
    }
};
```

### 28.Implement strStr()

Implement [strStr()](http://www.cplusplus.com/reference/cstring/strstr/).

Return the index of the first occurrence of needle in haystack, or **-1** if needle is not part of haystack.

**Example 1:**

```
Input: haystack = "hello", needle = "ll"
Output: 2

```

**Example 2:**

```
Input: haystack = "aaaaa", needle = "bba"
Output: -1

```

**Clarification:**

What should we return when `needle` is an empty string? This is a great question to ask during an interview.

For the purpose of this problem, we will return 0 when `needle` is an empty string. This is consistent to C's [strstr()](http://www.cplusplus.com/reference/cstring/strstr/) and Java's [indexOf()](https://docs.oracle.com/javase/7/docs/api/java/lang/String.html#indexOf(java.lang.String)).

#### 解析

字符串匹配，可以使用暴力或者kmp，面试的时候暴力即可，但是要bug free

注意，类似于i\<haystack.size()-needle.size()+1，当i=0时候仍然会判true，因为c++中容器的size返回的是size_t类型，大小由机器位数决定，32位机器为4字节无符号数，64位为8字节无符号数，所以haystack.size()-needle.size()+1\>0

#### 代码

暴力：

```cpp
class Solution {
public:
    int strStr(string haystack, string needle) {
        if(needle.size()==0) return 0;
        const int n=haystack.size()-needle.size()+1;
        for(int i=0;i<n;i++){
            if(haystack[i]==needle[0]){
                int j=0,k=i;
                while(j<needle.size()&&k<haystack.size()){
                    if(haystack[k]!=needle[j])
                        break;
                    j++;k++;
                }
                if(j==needle.size())
                    return i;
            }
        }
        return -1;
    }
};
```

### 8.String to Integer (atoi)

Implement `atoi` which converts a string to an integer.

The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned.

**Note:**

- Only the space character `' '` is considered as whitespace character.
- Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231,  231 − 1]. If the numerical value is out of the range of representable values, INT_MAX (231 − 1) or INT_MIN (−231) is returned.

**Example 1:**

```
Input: "42"
Output: 42

```

**Example 2:**

```
Input: "   -42"
Output: -42
Explanation: The first non-whitespace character is '-', which is the minus sign.
             Then take as many numerical digits as possible, which gets 42.

```

**Example 3:**

```
Input: "4193 with words"
Output: 4193
Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.

```

**Example 4:**

```
Input: "words and 987"
Output: 0
Explanation: The first non-whitespace character is 'w', which is not a numerical 
             digit or a +/- sign. Therefore no valid conversion could be performed.
```

**Example 5:**

```
Input: "-91283472332"
Output: -2147483648
Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
             Thefore INT_MIN (−231) is returned.
```

#### 解析

细节题，注意：

- 不规则输入
- 无效格式
- 溢出数据

#### 代码

```cpp
class Solution {
public:
    int myAtoi(string str) {
        if(str.empty())
            return 0;
        long long res=0;
        int flag=0;//0 -> positive number ,1->negative number
        int j=0;
        while(str[j]==' ')
            j++;
        if(str[j]=='-'){
            flag=1;
            j++;
        }
        else if(str[j]=='+'){
            flag=0;
            j++;
        }
        for(;j<str.size();j++){
            
            int tmp=str[j]-'0';
            if(tmp<0||tmp>9){
                break;
            }
            res*=10;  
            res+=tmp;
            if(flag==1&&(-res)<INT_MIN)//out of the range of representable values
            {
                
                return INT_MIN;
            }
                
            else if((flag==0)&&(res>INT_MAX))
                return INT_MAX;
        }
        if(flag==1)
            res=-res;
        return (int)res;
    }
};
```

### 67.Add Binary

Given two binary strings, return their sum (also a binary string).

The input strings are both **non-empty** and contains only characters `1` or `0`.

**Example 1:**

```
Input: a = "11", b = "1"
Output: "100"
```

**Example 2:**

```
Input: a = "1010", b = "1011"
Output: "10101"
```

#### 代码

```cpp
class Solution {
public:
    string addBinary(string a, string b) {
        string res="";
        int i=a.size()-1,j=b.size()-1;
        int flag=0;//carry
        while(i>=0||j>=0||flag==1){
            flag+=i>=0?a[i--]-'0':0;
            flag+=j>=0?b[j--]-'0':0;
            res=char(flag%2+'0')+res;
            flag/=2;
        }
        return res;
    }
};
```

### 5.Longest Palindromic Substring

Given a string **s**, find the longest palindromic substring in **s**. You may assume that the maximum length of **s** is 1000.

**Example 1:**

```
Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.

```

**Example 2:**

```
Input: "cbbd"
Output: "bb"
```

#### 解析

本题为最大回文子串，动态规划解法为：

复杂度`O(n^2)`。设状态为`f(i,j)`，表示区间[i,j]是否为回文串，则状态转移方程为

![动态规划方程](https://i.loli.net/2018/09/20/5ba3971846fb5.png)

其他解法（暴力解法，Manacher 算法）请见这篇文章 [最长回文子串——Manacher 算法](https://segmentfault.com/a/1190000003914228)

#### 代码

动态规划解法：

```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        const int n=s.size();
        bool f[1000][1000] = {false};
        int maxlen=1,start=0;
        for(int j=0;j<n;j++){
            f[j][j]=true;
            for(int i=0;i<j;i++){
                f[i][j]=(s[i]==s[j]&&(j-i<2||f[i+1][j-1]));//dp equation
                if(maxlen<=(j-i+1)&&f[i][j]){
                    maxlen=j-i+1;
                    start=i;
                }     
            }
        }
        return s.substr(start,maxlen);
    }
};
```



Manacher 算法解法：

```cpp
class Solution {
public:
    string longestPalindrome(string s) {
        if(s.size()==0) return "";
        string add=preProcess(s);
        int maxright=0,maxlen=0,pos=0,res=0;
        int RL[add.size()]={0};
        for(int i=0;i<add.size();i++){
            if(i<maxright)
                RL[i]=min(RL[pos*2-i],maxright-i+1);
            else
                RL[i]=1;
            while(i-RL[i]+1>=0&&RL[i]+i<=add.size()&&add[i+RL[i]]==add[i-RL[i]])
                RL[i]++;
            if(i+RL[i]-1>maxright){
                maxright=i+RL[i]-1;
                pos=i;
            }
            
            if(maxlen<=RL[i]){
                res=i;
                maxlen=RL[i];
            }
            
        }
        return s.substr((res-maxlen+1)/2,maxlen-1);
        
    }
    string preProcess(const string& s){
        int n=s.size();
        string ret="";
        for(int i=0;i<n;i++)
            ret+='#'+s.substr(i,1);
        ret+='#';
        return ret;
    }
};
```

### 14.Longest Common Prefix

Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string `""`.

**Example 1:**

```
Input: ["flower","flow","flight"]
Output: "fl"

```

**Example 2:**

```
Input: ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.

```

**Note:**

All given inputs are in lowercase letters `a-z`.

#### 解析

以第一个string为基准，其他string相同位置与之对比。

#### 代码

```cpp
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()) return "";
        for(int i=0;i<strs[0].size();i++){
            for(int j=1;j<strs.size();j++){
                if(strs[0][i]!=strs[j][i])
                    return strs[0].substr(0,i);
            }
            
        }
        return strs[0];
    }
};
```

### 3.Longest Substring Without Repeating Characters

Given a string, find the length of the **longest substring** without repeating characters.

**Example 1:**

```
Input: "abcabcbb"
Output: 3 
Explanation: The answer is "abc", with the length of 3. 

```

**Example 2:**

```
Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

```

**Example 3:**

```
Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. 
             Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
```

#### 解析

用hash table存储不同的char

#### 代码

```cpp
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char,int> tb;
        int maxlen=0,start=0,curlen=0;
        for(int i=0;i<s.size();i++){
            if(tb.find(s[i])!=tb.end()){
                for(int j=start;j<tb[s[i]];j++){
                    tb.erase(s[j]);
                }
                start=tb[s[i]]+1;
                curlen=i-start+1;
            }
            else{
                curlen++;
            }
            tb[s[i]]=i;
            maxlen=max(maxlen,curlen);
        }
        return maxlen;
    }
};
```

### 10.Regular Expression Matching

Given an input string (`s`) and a pattern (`p`), implement regular expression matching with support for `'.'` and `'*'`.

```
'.' Matches any single character.
'*' Matches zero or more of the preceding element.
```

The matching should cover the **entire** input string (not partial).

**Note:**

- `s` could be empty and contains only lowercase letters `a-z`.
- `p` could be empty and contains only lowercase letters `a-z`, and characters like `.` or `*`.

**Example 1:**

```
Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

```

**Example 2:**

```
Input:
s = "aa"
p = "a*"
Output: true
Explanation: '*' means zero or more of the precedeng element, 'a'. Therefore, by repeating 'a' once, it becomes "aa".

```

**Example 3:**

```
Input:
s = "ab"
p = ".*"
Output: true
Explanation: ".*" means "zero or more (*) of any character (.)".

```

**Example 4:**

```
Input:
s = "aab"
p = "c*a*b"
Output: true
Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore it matches "aab".

```

**Example 5:**

```
Input:
s = "mississippi"
p = "mis*is*p*."
Output: false
```

#### 解析

'.' 和 当前字符匹配是一样的情况，但是'*'要复杂很多。

第二个字符是 '*' 的时候，如果模式中的字符匹配，分为两种情况：

1. 指向 s 字符串的指针移到下一个字符，指向 p 字符串的不变
2. 指向 s 字符串的指针不变，指向 p 字符串的往后移到两个字符

#### 代码

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty())    return s.empty();
        
        if ('*' == p[1])
            return (isMatch(s, p.substr(2)) || !s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p));
        else
            return !s.empty() && (s[0] == p[0] || '.' == p[0]) && isMatch(s.substr(1), p.substr(1));
    }
};
```

### 44.Wildcard Matching

Given an input string (`s`) and a pattern (`p`), implement wildcard pattern matching with support for `'?'` and `'*'`.

```
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

```

The matching should cover the **entire** input string (not partial).

**Note:**

- `s` could be empty and contains only lowercase letters `a-z`.
- `p` could be empty and contains only lowercase letters `a-z`, and characters like `?` or `*`.

**Example 1:**

```
Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".

```

**Example 2:**

```
Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.

```

**Example 3:**

```
Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.

```

**Example 4:**

```
Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".

```

**Example 5:**

```
Input:
s = "acdcb"
p = "a*c?b"
Output: false
```

#### 解析

对于s中的每个元素
如果* s == * p 或 * p ==‘? 这意味着这是匹配，然后转到下一个元素s ++， p ++。
如果p =='*’，这也是一个匹配，这时候可能一个或多个字符是可用的，所以让我们保存这个 \* 的位置和匹配的s位置。
如果不匹配，那么我们检查是否有*在之前出现过：

- 如果没有*，则返回false；
- 如果有\*，我们将当前p设置为*的下一个元素，并将当前s设置为下一个保存的s位置。

例如

abed 
？b * d ** 

a = ?,继续，b = b，继续，
e = \*，保存*位置prev = 3，保存位置ss = 3，p ++ 
e！= d，检查是否存在a *，存在，则 ss ++，s = ss；p = prev + 1 
d = d，继续，结束。
检查p中的剩余元素，如果所有都是*，则为true，否则为false; 

**请注意，在char数组中，最后一个是NOT NULL，要检查结尾，请使用“\*p”或“* p =='\0'。**

#### 代码

```cpp
class Solution {
public:
    bool isMatch(string s, string p) {
        return isMatch(s.c_str(),p.c_str());
    }
private:
    bool isMatch(const char * s,const char* p)
    {
        const char * prev=nullptr;
        const char * ss=s;
        while(*s){
            if(*s==*p||*p=='?'){
                s++;p++;continue;
            }
            if(*p=='*'){
                prev=p++;
                ss=s;
                continue;
            }
            if(prev){
                p=prev+1;
                s=++ss;
                continue;
            }
            return false;
        }
        while(*p=='*')p++;
        return !*p;
    }
};
```

### 65.Valid Number

Validate if a given string can be interpreted as a decimal number.

Some examples:
`"0"` => `true`
`" 0.1 "` => `true`
`"abc"` => `false`
`"1 a"` => `false`
`"2e10"` => `true`
`" -90e3   "` => `true`
`" 1e"` => `false`
`"e3"` => `false`
`" 6e-1"` => `true`
`" 99e2.5 "` => `false`
`"53.5e93"` => `true`
`" --6 "` => `false`
`"-+3"` => `false`
`"95a54e53"` => `false`

**Note:** It is intended for the problem statement to be ambiguous. You should gather all requirements up front before implementing one. However, here is a list of characters that can be in a valid decimal number:

- Numbers 0-9
- Exponent - "e"
- Positive/negative sign - "+"/"-"
- Decimal point - "."

Of course, the context of these characters also matters in the input.

**Update (2015-02-10):**
The signature of the `C++` function had been updated. If you still see your function signature accepts a `const char *` argument, please click the reload button to reset your code definition.

#### 解析

和剑指offer中的表示 [数值的字符串](https://github.com/starFalll/Sword-pointing-to-offer#53%E8%A1%A8%E7%A4%BA%E6%95%B0%E5%80%BC%E7%9A%84%E5%AD%97%E7%AC%A6%E4%B8%B2) 差不多，只是多了前后的空格。

在数值之前可能有一个表示正负的’-‘或者’+’。接下来是若干个 0 到 9 的数位表示数值的整数部分（在某些小数里可能没有数值的整数部分）。如果数值是一个小数，那么在小数点后面可能会有若干个 0 到 9 的数位表示数值的小数部分。如果数值用科学计数法表示，接下来是一个’e’或者‘E’，以及紧跟着的一个整数（可以有正负号）表示指数。

判断一个字符串是否符合上述模式时，首先看第一个字符是不是正负号。如果是，在字符串上移动一个字符，继续扫描剩余的字符串中 0 到 9 的数位。如果是一个小数，则将遇到小数点。另外，如果是用科学计数法表示的数值，在整数或者小数的后面还有可能遇到’e’或者’E’。

#### 代码

```cpp
class Solution {
public:
    bool isNumber(string s) {
        if(s.empty())return false;
        auto p=s.begin();
        auto end=s.end();
        bool num=scanInt(p,end);
        if(*p=='.'){
            p++;
            num=scanUnsignedInt(p,end)||num;
        }
        if(*p=='e'||*p=='E'){
            p++;
            num=num&&scanInt(p,end);
        }
        while(p!=end&&*p==' ')
            p++;
        return num&&(p==end);
    }
    
    bool scanUnsignedInt(string::iterator& p,string::iterator& end)
    {
        auto first=p;
        while(p!=end&&*p>='0'&&*p<='9')
            p++;
        return p>first;
    }
    bool scanInt(string::iterator& p,string::iterator& end)
    {
        while(*p==' ')
            p++;
        if(*p=='+'||*p=='-')
            p++;
        return scanUnsignedInt(p,end);
    }
    
};
```

### 12.Integer to Roman

Roman numerals are represented by seven different symbols: `I`, `V`, `X`, `L`, `C`, `D` and `M`.

```
Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
```

For example, two is written as `II` in Roman numeral, just two one's added together. Twelve is written as, `XII`, which is simply `X` + `II`. The number twenty seven is written as `XXVII`, which is `XX` + `V` + `II`.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not `IIII`. Instead, the number four is written as `IV`. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as `IX`. There are six instances where subtraction is used:

- `I` can be placed before `V` (5) and `X` (10) to make 4 and 9. 
- `X` can be placed before `L` (50) and `C` (100) to make 40 and 90. 
- `C` can be placed before `D` (500) and `M` (1000) to make 400 and 900.

Given an integer, convert it to a roman numeral. Input is guaranteed to be within the range from 1 to 3999.

**Example 1:**

```
Input: 3
Output: "III"
```

**Example 2:**

```
Input: 4
Output: "IV"
```

**Example 3:**

```
Input: 9
Output: "IX"
```

**Example 4:**

```
Input: 58
Output: "LVIII"
Explanation: C = 100, L = 50, XXX = 30 and III = 3.

```

**Example 5:**

```
Input: 1994
Output: "MCMXCIV"
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
```

#### 代码

```
class Solution {
public:
    string intToRoman(int num) {
        const int number[]={1000,900,500,400,100,90,50,40,10,9,5,4,1};
        const string s[]={"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
        string res="";
        for(int i=0;num>0;i++){
            int count=num/number[i];
            num%=number[i];
            while(count>0){
                res+=s[i];
                count--;
            }
        }
        return res;
    }
};
```



### 13.Roman to Integer

Roman numerals are represented by seven different symbols: `I`, `V`, `X`, `L`, `C`, `D` and `M`.

```
Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
```

For example, two is written as `II` in Roman numeral, just two one's added together. Twelve is written as, `XII`, which is simply `X` + `II`. The number twenty seven is written as `XXVII`, which is `XX` + `V` + `II`.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not `IIII`. Instead, the number four is written as `IV`. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as `IX`. There are six instances where subtraction is used:

- `I` can be placed before `V` (5) and `X` (10) to make 4 and 9. 
- `X` can be placed before `L` (50) and `C` (100) to make 40 and 90. 
- `C` can be placed before `D` (500) and `M` (1000) to make 400 and 900.

Given a roman numeral, convert it to an integer. Input is guaranteed to be within the range from 1 to 3999.

**Example 1:**

```
Input: "III"
Output: 3
```

**Example 2:**

```
Input: "IV"
Output: 4
```

**Example 3:**

```
Input: "IX"
Output: 9
```

**Example 4:**

```
Input: "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.

```

**Example 5:**

```
Input: "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
```

#### 代码

```cpp
class Solution {
private:
    unordered_map<char,int> chmap;
public:
    int romanToInt(string s) {
        chmap['I']=1;
        chmap['V']=5;
        chmap['X']=10;
        chmap['L']=50;
        chmap['C']=100;
        chmap['D']=500;
        chmap['M']=1000;
        int res=0;
        for(int i=0;i<s.size();){
            if(i+1<s.size()&&chmap[s[i]]<chmap[s[i+1]]){
                res+=chmap[s[i+1]]-chmap[s[i]];
                i+=2;
            }
            else{
                res+=chmap[s[i]];
                i++;
            }
        }
        return res;
        
    }
};
```

### 38.Count and Say

The count-and-say sequence is the sequence of integers with the first five terms as following:

```
1.     1
2.     11
3.     21
4.     1211
5.     111221

```

`1` is read off as `"one 1"` or `11`.
`11` is read off as `"two 1s"` or `21`.
`21` is read off as `"one 2`, then `one 1"` or `1211`.

Given an integer *n* where 1 ≤ *n* ≤ 30, generate the *n*th term of the count-and-say sequence.

Note: Each term of the sequence of integers will be represented as a string.

 

**Example 1:**

```
Input: 1
Output: "1"

```

**Example 2:**

```
Input: 4
Output: "1211"
```

#### 解析

这道题的题意很难理解，题意是n=1时输出字符串1；n=2时，数上次字符串中的数值个数，因为上次字符串有1个1，所以输出11；n=3时，由于上次字符是11，有2个1，所以输出21；n=4时，由于上次字符串是21，有1个2和1个1，所以输出1211。依次类推，写个countAndSay(n)函数返回字符串。

#### 代码

```cpp
class Solution {
public:
    string countAndSay(int n) {
        string ret="1";
        if(n==1)
            return ret;
        string tmp;
        while(--n>0){
            tmp=ret;
            ret="";
            int len=tmp.size();
            int i=0;
            while(i<len){
                int j=i+1;
                while(j<len&&j-i<9&&tmp[i]==tmp[j]) j++;
                ret+=((j-i)+'0');
                ret+=tmp[i];
                i=j;
            }
        }
        return ret;
    }
};
```

### 49.Group Anagrams

Given an array of strings, group anagrams together.

**Example:**

```
Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
Output:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]
```

#### 代码

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>> strmap;
        for(auto s:strs){
            string key=s;
            sort(key.begin(),key.end());
            strmap[key].push_back(s);
        }
        vector<vector<string>> res;
        for(auto it=strmap.cbegin();it!=strmap.cend();it++){
            res.push_back(it->second);
        }
        return res;
    }
};
```

### 58.Length of Last Word

Given a string *s* consists of upper/lower-case alphabets and empty space characters `' '`, return the length of last word in the string.

If the last word does not exist, return 0.

**Note:** A word is defined as a character sequence consists of non-space characters only.

**Example:**

```
Input: "Hello World"
Output: 5
```

#### 代码

```cpp
class Solution {
public:
    int lengthOfLastWord(string s) {
        int len=0;
        for(auto i=s.begin();i!=s.end();){
            if(*i++!=' '){
                len++;
            }
            else if(i!=s.end()&&*i!=' '){
                len=0;
            }
        }
        return len;
    }
};
```



### 71.Simplify Path

Given an absolute path for a file (Unix-style), simplify it. 

For example,
**path** = `"/home/"`, => `"/home"`
**path** = `"/a/./b/../../c/"`, => `"/c"`
**path** = `"/a/../../b/../c//.//"`, => `"/c"`
**path** = `"/a//b////c/d//././/.."`, => `"/a/b/c"`

In a UNIX-style file system, a period ('.') refers to the current directory, so it can be ignored in a simplified path. Additionally, a double period ("..") moves up a directory, so it cancels out whatever the last directory was. For more information, look here: <https://en.wikipedia.org/wiki/Path_(computing)#Unix_style>

**Corner Cases:**

- Did you consider the case where **path** = `"/../"`?
  In this case, you should return `"/"`.
- Another corner case is the path might contain multiple slashes `'/'` together, such as `"/home//foo/"`.
  In this case, you should ignore redundant slashes and return `"/home/foo"`.

#### 解析

分为四种情况：

1. "/../" or"/.."，这种需要返回上一目录
2. 多个连续斜杠，只需要在字符串末尾加一个斜杠
3. "/../"，忽略
4. 剩下的就是目录或者文件

#### 代码

````cpp
class Solution {
public:
    string simplifyPath(string path) {
        string res="/";
        if(path.empty()) return res;
        for(auto i=path.begin();i!=path.end();){
            if(*i=='/'){//solve ///
               if(*(res.end()-1)!='/')
                   res.push_back('/');
                i++;
               }
            else if(*(i-1)=='/'&&*i=='.'&&(i+1)!=path.end()&&*(i+1)=='.'&&((i+2)==path.end()||*(i+2)=='/')){// solve "/../" or"/.."
                res.pop_back();
                while(!res.empty()&&*(res.end()-1)!='/')
                    res.pop_back();
                
                i=i+2;
            }
            else if(*i!='.'||((i+1)!=path.end()&&*(i+1)!='/')){
                while(*i!='/'&&i!=path.end()){
                    res.push_back(*i);
                    i++;
                }
            }
            else{//solve "/./"
                i++;
            }
        }
        if(*(res.end()-1)=='/'&&res.size()!=1)
            res.pop_back();
        if(res.empty())
            res.push_back('/');
        return res;
        
    }
};
````

## 栈

### 20.Valid Parentheses

Given a string containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is valid.

An input string is valid if:

1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.

Note that an empty string is also considered valid.

**Example 1:**

```
Input: "()"
Output: true

```

**Example 2:**

```
Input: "()[]{}"
Output: true

```

**Example 3:**

```
Input: "(]"
Output: false

```

**Example 4:**

```
Input: "([)]"
Output: false

```

**Example 5:**

```
Input: "{[]}"
Output: true
```

#### 解析

既可以用stack保存左边的符号，也可以用string（因为有pop_back方法）。

#### 代码

```cpp
class Solution {
public:
    bool isValid(string s) {
        if(s.empty()) return true;
        unordered_map<char,char> index;
        index['(']=')';
        index['[']=']';
        index['{']='}';
        string res="";
        for(auto i=s.begin();i!=s.end();i++){
            if(*i=='('||*i=='{'||*i=='['){
                res+=*i;
            }
            else{
                if(index[*(res.end()-1)]!=*i){
                    return false;
                }
                else{
                    res.pop_back();
                }
            }
        }
        return res.empty();
    }
};
```

### 32.Longest Valid Parentheses

Given a string containing just the characters `'('` and `')'`, find the length of the longest valid (well-formed) parentheses substring.

**Example 1:**

```
Input: "(()"
Output: 2
Explanation: The longest valid parentheses substring is "()"

```

**Example 2:**

```
Input: ")()())"
Output: 4
Explanation: The longest valid parentheses substring is "()()"
```

#### 解析

1. 从头到尾扫描字符串。
2. 如果当前字符是 '('，将其下标 push 到堆栈。如果当前字符是 ')' 并且堆栈顶部索引处的字符是 '('，我们找到一匹配的字符串，所以从堆栈弹出。否则，我们将 ')' 的下标 push 到堆栈。
3. 扫描完成后，堆栈将只包含无法匹配的字符下标。观察可以发现：相邻下标之间的子串应该是有效的括号。
4. 如果堆栈为空，则整个输入字符串有效。否则，我们可以扫描堆栈以获得最长的有效子字符串，如步骤3中所述。

#### 代码

```cpp
class Solution {
public:
    int longestValidParentheses(string s) {
        if(s.empty()) return 0;
        stack<int> lefts;
        int longest=0;
        for(int i=0;i<s.size();i++){
            if(s[i]=='(') lefts.push(i);
            else{
                if(!lefts.empty()&&s[lefts.top()]=='(')
                    lefts.pop();
                else
                    lefts.push(i);
            }
        }
        if(lefts.empty()) 
            longest=s.size();
        else{
            int a=s.size(),b=0;
            while(!lefts.empty()){
                b=lefts.top();lefts.pop();
                longest=max(longest,a-b-1);
                a=b;
            }
            longest=max(longest,a);
        }
        return longest;
        
    }
};
```

### 84.Largest Rectangle in Histogram

Given *n* non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.

![img](https://leetcode.com/static/images/problemset/histogram.png)
Above is a histogram where width of each bar is 1, given height = `[2,1,5,6,2,3]`.

 

![img](https://leetcode.com/static/images/problemset/histogram_area.png)
The largest rectangle is shown in the shaded area, which has area = `10` unit.

 

**Example:**

```
Input: [2,1,5,6,2,3]
Output: 10
```

#### 解析

这道题目算是比较难的一道题目了，首先最简单的做法就是对于任意一个bar，向左向右遍历，直到高度小于该bar，这时候计算该区域的矩形区域面积。对于每一个bar，我们都做如上处理，最后就可以得到最大值了。当然这种做法是O(n^2)，过不了大数据集合测试。

从上面我们直到，对于任意一个bar n，我们得到的包含该bar n的矩形区域里面bar n是最小的。我们使用ln和rn来表示bar n向左以及向右第一个小于bar n的bar的索引位置。

譬如题目中的bar 2的高度为5，它的ln为1，rn为4。包含bar 2的矩形区域面积为(4 - 1 - 1) * 5 = 10。

我们可以从左到右遍历所有bar，并将其push到一个stack中，如果当前bar的高度小于栈顶bar，我们pop出栈顶的bar，同时以该bar计算矩形面积。那么我们如何知道该bar的ln和rn呢？rn铁定就是当前遍历到的bar的索引，而ln则是当前的栈顶bar的索引，因为此时栈顶bar的高度一定小于pop出来的bar的高度。

为了更好的处理最后一个bar的情况，我们在实际中会插入一个高度为0的bar，这样就能pop出最后一个bar并计算了。

#### 代码

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        if(heights.empty()) return 0;
        stack<int> res;
        heights.push_back(0);
        int result=0;
        for(int i=0;i<heights.size();){
            if(res.empty()||heights[i]>heights[res.top()])
                res.push(i++);
            else{
                int tmp=res.top();
                res.pop();
                result=max(result,heights[tmp]*(res.empty()?i:i-res.top()-1));
            }
        }
        return result;
    }
};
```

### 150.Evaluate Reverse Polish Notation

Evaluate the value of an arithmetic expression in [Reverse Polish Notation](http://en.wikipedia.org/wiki/Reverse_Polish_notation).

Valid operators are `+`, `-`, `*`, `/`. Each operand may be an integer or another expression.

**Note:**

- Division between two integers should truncate toward zero.
- The given RPN expression is always valid. That means the expression would always evaluate to a result and there won't be any divide by zero operation.

**Example 1:**

```
Input: ["2", "1", "+", "3", "*"]
Output: 9
Explanation: ((2 + 1) * 3) = 9

```

**Example 2:**

```
Input: ["4", "13", "5", "/", "+"]
Output: 6
Explanation: (4 + (13 / 5)) = 6

```

**Example 3:**

```
Input: ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"]
Output: 22
Explanation: 
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22

```

#### 解析

逆波兰表达式，做计算器会用到。

#### 代码

```cpp
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        if(tokens.empty()) return 0;
        stack<string> s;
        for(int i=0;i<tokens.size();i++){
            if(tokens[i].size()!=1||string("+-*/").find(tokens[i])==string::npos)
                s.push(tokens[i]);
            else{
                int n2=stoi(s.top());
                s.pop();
                int n1=stoi(s.top());
                s.pop();
                switch(tokens[i][0]){
                case '+':n1+=n2;break;
                case '-':n1-=n2;break;
                case '*':n1*=n2;break;
                case '/':n1/=n2;break;
                }
                s.push(to_string(n1));
            }
        }
        return stoi(s.top());
    }
};
```

## 二叉树

### 144. Binary Tree Preorder Traversal

Given a binary tree, return the *preorder* traversal of its nodes' values.

**Example:**

```
Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,2,3]

```

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        if(!root) return res;
        res.push_back(root->val);
        vector<int> tmp1=preorderTraversal(root->left);
        vector<int> tmp2=preorderTraversal(root->right);
        res.insert(res.end(),tmp1.begin(),tmp1.end());
        res.insert(res.end(),tmp2.begin(),tmp2.end());
        return res;
        
    }
};
```

### 94.Binary Tree Inorder Traversal

Given a binary tree, return the *inorder* traversal of its nodes' values.

**Example:**

```
Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [1,3,2]
```

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        if(!root) return res;
        vector<int> tmp1=inorderTraversal(root->left);
        res.insert(res.end(),tmp1.begin(),tmp1.end());
        res.push_back(root->val);
        vector<int> tmp2=inorderTraversal(root->right);
        res.insert(res.end(),tmp2.begin(),tmp2.end());
        return res;
    }
};
```

### 145.Binary Tree Postorder Traversal

Given a binary tree, return the *postorder* traversal of its nodes' values.

**Example:**

```
Input: [1,null,2,3]
   1
    \
     2
    /
   3

Output: [3,2,1]
```

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if(!root) return res;
        vector<int> tmp1=postorderTraversal(root->left);
        vector<int> tmp2=postorderTraversal(root->right);
        res.insert(res.end(),tmp1.begin(),tmp1.end());
        res.insert(res.end(),tmp2.begin(),tmp2.end());
        res.push_back(root->val);
        return res;
    }
};
```

### 102.Binary Tree Level Order Traversal

Given a binary tree, return the *level order* traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree `[3,9,20,null,null,15,7]`,

```
    3
   / \
  9  20
    /  \
   15   7

```

return its level order traversal as:

```
[
  [3],
  [9,20],
  [15,7]
]
```

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;
        queue<TreeNode*> q,next;
        q.push(root);
        while(!q.empty()){
            vector<int> line;
            while(!q.empty()){
                TreeNode* tmp=q.front();
                q.pop();
                line.push_back(tmp->val);
                if(tmp->left) next.push(tmp->left);
                if(tmp->right) next.push(tmp->right);
            }
            res.push_back(line);
            swap(q,next);
        }
        return res;
    }
};
```

### 107.Binary Tree Level Order Traversal II

Given a binary tree, return the *bottom-up level order* traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree `[3,9,20,null,null,15,7]`,

```
    3
   / \
  9  20
    /  \
   15   7

```

return its bottom-up level order traversal as:

```
[
  [15,7],
  [9,20],
  [3]
]
```

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;
        queue<TreeNode*> q,next;
        q.push(root);
        while(!q.empty()){
            vector<int> line;
            while(!q.empty()){
                TreeNode* tmp=q.front();
                q.pop();
                line.push_back(tmp->val);
                if(tmp->left) next.push(tmp->left);
                if(tmp->right) next.push(tmp->right);
            }
            res.push_back(line);
            swap(q,next);
        }
        reverse(res.begin(),res.end());
        return res;
    }
};
```

### 103.Binary Tree Zigzag Level Order Traversal

Given a binary tree, return the *zigzag level order* traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree `[3,9,20,null,null,15,7]`,

```
    3
   / \
  9  20
    /  \
   15   7

```

return its zigzag level order traversal as:

```
[
  [3],
  [20,9],
  [15,7]
]
```

#### 解析

每隔一层反转一次。

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;
        queue<TreeNode*> q,next;
        q.push(root);
        bool flag=false;//false for postive
        while(!q.empty()){
            vector<int> line;
            while(!q.empty()){   
                TreeNode* tmp=q.front();
                q.pop();
                line.push_back(tmp->val);
                if(tmp->left) next.push(tmp->left);
                if(tmp->right) next.push(tmp->right);
                
            }
            if(flag){
                reverse(line.begin(),line.end());
                flag=false;
            }
            else
                flag=true;
            res.push_back(line);
            swap(q,next);
        }
        return res;
    }
};
```

### 99.Recover Binary Search Tree

Two elements of a binary search tree (BST) are swapped by mistake.

Recover the tree without changing its structure.

**Example 1:**

```
Input: [1,3,null,null,2]

   1
  /
 3
  \
   2

Output: [3,1,null,null,2]

   3
  /
 1
  \
   2

```

**Example 2:**

```
Input: [3,1,4,null,null,2]

  3
 / \
1   4
   /
  2

Output: [2,1,4,null,null,3]

  2
 / \
1   4
   /
  3
```

#### 解析

二叉搜索树中序遍历的结果为单调递增的序列。

##### 普通方法

此题使用普通中序遍历的解法是使用一个vector保存中序遍历的结点指针，然后寻找两处逆向的位置，即顺序遍历vector，其中第一个大于后面一个数的数 a 和后面小于a的最大数交换。此种方法时间复杂度为O(n)，空间复杂度为O(n)。

##### Morris遍历

使用Morris遍历通过调整树的结构，可以只用O(1)的空间复杂度实现对二叉树的遍历。

。下图是Morris算法对二叉树遍历的完整的过程。

[![img](https://oychao.github.io/images/BTree.svg)](https://oychao.github.io/images/BTree.svg)

Morris中序遍历的流程

从图中的说明可以看出，Morris的最核心的思想就是：找到当前节点中序遍历的前驱结点，并将前驱节点的右节点指向当前节点，知道当前节点的左子树处理完成后，再将树结构调整回原状。

总结Morris中序遍历算法过程如下：

1. 初始化当前节点指向根节点

2. 如果当前节点不为空

   - 如果当前节点没有左节点

     - 输出当前节点的数据
     - 设置当前节点指向当前节点的右节点

   - 如果当前节点存在左节点

     - 寻找当前节点的左子树的最右节点的右节点，设置其为前驱结点

       - 如果前驱结点的右节点为空，则将其右节点指向当前节点（还未遍历过，需要修改树结构）

         并设置当前节点指向当前节点的左节点

       - 如果前驱节点的右节点已经指向当前节点，则将其右节点置空（已经遍历过，将树结构修改回原样）

         并设置当前节点指向当前节点的右节点

##### Leetcode优化方法

disscuss区的方法，使用普通中序遍历，用三个指针，一个prev记录前序结点的位置，一个first记录第一个要交换的结点，一个last记录第二个要交换的结点。

#### 代码

##### Morris中序遍历

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void recoverTree(TreeNode* root) {
        pair<TreeNode*,TreeNode*> broken;
        TreeNode* prev=nullptr;//inorder traversal's previous node
        TreeNode* cur=root;
        while(cur){
            if(!cur->left){
                select(broken,prev,cur);
                prev=cur;
                cur=cur->right;
            }
            else{
                auto node=cur->left;
                while(node->right&&node->right!=cur)
                    node=node->right;
                if(node->right==nullptr){
                    node->right=cur;
                    cur=cur->left;
                }
                else{
                    select(broken,prev,cur);
                    node->right=nullptr;
                    prev=cur;
                    cur=cur->right;
                }
            }
        }
        swap(broken.first->val,broken.second->val);
    }
    void select(pair<TreeNode*,TreeNode*>& b,TreeNode* prev,TreeNode* cur){
        if(prev!=nullptr&&prev->val>cur->val){//The previous node of the inorder traversal is larger than the current node,select the mistake
            if(b.first==nullptr){
                b.first=prev;
            }
            b.second=cur;
        }
    }
};
```

##### Leetcode优化方法

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    TreeNode* first=nullptr;
    TreeNode* last=nullptr;
    TreeNode* prev=new TreeNode(INT_MIN);
public:
    void recoverTree(TreeNode* root) {
        traverse(root);
        swap(first->val,last->val);
    }
    void traverse(TreeNode* root){
        if(!root)
            return;
        traverse(root->left);
        if(!first&&prev->val>root->val){
            first=prev;
        }
        if(first&&prev->val>root->val){
            last=root;
        }
        prev=root;
        traverse(root->right);
    }
};
```

### 100.Same Tree

Given two binary trees, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical and the nodes have the same value.

**Example 1:**

```
Input:     1         1
          / \       / \
         2   3     2   3

        [1,2,3],   [1,2,3]

Output: true

```

**Example 2:**

```
Input:     1         1
          /           \
         2             2

        [1,2],     [1,null,2]

Output: false

```

**Example 3:**

```
Input:     1         1
          / \       / \
         2   1     1   2

        [1,2,1],   [1,1,2]

Output: false
```

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(!p&&!q) return true;
        if(!p||!q||p->val!=q->val) return false;
        return isSameTree(p->left,q->left)&&isSameTree(p->right,q->right);
    }
};
```

### 101.Symmetric Tree

Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree `[1,2,2,3,4,4,3]` is symmetric:

```
    1
   / \
  2   2
 / \ / \
3  4 4  3

```

But the following `[1,2,2,null,3,null,3]` is not:

```
    1
   / \
  2   2
   \   \
   3    3
```

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(!root) return true;
        return isSymmetric(root->left,root->right);
    }
    bool isSymmetric(TreeNode* p,TreeNode* q)
    {
        if(!p&&!q) return true;
        if(!p||!q) return false;
        return p->val==q->val&&isSymmetric(p->left,q->right)&&isSymmetric(p->right,q->left);
    }
    
};
```

### 110.Balanced Binary Tree

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:

> a binary tree in which the depth of the two subtrees of *every* node never differ by more than 1.

**Example 1:**

Given the following tree `[3,9,20,null,null,15,7]`:

```
    3
   / \
  9  20
    /  \
   15   7
```

Return true.
**Example 2:**

Given the following tree `[1,2,2,3,3,null,null,4,4]`:

```
       1
      / \
     2   2
    / \
   3   3
  / \
 4   4

```

Return false.

#### 解析

基于DFS。我们在DFS递归中返回当前节点的高度。当当前节点（包括当前结点）的子树平衡时，函数ifbalance（）返回非负值作为高度。否则返回-1。根据两个孩子的 left 和 right，父节点可以检查子树是否平衡，并确定其返回值。

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return ifbalance(root) != -1;
    }
    
    int ifbalance(TreeNode* root)
    {
        if(!root) return 0;
        int left=ifbalance(root->left);
        if(left==-1) return -1;
        int right=ifbalance(root->right);
        if(right==-1) return -1;
        if(abs(left-right)>1) return -1;
        return max(left,right) + 1;
    }
};
```

### 114.Flatten Binary Tree to Linked List

Given a binary tree, flatten it to a linked list in-place.

For example, given the following tree:

```
    1
   / \
  2   5
 / \   \
3   4   6

```

The flattened tree should look like:

```
1
 \
  2
   \
    3
     \
      4
       \
        5
         \
          6
```

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    void flatten(TreeNode* root) {
        flatten(root,nullptr);
    }
    
    TreeNode* flatten(TreeNode* root,TreeNode* tail)
    {
        if(root==nullptr) return tail;
      	//root is list ,and tail behind it
        root->right=flatten(root->left,flatten(root->right,tail));
        root->left=nullptr;
        
        return root;
        
    }
};
```

### 116.Populating Next Right Pointers in Each Node

Given a binary tree

```
struct TreeLinkNode {
  TreeLinkNode *left;
  TreeLinkNode *right;
  TreeLinkNode *next;
}

```

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to `NULL`.

Initially, all next pointers are set to `NULL`.

**Note:**

- You may only use constant extra space.
- Recursive approach is fine, implicit stack space does not count as extra space for this problem.
- You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).

**Example:**

Given the following perfect binary tree,

```
     1
   /  \
  2    3
 / \  / \
4  5  6  7

```

After calling your function, the tree should look like:

```
     1 -> NULL
   /  \
  2 -> 3 -> NULL
 / \  / \
4->5->6->7 -> NULL
```

#### 代码

1.通用版本，不仅仅适用于完全二叉树

````cpp
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        while(root){
            TreeLinkNode* prev=nullptr;
            TreeLinkNode* next=nullptr;
            for(;root;root=root->next){
                if(!next) next=root->left?root->left:root->right;
                if(root->left){
                    if(prev) prev->next=root->left;
                    prev=root->left;
                }
                if(root->right){
                    if(prev) prev->next=root->right;
                    prev=root->right;
                }
            }
            root=next;
        }
    }
};
````

2.仅仅适用于完全二叉树

```cpp
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        if(!root) return;
        if(!root->left&&!root->right) return;
        root->left->next=root->right;
        if(root->next){
            root->right->next=root->next->left;
        }
        connect(root->left);
        connect(root->right);
    }
};
```



### 117.Populating Next Right Pointers in Each Node II

Given a binary tree

```
struct TreeLinkNode {
  TreeLinkNode *left;
  TreeLinkNode *right;
  TreeLinkNode *next;
}

```

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to `NULL`.

Initially, all next pointers are set to `NULL`.

**Note:**

- You may only use constant extra space.
- Recursive approach is fine, implicit stack space does not count as extra space for this problem.

**Example:**

Given the following binary tree,

```
     1
   /  \
  2    3
 / \    \
4   5    7

```

After calling your function, the tree should look like:

```
     1 -> NULL
   /  \
  2 -> 3 -> NULL
 / \    \
4-> 5 -> 7 -> NULL
```

#### 解析

和116题的代码一样。

#### 代码

```cpp
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  TreeLinkNode *left, *right, *next;
 *  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
 * };
 */
class Solution {
public:
    void connect(TreeLinkNode *root) {
        while(root){
            TreeLinkNode* prev=nullptr;
            TreeLinkNode* next=nullptr;
            for(;root;root=root->next){
                if(!next) next=root->left?root->left:root->right;
                if(root->left){
                    if(prev) prev->next=root->left;
                    prev=root->left;
                }
                if(root->right){
                    if(prev) prev->next=root->right;
                    prev=root->right;
                }
            }
            root=next;
        }
    }
};
```

### 105.Construct Binary Tree from Preorder and Inorder Traversal

Given preorder and inorder traversal of a tree, construct the binary tree.

**Note:**
You may assume that duplicates do not exist in the tree.

For example, given

```
preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
```

Return the following binary tree:

```
    3
   / \
  9  20
    /  \
   15   7
```

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTree(preorder.begin(),preorder.end(),inorder.begin(),inorder.end());
    }
    template<typename Input>
    TreeNode* buildTree(Input pre_first,Input pre_last,Input in_first,Input in_last)
    {
        if(pre_first==pre_last) return nullptr;
        if(in_first==in_last) return nullptr;
        auto root=new TreeNode(*pre_first);
        auto inroot=find(in_first,in_last,*pre_first);
        auto leftlen=distance(in_first,inroot);
        root->left=buildTree(pre_first+1,pre_first+1+leftlen,in_first,inroot);
        root->right=buildTree(pre_first+1+leftlen,pre_last,inroot+1,in_last);
        
        return root;
    }
};
```

### 106.Construct Binary Tree from Inorder and Postorder Traversal

Given inorder and postorder traversal of a tree, construct the binary tree.

**Note:**
You may assume that duplicates do not exist in the tree.

For example, given

```
inorder = [9,3,15,20,7]
postorder = [9,15,7,20,3]
```

Return the following binary tree:

```
    3
   / \
  9  20
    /  \
   15   7
```

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
         return buildTree(inorder.begin(),inorder.end(),postorder.begin(),postorder.end());
    }
    template<typename Input>
    TreeNode* buildTree(Input in_first,Input in_last,Input post_first,Input post_last)
    {
        if(in_first==in_last) return nullptr;
        if(post_first==post_last) return nullptr;
        auto root=new TreeNode(*(post_last-1));
        auto inroot=find(in_first,in_last,*(post_last-1));
        auto leftlen=distance(in_first,inroot);
        root->left=buildTree(in_first,inroot,post_first,post_first+leftlen);
        root->right=buildTree(inroot+1,in_last,post_first+leftlen,post_last-1);
        
        return root;
    }
};
```

### 96.Unique Binary Search Trees

Given *n*, how many structurally unique **BST's** (binary search trees) that store values 1 ... *n*?

**Example:**

```
Input: 3
Output: 5
Explanation:
Given n = 3, there are a total of 5 unique BST's:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
```

#### 解析

如果把上例的顺序改一下，就可以看出规律了。

```
 1       1           2          3       3
  \       \         / \        /       / 
   3       2       1   3      2       1
  /         \                /         \
2            3              1           2

```

比如，以1为根的树的个数，等于左子树的个数乘以右子树的个数，左子树是0个元素的树，右子树是2个元素的树。以2为根的树的个数，等于左子树的个数乘以右子树的个数，左子树是1个元素的树，右子树也是1个元素的树。依此类推。

当数组为 `1,2,3,...,n`时，基于以下原则的构建的BST树具有唯一性： \textbf{以i为根节点的树，其左子树由[1, i-1]构成， 其右子树由[i+1, n]构成。}

定义`f(i)`为以`[1,i]`能产生的Unique Binary Search Tree的数目，则

如果数组为空，毫无疑问，只有一种BST，即空树，`f(0)=1`。

如果数组仅有一个元素{1}，只有一种BST，单个节点，`f(1)=1`。

如果数组有两个元素{1,2}， 那么有如下两种可能

```
1             2
  \          /
    2      1

```

$f(2) = f(0) * f(1)$，when 1 as root

\+ $ f(1) * f(0) $ ，when 2 as root

再看一看3个元素的数组，可以发现BST的取值方式如下：

$f(3) = f(0) * f(2)$ ，when 1 as root

\+ $f(1) * f(1)$ ，when 2 as root

\+$ f(2) * f(0)$ ，when 3 as root

所以，由此观察，可以得出`f`的递推公式为

$f(i) = \sum_{k=1}^{i} f(k-1) \times f(i-k)$

至此，问题划归为一维动态规划。

#### 代码

```cpp
class Solution {
public:
    int numTrees(int n) {
        vector<int> f(n+1,0);
        f[0]=1;
        f[1]=1;
        for(int i=2;i<=n;i++)
            for(int j=1;j<=i;j++)
                f[i]+=f[j-1]*f[i-j];
        return f[n];
    }
};
```

### 95.Unique Binary Search Trees II

Given an integer *n*, generate all structurally unique **BST's** (binary search trees) that store values 1 ... *n*.

**Example:**

```
Input: 3
Output:
[
  [1,null,3,2],
  [3,2,null,1],
  [3,1,null,null,2],
  [2,1,3],
  [1,null,2,null,3]
]
Explanation:
The above output corresponds to the 5 unique BST's shown below:

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3

```

#### 解析

见上一题(96)

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> res;
        if(n==0) return res;//escape input 0
        return generate(1,n);
    }
    vector<TreeNode*> generate(int start,int end)
    {
        vector<TreeNode*> res;
        if(start>end){
            res.push_back(nullptr);
            return res;
        }
        for(int i=start;i<=end;i++)//root from start to end
        {
            vector<TreeNode*> leftnode=generate(start,i-1);
            vector<TreeNode*> rightnode=generate(i+1,end);
            for(auto k:leftnode)
                for(auto m:rightnode){//one situation for root i
                    TreeNode* node=new TreeNode(i);
                    node->left=k;
                    node->right=m;
                    res.push_back(node);
                }
        }
        return res;
    }
};
```

### 98.Validate Binary Search Tree

Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

- The left subtree of a node contains only nodes with keys **less than** the node's key.
- The right subtree of a node contains only nodes with keys **greater than** the node's key.
- Both the left and right subtrees must also be binary search trees.

**Example 1:**

```
Input:
    2
   / \
  1   3
Output: true

```

**Example 2:**

```
    5
   / \
  1   4
     / \
    3   6
Output: false
Explanation: The input is: [5,1,4,null,null,3,6]. The root node's value
             is 5 but its right child's value is 4.
```

#### 解析

BST中序遍历顺序的结点数值是递增的，可以利用这个特性求解。

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        TreeNode* prev=nullptr;
        return isValidBST(root,prev);
    }
    bool isValidBST(TreeNode* root,TreeNode*& prev)//inorder
    {
        if(!root) return true;
        if(!isValidBST(root->left,prev)) return false;
        if(prev&&prev->val>=root->val) return false;//if inorder not increment,false
        prev=root;
        return isValidBST(root->right,prev);
        
    }
};
```

### 108.Convert Sorted Array to Binary Search Tree

Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of *every* node never differ by more than 1.

**Example:**

```
Given the sorted array: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5
```

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return sortedArrayToBST(nums,0,nums.size());
        
    }
    TreeNode* sortedArrayToBST(vector<int>& nums,int low,int hight)
    {
        if(low>=hight) return nullptr;
        int mid=(hight+low)/2;
        TreeNode* root=new TreeNode(nums[mid]);
        root->left=sortedArrayToBST(nums,low,mid);
        root->right=sortedArrayToBST(nums,mid+1,hight);
        return root;
    }
    
};
```

### 109.Convert Sorted List to Binary Search Tree

Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of *every* node never differ by more than 1.

**Example:**

```
Given the sorted linked list: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5
```

#### 解析

自底向上，和前一道差不多，只是链表形式只能一个一个往后走。

#### 代码

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        int len=0;
        ListNode* p=head;
        while(p)
        {
            p=p->next;
            len++;
        }
        return sortedListToBST(head,0,len-1);
    }
    TreeNode* sortedListToBST(ListNode*& head,int low,int hight)
    {
        if(low>hight) return nullptr;//low==hight return head
        int mid=low+(hight-low)/2;
        TreeNode* left=sortedListToBST(head,low,mid-1);
        TreeNode* root=new TreeNode(head->val);
        root->left=left;
        head=head->next;
        root->right=sortedListToBST(head,mid+1,hight);
        return root;
    }
};
```

### 111.Minimum Depth of Binary Tree

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

**Note:** A leaf is a node with no children.

**Example:**

Given binary tree `[3,9,20,null,null,15,7]`,

```
    3
   / \
  9  20
    /  \
   15   7
```

return its minimum depth = 2.

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        int min=INT_MAX;
        int res=0;
        res+=minDepth(root->left);
        if(res<min&&res>0)
            min=res;
        res=0;
        res+=minDepth(root->right);
        if(res<min&&res>0)
            min=res;
        if(min==INT_MAX)
            return 1;
        else
            return min+1;
    }
};
```

### 104.Maximum Depth of Binary Tree

Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

**Note:** A leaf is a node with no children.

**Example:**

Given binary tree `[3,9,20,null,null,15,7]`,

```
    3
   / \
  9  20
    /  \
   15   7
```

return its depth = 3.

#### 解析

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        return max(maxDepth(root->left),maxDepth(root->right))+1;
    }
};
```

### 112.Path Sum

Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.

**Note:** A leaf is a node with no children.

**Example:**

Given the below binary tree and `sum = 22`,

```
      5
     / \
    4   8
   /   / \
  11  13  4
 /  \      \
7    2      1

```

return true, as there exist a root-to-leaf path `5->4->11->2` which sum is 22.

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        return hasPathSum(root,sum,0);
    }
    bool hasPathSum(TreeNode* root, int sum,int add){
        if(!root) return false;
        if(!root->left&&!root->right&&root->val+add==sum) return true;
        return hasPathSum(root->left,sum,add+root->val)||hasPathSum(root->right,sum,add+root->val);
    }
};
```

### 113.Path Sum II

Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

**Note:** A leaf is a node with no children.

**Example:**

Given the below binary tree and `sum = 22`,

```
      5
     / \
    4   8
   /   / \
  11  13  4
 /  \    / \
7    2  5   1

```

Return:

```
[
   [5,4,11,2],
   [5,8,4,5]
]
```

#### 解析

和上一题差不多，只是需要求出所有满足条件的路径并保存。

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        vector<int> line;
        pathSum(root,sum,0,res,line);
        return res;
    }
    void pathSum(TreeNode* root, int sum,int add,vector<vector<int>>& res,vector<int>& line)
    {
        if(!root) return;
        if(!root->left&&!root->right&&root->val+add==sum){
            line.push_back(root->val);
            res.push_back(line);
            line.pop_back();
            return;
        }
        line.push_back(root->val);
        pathSum(root->left,sum,add+root->val,res,line);
        pathSum(root->right,sum,add+root->val,res,line);
        line.pop_back();
        return;
    }
};
```

### 124.Binary Tree Maximum Path Sum

Given a **non-empty** binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain **at least one node** and does not need to go through the root.

**Example 1:**

```
Input: [1,2,3]

       1
      / \
     2   3

Output: 6

```

**Example 2:**

```
Input: [-10,9,20,null,null,15,7]

   -10
   / \
  9  20
    /  \
   15   7

Output: 42
```

#### 解析

这道题我们可以采用dfs遍历二叉树，先算出左右树的结果 l 和 r，如果 l 大于0，那么对后续结果有利，便加上这个值，r同理，因为是一条路径，使用 dfs 返回的时只能从左右两条子树中选一条最大的与根节点的和，或者如果两个子树都是小于0的，那么便只返回根节点。

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    int max_sum;
    int dfs(TreeNode* root)
    {
        if(!root) return 0;
        int l=dfs(root->left);
        int r=dfs(root->right);
        int sum=root->val;
        if(l>0) sum+=l;
        if(r>0) sum+=r;
        max_sum=max(max_sum,sum);
        return max(l,r)>0?max(l,r)+root->val:root->val;
    }
public:
    int maxPathSum(TreeNode* root) {
        max_sum=INT_MIN;
        dfs(root);
        return max_sum;
    }
};
```

### 129.Sum Root to Leaf Numbers

Given a binary tree containing digits from `0-9` only, each root-to-leaf path could represent a number.

An example is the root-to-leaf path `1->2->3` which represents the number `123`.

Find the total sum of all root-to-leaf numbers.

**Note:** A leaf is a node with no children.

**Example:**

```
Input: [1,2,3]
    1
   / \
  2   3
Output: 25
Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.
```

**Example 2:**

```
Input: [4,9,0,5,1]
    4
   / \
  9   0
 / \
5   1
Output: 1026
Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.
```

#### 解析

前序遍历，遇到叶节点将这根节点到叶节点一条路径表示的数值加到总数里面。

#### 代码

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    int sum;
    void sumNum(TreeNode* root,int total){
        total=total*10+root->val;
        if(!root->left&&!root->right){
            sum+=total;
            return;
        }
        if(root->left) sumNum(root->left,total);
        if(root->right) sumNum(root->right,total);
        return;
        
    }
public:
    int sumNumbers(TreeNode* root) {
        sum=0;
        if(!root) return 0;
        sumNum(root,0);
        return sum;
    }
};
```

## 排序

### 88.Merge Sorted Array

Given two sorted integer arrays *nums1* and *nums2*, merge *nums2* into *nums1* as one sorted array.

**Note:**

- The number of elements initialized in *nums1* and *nums2* are *m* and *n* respectively.
- You may assume that *nums1* has enough space (size that is greater or equal to *m* + *n*) to hold additional elements from *nums2*.

**Example:**

```
Input:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

Output: [1,2,2,3,5,6]
```

#### 解析

nums1的空间大于等于 m+n，则可以从末尾往前排序。

#### 代码

```cpp
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i=m+n-1;
        int l1=m-1;
        int l2=n-1;
        while(l1>=0&&l2>=0){
            nums1[i--]=nums2[l2]>=nums1[l1]?nums2[l2--]:nums1[l1--];
        }
        while(l2>=0){
            nums1[i--]=nums2[l2--];
        }
    }
};
```

### 21.Merge Two Sorted Lists

Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

**Example:**

```
Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4
```

#### 代码

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode dummy(-1);
        ListNode* res=&dummy;
        if(!l1) return l2;
        if(!l2) return l1;
        while(l1&&l2){
            if(l1->val>l2->val){
                res->next=l2;
                l2=l2->next;
            }
            else{
                res->next=l1;
                l1=l1->next;
            }
            res=res->next;
        }
        if(l1){
            res->next=l1;
        }else if(l2){
            res->next=l2;
        }
        return dummy.next;
    }
};
```

### 23.Merge k Sorted Lists

Merge *k* sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

**Example:**

```
Input:
[
  1->4->5,
  1->3->4,
  2->6
]
Output: 1->1->2->3->4->4->5->6
```

#### 解析

可以复用[之前一题](https://github.com/starFalll/LeetCode/blob/master/algorithms/21.Merge%20Two%20Sorted%20Lists.md)的代码。时间复杂度为O(n1+n2+n3+....)。

#### 代码

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
private:
    ListNode* mergeLists(ListNode* p1,ListNode* p2)
    {
        if(!p1) return p2;
        if(!p2) return p1;
        ListNode dummy(-1);
        ListNode* res=&dummy;   
        while(p1&&p2){
            if(p1->val>p2->val){
                res->next=p2;
                p2=p2->next;
            }
            else{
                res->next=p1;
                p1=p1->next;
            }
            res=res->next;
        }
        if(p1){
            res->next=p1;
        }else if(p2){
            res->next=p2;
        }
        return dummy.next;
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return nullptr;
        ListNode* p=lists[0];
        for(int i=1;i<lists.size();i++){
            p=mergeLists(p,lists[i]);
        }
        return p;
    }
    
};
```

### 147.Insertion Sort List

Sort a linked list using insertion sort.


![img](https://upload.wikimedia.org/wikipedia/commons/0/0f/Insertion-sort-example-300px.gif)
A graphical example of insertion sort. The partial sorted list (black) initially contains only the first element in the list.
With each iteration one element (red) is removed from the input data and inserted in-place into the sorted list


**Algorithm of Insertion Sort:**

1. Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list.
2. At each iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted list, and inserts it there.
3. It repeats until no input elements remain.

**Example 1:**

```
Input: 4->2->1->3
Output: 1->2->3->4

```

**Example 2:**

```
Input: -1->5->3->4->0
Output: -1->0->3->4->5
```

#### 解析

链表插入排序，从开始找，可以用一个新的链表来代表排序后的链表，就是图中黑色的框所代表的内容。

#### 代码

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
private:
    ListNode* findPre(ListNode* head,int x)
    {
        ListNode* pre=nullptr;
        ListNode* p=head;
        while(p&&p->val<=x){
            pre=p;
            p=p->next;
        }
        return pre;
    }
public:
    ListNode* insertionSortList(ListNode* head) {
        if(!head) return nullptr;
        ListNode dummy(INT_MIN);
        ListNode* cur=head;
        while(cur){
            auto pos=findPre(&dummy,cur->val);
            auto tmp=cur->next;
            cur->next=pos->next;
            pos->next=cur;
            cur=tmp;
        }
        return dummy.next;
    }
    
};
```

### 148.Sort List

Sort a linked list in *O*(*n* log *n*) time using constant space complexity.

**Example 1:**

```
Input: 4->2->1->3
Output: 1->2->3->4

```

**Example 2:**

```
Input: -1->5->3->4->0
Output: -1->0->3->4->5
```

#### 代码

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
private:
    ListNode* merge2Lists(ListNode* l1,ListNode* l2)
    {
        ListNode dummy(-1);
        ListNode* p= &dummy;
        while(l1&&l2){
            if(l1->val>l2->val){
                p->next=l2;
                l2=l2->next;
            }
            else{
                p->next=l1;
                l1=l1->next;
            }
            p=p->next;
        }
        if(l1){
            p->next=l1;
        }else if(l2){
            p->next=l2;
        }
        return dummy.next;
    }
public:
    ListNode* sortList(ListNode* head) {
        if(!head||!head->next) return head;
        /*
        step 1: split list into two parts
        */
        ListNode* fast=head,*slow=head;
        while(fast->next&&fast->next->next){//find mid node(slow)
            fast=fast->next->next;
            slow=slow->next;
        }
        fast=slow;
        slow=slow->next;
        fast->next=nullptr;
        /*
        step 2: sort each part l1 and l2
        */
        ListNode* l=sortList(head);
        ListNode* r=sortList(slow);
        /*
        step 3: merge step
        */
        return merge2Lists(l,r);
        
    }
    
};
```

### 41.First Missing Positive

Given an unsorted integer array, find the smallest missing positive integer.

**Example 1:**

```
Input: [1,2,0]
Output: 3

```

**Example 2:**

```
Input: [3,4,-1,1]
Output: 2

```

**Example 3:**

```
Input: [7,8,9,11,12]
Output: 1

```

**Note:**

Your algorithm should run in *O*(*n*) time and uses constant extra space.

#### 解析

##### 方法1

使用hash table 存储 nums 中的内容，然后顺序遍历正数，从 i 到 INT_MAX，返回第一个不在  hash table 中的数。

##### 方法2

本质上是桶排序，每当 `A[i]!=i+1` 的时候，将 `A[i]` 与 `A[A[i]-1]` 交换，也就是把每个数字放回对应的下标的位置，直到交换完，即 `A[i]==i+1`。

#### 代码

##### 方法1

```cpp
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        if(nums.empty()) return 1;
        unordered_map<int,bool> index;
        for(int i=0;i<nums.size();i++){
            index[nums[i]]=true;
        }
        for(int i=1;i<=INT_MAX;i++){
            if(index.find(i)==index.end()){
                return i;
            }
        }
        return -1;
    }
};
```

##### 方法2

```cpp
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n=nums.size();
        for(int i=0;i<n;i++){
            while(nums[i]!=i+1){
                int tmp=nums[i];
                if(tmp<=0||tmp>n)break;
                if(nums[tmp-1]==tmp)break;
                swap(nums[tmp-1],nums[i]);
            }
        }
        for(int i=0;i<n;i++){
            if(nums[i]!=i+1) return i+1;
        }
        return n+1;
    }
};
```

### 75.Sort Colors

Given an array with *n* objects colored red, white or blue, sort them **in-place **so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

**Note:** You are not suppose to use the library's sort function for this problem.

**Example:**

```
Input: [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
```

**Follow up:**

- A rather straight forward solution is a two-pass algorithm using counting sort.
  First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.
- Could you come up with a one-pass algorithm using only constant space?

#### 解析

设置两个index，最开始一个位于头部，一个位于尾部，变量 i 从0开始遍历如果指向的内容是2则 i 和尾部交换，尾部往前走；如果 i 指向 0，则和头部交换，头部往后走。

#### 代码

```cpp
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int zero = 0;
        int second = nums.size()-1;
        for(int i = 0; i <= second; i++)
        {
            while (nums[i] == 2 && i < second) {
                swap(nums[i], nums[second--]);
            }
            while (nums[i] == 0 && i > zero)
            {
                swap(nums[i], nums[zero++]);
            }
        }
    }
};
```

## 查找

### 34.Find First and Last Position of Element in Sorted Array

Given an array of integers `nums` sorted in ascending order, find the starting and ending position of a given `target` value.

Your algorithm's runtime complexity must be in the order of *O*(log *n*).

If the target is not found in the array, return `[-1, -1]`.

**Example 1:**

```
Input: nums = [5,7,7,8,8,10], target = 8
Output: [3,4]
```

**Example 2:**

```
Input: nums = [5,7,7,8,8,10], target = 6
Output: [-1,-1]
```

#### 解析

使用二分法。

#### 代码

```cpp
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res={-1,-1};
        if(nums.empty()) return res;
        if(target<nums[0]||target>nums[nums.size()-1]) return res;
        int low=0,high=nums.size()-1;
        while(low<=high){
            int mid=(low+high)/2;
            if(target<nums[mid]){
                high=mid-1;
            }
            else if(target>nums[mid]){
                low=mid+1;
            }
            else{
                high=mid-1;
                res[0]=mid;
            }
        }
        low=0,high=nums.size()-1;
        while(low<=high){
            int mid=(low+high)/2;
            if(target<nums[mid]){
                high=mid-1;
            }
            else if(target>nums[mid]){
                low=mid+1;
            }
            else{
                low=mid+1;
                res[1]=mid;
            }
        }
        return res;
    }
};
```

### 35.Search Insert Position

Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

**Example 1:**

```
Input: [1,3,5,6], 5
Output: 2

```

**Example 2:**

```
Input: [1,3,5,6], 2
Output: 1

```

**Example 3:**

```
Input: [1,3,5,6], 7
Output: 4

```

**Example 4:**

```
Input: [1,3,5,6], 0
Output: 0
```

#### 解析

可以顺序遍历，也可以二分法。对于二分法来说，终止条件是 `low>high`，又因为目标值在 [low,high+1] 之内，所以 `low<=high+1`，综上我们知道 `[low, high+1] = [low, low]`，所以 low 就是目标值的下标。

#### 代码

顺序遍历：

```cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        for(int i=0;i<nums.size();i++){
            if(nums[i]==target)
                return i;
            else if(nums[i]>target)
                return i;
        }
        return nums.size();
    }
};
```

二分法：

```cpp
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int low=0,high=nums.size()-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(nums[mid]==target)
                return mid;
            else if(nums[mid]>target)
                high=mid-1;
            else
                low=mid+1;
        }
        return low;
    }
};
```

### 74.Search a 2D Matrix

Write an efficient algorithm that searches for a value in an *m* x *n* matrix. This matrix has the following properties:

- Integers in each row are sorted from left to right.
- The first integer of each row is greater than the last integer of the previous row.

**Example 1:**

```
Input:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 3
Output: true

```

**Example 2:**

```
Input:
matrix = [
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
target = 13
Output: false
```

#### 解析

先找到目标值所在的列再用二分法查找。

#### 代码

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()||matrix[0].empty()) return false;
        int row=-1;
        int n=matrix[0].size()-1;
        for(int i=0;i<matrix.size();i++){
            if(matrix[i][n]>=target){
                row=i;
                break;
            }
        }
        if(row<0)return false;
        int low=0,high=matrix[row].size()-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(matrix[row][mid]==target){
                return true;
            }
            else if(matrix[row][mid]>target)
                high=mid-1;
            else
                low=mid+1;
        }
        return false;
    }
};
```

## 回溯法

### 78.Subsets

Given a set of **distinct** integers, *nums*, return all possible subsets (the power set).

**Note:** The solution set must not contain duplicate subsets.

**Example:**

```
Input: nums = [1,2,3]
Output:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
```

#### 解析

##### 递归法

使用增量构造的方法，每个元素都有两种选择，选或者不选。

##### 迭代法I

使用二进制法，本方法的前提是：集合的元素不超过int位数。用一个int整数表示位向量，第`i`位为1，则表示选择`S[i]`，为0则不选择。例如 `S={A,B,C,D}`，则`0110=6`表示子集 `{B,C}`。

这种方法最巧妙。因为它不仅能生成子集，还能方便的表示集合的并、交、差等集合运算。设两个集合的位向量分别为B_1和B_2，则$B_1\cup B_2, B_1 \cap B_2, B_1 \triangle B_2B1∪B2,B1∩B2,B1△B2$分别对应集合的并、交、对称差。

二进制法，也可以看做是位向量法，只不过更加优化。

##### 迭代法II

起始subset集为：[]
添加S0后为：[], **[S0]**
添加S1后为：[], [S0], **[S1], [S0, S1]**
添加S2后为：[], [S0], [S1], [S0, S1],** [S2], [S0, S2], [S1, S2], [S0, S1, S2]**
加粗subset为每次新增的。显然规律为添加Si后，新增的subset为克隆现有的所有subset，并在它们后面都加上Si。

#### 代码

##### 递归法

```cpp
class Solution {
private:
    void subset(const vector<int>& S,vector<int>& path,int step,vector<vector<int>>& res)
    {
        if(step==S.size()){
            res.push_back(path);
            return;
        }
        //not choose S[step]
        subset(S,path,step+1,res);
        //choose S[step]
        path.push_back(S[step]);
        subset(S,path,step+1,res);
        path.pop_back();
        return;
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        vector<int> path;
        subset(nums,path,0,res);
        return res;
    }
};
```

##### 迭代法I

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        vector<int> line;
        const int n=nums.size();
        for(int i=0;i<(1<<n);i++){
            for(int j=0;j<n;j++){
                if(i&(1<<j)) line.push_back(nums[j]);
            }
            res.push_back(line);
            line.clear();
        }
        return res;
    }
};
```

##### 迭代法II

```cpp
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> tmp;
        res.push_back(tmp);
        sort(nums.begin(),nums.end());
        for(int i=0;i<nums.size();i++){
            int n=res.size();
            for(int j=0;j<n;j++){
                tmp=res[j];
                tmp.push_back(nums[i]);
                res.push_back(tmp);
            }
        }
        return res;
    }
};
```

### 90.Subsets II

Given a collection of integers that might contain duplicates, **nums**, return all possible subsets (the power set).

**Note:** The solution set must not contain duplicate subsets.

**Example:**

```
Input: [1,2,2]
Output:
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
```

#### 解析

题目和 [上一道题](https://github.com/starFalll/LeetCode/blob/master/algorithms/78.Subsets.md) 差不多，只是集合里面可以有重复的数值。

类似于上一题迭代法II的方法：

例如[1,2,2]

起始subset集为：[]
添加S0后为：[], **[1]**
添加S1后为：[], [1], **[2], [1, 2]**
添加S2后为：[], [1], *[2], [1, 2],* **[2,2], [1,2,2]**
加粗subset为每次新增的。如果新增加的数和排序后没有和前一个数重复，则处理方法和上一题一样；如果重复，那么只有斜体部分末尾才增加，即当前结果的后一半增加。

注意，首先要对nums排序，不然会出错。

#### 代码

```cpp
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> res;
        vector<int> tmp;
        res.push_back(tmp);
        int prev_size=0;
        for(int i=0;i<nums.size();i++){
            const int size=res.size();
            for(int j=0;j<size;j++){
                if(i==0||nums[i]!=nums[i-1]||j>=prev_size){
                    tmp=res[j];
                    tmp.push_back(nums[i]);
                    res.push_back(tmp);
                }
            }
            prev_size=size;
        }
        return res;
    }
};
```

### 46.Permutations

Given a collection of **distinct** integers, return all possible permutations.

**Example:**

```
Input: [1,2,3]
Output:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
```

#### 解析

和 subset 差不多的解决方法，都是使用回溯法。

#### 代码

````cpp
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;
        dfs(nums,path,res);
        return res;
    }
    void dfs(vector<int>& nums,vector<int>& path,vector<vector<int>>& res)
    {
        if(path.size()==nums.size()){
            res.push_back(path);
            return;
        }
        for(auto i:nums){
            auto pos=find(path.begin(),path.end(),i);
            if(pos==path.end()){
                path.push_back(i);
                dfs(nums,path,res);
                path.pop_back();
            }
        }
    }
};
````

### 77.Combinations

Given two integers *n* and *k*, return all possible combinations of *k* numbers out of 1 ... *n*.

**Example:**

```
Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
```

#### 解析

和subset，permutations差不多，都可以采用回溯法。

#### 代码

```c++
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> path;
        vector<int> nums;
        for(int i=1;i<=n;i++){
            nums.push_back(i);
        }
        dfs(nums,k,path,res,0);
        return res;
    }
    
    void dfs(vector<int>& S,int len,vector<int>& path,vector<vector<int>>& res,int deep)
    {
        if(path.size()==len){
            res.push_back(path);
            return;
        }
        for(int i=deep;i<S.size();i++){
            path.push_back(S[i]);
            dfs(S,len,path,res,i+1);
            path.pop_back();
        }
        return;
    }
};
```

### 17.Letter Combinations of a Phone Number

Given a string containing digits from `2-9` inclusive, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

![img](http://upload.wikimedia.org/wikipedia/commons/thumb/7/73/Telephone-keypad2.svg/200px-Telephone-keypad2.svg.png)

**Example:**

```
Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

```

**Note:**

Although the above answer is in lexicographical order, your answer could be in any order you want.

#### 解析

同样是使用回溯法。

#### 代码

```cpp
class Solution {
private:
    const vector<string> keywords={" "," ","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};//0-9
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        string path;
        if(digits.empty()) return res;
        dfs(digits,0,path,res);
        return res;
    }
    void dfs(const string& digits,int len,string& path,vector<string>& res)
    {
        if(len==digits.size())
        {
            res.push_back(path);
            return;
        }
        for(auto i:keywords[digits[len]-'0']){
            path.push_back(i);
            dfs(digits,len+1,path,res);
            path.pop_back();
        }
    }
};
```

## 动态规划

### 62.Unique Paths

A robot is located at the top-left corner of a *m* x *n* grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

![img](https://leetcode.com/static/images/problemset/robot_maze.png)
Above is a 7 x 3 grid. How many possible unique paths are there?

**Note:** *m* and *n* will be at most 100.

**Example 1:**

```
Input: m = 3, n = 2
Output: 3
Explanation:
From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Right -> Down
2. Right -> Down -> Right
3. Down -> Right -> Right

```

**Example 2:**

```
Input: m = 7, n = 3
Output: 28
```

#### 解析

备忘录法和动态规划均可。

设状态为`f[i][j]`，表示从起点`(1,1)`到达`(i,j)`的路线条数，则状态转移方程为：

```
f[i][j]=f[i-1][j]+f[i][j-1]
```

#### 代码

备忘录法

```cpp
class Solution {
private:
    vector<vector<int>> f;
public:
    int uniquePaths(int m, int n) {
        //f[x][y] is the path (0,0)->(x,y)
        f=vector<vector<int>>(m,vector<int>(n,0));
        f[0][0]=1;
        return dfs(m-1,n-1);
    }
    int dfs(int x,int y){
        if(x<0||y<0) return 0;//illegal
        if(x==0||y==0) return f[0][0];//end
        if(f[x][y]>0){
            return f[x][y];
        }else{
            return f[x][y]=dfs(x-1,y)+dfs(x,y-1);
        }
        
    }
};
```

动态规划

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> f(n,0);
        f[0]=1;
        for(int i=0;i<m;i++){
            for(int j=1;j<n;j++){
                f[j]=f[j]+f[j-1];
            }
        }
        return f[n-1];
    }
};
```

### 63.Unique Paths II

A robot is located at the top-left corner of a *m* x *n* grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?

![img](https://leetcode.com/static/images/problemset/robot_maze.png)

An obstacle and empty space is marked as `1` and `0` respectively in the grid.

**Note:** *m* and *n* will be at most 100.

**Example 1:**

```
Input:
[
  [0,0,0],
  [0,1,0],
  [0,0,0]
]
Output: 2
Explanation:
There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right
```

#### 解析

将上一题的备忘录法加几个判断即可。

#### 代码

```cpp
class Solution {
private:
    vector<vector<int>> f;
    int m;
    int n;
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        if(obstacleGrid.empty()) return 0;
        m=obstacleGrid.size();
        n=obstacleGrid[0].size();
        if(obstacleGrid[0][0]||obstacleGrid[m-1][n-1]) return 0;
        f=vector<vector<int>>(m,vector<int>(n,0));
        f[0][0]=1;
        return dfs(m-1,n-1,obstacleGrid);
    }
    int dfs(int x,int y,vector<vector<int>>& obstacleGrid)
    {
        if(x<0||y<0) return 0;
        if(obstacleGrid[x][y]==1){
            return 0;
        }
        if(x==0&&y==0) return f[0][0];
        if(f[x][y]>0){
            return f[x][y];
        }else{
            return f[x][y]=dfs(x-1,y,obstacleGrid)+dfs(x,y-1,obstacleGrid);
        }
    }
};
```

### 50.Pow(x, n)

Implement [pow(*x*, *n*)](http://www.cplusplus.com/reference/valarray/pow/), which calculates *x* raised to the power *n* (xn).

**Example 1:**

```
Input: 2.00000, 10
Output: 1024.00000

```

**Example 2:**

```
Input: 2.10000, 3
Output: 9.26100

```

**Example 3:**

```
Input: 2.00000, -2
Output: 0.25000
Explanation: 2-2 = 1/22 = 1/4 = 0.25

```

**Note:**

- -100.0 < *x* < 100.0
- *n* is a 32-bit signed integer, within the range [−231, 231 − 1]

#### 解析

二分法，$x^n = x^{n/2} \times x^{n/2} \times x^{n\%2}$

#### 代码

```cpp
class Solution {
public:
    double myPow(double x, int n) {
        if(n<0) return (1.0)/power(x,-n);
        return power(x,n);
    }
    double power(double x,int n)
    {
        if(n==0) return 1;
        double v=power(x,n/2);
        if(n%2==0) return v*v;
        else return v*v*x;
    }
};
```

### 69.Sqrt(x)

Implement `int sqrt(int x)`.

Compute and return the square root of *x*, where *x* is guaranteed to be a non-negative integer.

Since the return type is an integer, the decimal digits are truncated and only the integer part of the result is returned.

**Example 1:**

```
Input: 4
Output: 2

```

**Example 2:**

```
Input: 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since 
             the decimal part is truncated, 2 is returned.
```

#### 解析

二分法。

#### 代码

```cpp
class Solution {
public:
    int mySqrt(int x) {
        if(x==0) return 0;
        if(x==1||x==2)return 1;
        int high=x/2;
        int low=1;
        int last=-1;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(x/mid<mid){
                high=mid-1;
            }
            else if(x/mid>mid){
                low=mid+1;
                last=mid;
            }
            else
                return mid;
        }
        return last;
    }
};
```

## 动态规划

### 53.Maximum Subarray

Given an integer array `nums`, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

**Example:**

```
Input: [-2,1,-3,4,-1,2,1,-5,4],
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
```

#### 解析

动态规划思想，用一个变量sum存储和，如果sum值小于等于0，则sum置0，重新开始求和。

#### 代码

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int m=nums[0];
        int sum=0;
        for(int i=0;i<nums.size();i++){
            sum+=nums[i];
            m=max(m,sum);
            if(sum<0)
                sum=0;
        }
        return m;
    }
};
```



