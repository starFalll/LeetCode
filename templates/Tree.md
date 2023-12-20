# Tree

## Binary Indexed Tree

Time Complexity: all O(logn)

```c++
// must initialize to n+1, start from 1 (because of lowbit calculate)
class BIT {
    vector<int> tree;
public:
    BIT(int n) : tree(n) {}
    // Find the value consisting of the lowest bit 1 and the following 0
		int lowbit(int x) {
        return x & -x;
    }
    // add c at index i
    void add(int x, int c) {
       for(int i = x; i < tree.size(); i += lowbit(i)) tree[i] += c;
    }

    // return the sum of [1, x]
    int sum(int x) {
        int res = 0;
        for(int i = x; i > 0; i -= lowbit(i)) res += tree[i];
        return res;
    }

    // return the sum of [left, right]
    int query(int left, int right) {
        return sum(right) - sum(left - 1);
    }
};
```

[2659. Make Array Empty](https://leetcode.com/problems/make-array-empty/)
