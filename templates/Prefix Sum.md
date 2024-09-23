# Prefix Sum

Fox example, we want to get sum equal to K, `nums[i,...j] = nums[0...j] - nums[0...i] = k`, if `nums[0...j]-k`exists, then `nums[0...i]`exists, so there is `nums[i,...j]` matching the requirements.

So we just need to prove if `nums[0...i]-k`exists, which can using prefix sum.

[560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/)

`nums[i,...j] = nums[0...i] - nums[0...j] = k`

-> 所以如果`nums[0...i]-k`有结果，则说明`nums[i....j]==k`存在，用prefix sum处理，用hashmap存储前缀和。

先加res是为了解决k=0的情况，由于先加res，由于存在`sum==k`的情况，所以初始化需要插入`{0, 1}`

```c++
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        m.insert({0, 1});
        int sum = 0, res = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            res += m[sum - k];
            m[sum]++;
        }
        return res;
    }
};
```

2D Prefix Sum:

[1074. Number of Submatrices That Sum to Target](https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/)

```c++
// 2D array prefix sum
class Solution {
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        // sum, num
        unordered_map<int, int> prefix;
    
        int n = matrix.size(), m = matrix[0].size();
        int res = 0;
        for (int row = 0; row < n; row++) {
            vector<vector<int>> records(n, vector<int>(m, 0));
            for (int i = row; i < n; i++) {
                prefix.clear();
                prefix.insert({0, 1});
                int sum = 0;
                for (int j = 0; j < m; j++) {
                    sum += matrix[i][j] + (i > row ? records[i-1][j] : 0);
                    res += prefix[sum-target];
                    prefix[sum]++;
                    records[i][j] = (i > row ? records[i-1][j] : 0) + matrix[i][j];
                }   
            }
        }
        return res;
        
    }
};
```

## Bit Manipulation

When the status number is limited (5 corresponds to 0~31, 6->0~63, etc), we can use bit to store the status.

[1371. Find the Longest Substring Containing Vowels in Even Counts](https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/)