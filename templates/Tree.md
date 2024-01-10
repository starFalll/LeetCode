# Tree

Example: [493. Reverse Pairs](https://leetcode.com/problems/reverse-pairs/), can use both ways (BIT or Segment tree)

## Binary Indexed Tree

Single point modification, interval sum.

**must initialize to n+1, start from 1 (because of lowbit calculate)**.

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

## Segment Tree

1. Interval query
2. Interval modify
3. node modify

All the following implementations are based on the update operations of finding "sum of intervals" and "addition and subtraction" of intervals. (区间和)

https://www.acwing.com/blog/content/24440/

https://leetcode.cn/problems/longest-increasing-subsequence-ii/solutions/1/by-lfool-f6vs/

### Fixed array:

```c++
struct SegTree {
    vector<int> tree;
    vector<int> adds;
    SegTree(int n) {
        tree.resize(4*n, 0);
        adds.resize(4*n, 0);
    }
    void pushDown(int idx, int left_num, int right_num) {
        if (adds[idx] == 0) return;
        tree[idx*2+1] += adds[idx]*left_num;
        tree[idx*2+2] += adds[idx]*right_num;
      	
        adds[idx*2+1] += adds[idx];
        adds[idx*2+2] += adds[idx];
      /* Overwrite operation
        tree[idx*2+1] = adds[idx]*left_num;
        tree[idx*2+2] = adds[idx]*right_num;
        adds[idx*2+1] = adds[idx];
        adds[idx*2+2] = adds[idx];
        */
        adds[idx] = 0;
    }
    void update(int idx, int start, int end, int l, int r, int val) {
        if (l <= start && end <= r) {
            tree[idx] += (end - start + 1) * val; // interval sum
          	// tree[idx] = (end - start + 1) * val; Overwrite operation
            // adds[idx] = val;
            adds[idx] += val;
            return;
        }
        int mid = start + (end - start) / 2;
        pushDown(idx, mid - start + 1, end-mid);
        if (l <= mid) update(idx*2+1, start, mid, l, r, val);
        if (r > mid) update(idx*2+2, mid+1, end, l, r, val);
        tree[idx] = tree[idx*2+1] + tree[idx*2+2];
    }

    int query(int idx, int start, int end, int l, int r) {
        if (l <= start && end <= r) {
            return tree[idx];
        }
        int mid = start + (end - start) / 2;
        int res = 0;
        pushDown(idx, mid - start + 1, end-mid);
        if (l <= mid) res += query(idx*2+1, start, mid, l, r);
        if (r > mid) res += query(idx*2+2, mid+1, end, l, r);
        return res;
    }
};
```

### Dynamic version

```c++
struct Node {
    shared_ptr<Node> left, right;
    int val, add;
};

// dynamic creation.
class SegmentTreeDynamic {
    
    void pushUp(shared_ptr<Node> node) {
        node->val = node->left->val + node->right->val;
    }
    void pushDown(shared_ptr<Node> node, int leftNum, int rightNum) {
        if (node->left == nullptr) node->left = make_shared<Node>();
        if (node->right == nullptr) node->right = make_shared<Node>();
        if (node->add == 0) return;
        node->left->val += node->add * leftNum;
        node->right->val += node->add * rightNum;
        // 对区间进行「加减」的更新操作，下推懒惰标记时需要累加起来，不能直接覆盖
        // The update operation of "addition and subtraction" is performed on the interval. 
        // When pushing down the lazy mark, it needs to be accumulated and cannot be directly overwritten.
        node->left->add += node->add;
        node->right->add += node->add;
        node->add = 0;
    }
    void update(shared_ptr<Node> node, int start, int end, int l, int r, int val) {
        if (l <= start && end <= r) {
            node->val += (end - start + 1) * val;
            node->add += val;
            return ;
        }
        int mid = (start + end) >> 1;
        pushDown(node, mid - start + 1, end - mid);
        if (l <= mid) update(node->left, start, mid, l, r, val);
        if (r > mid) update(node->right, mid + 1, end, l, r, val);
        pushUp(node);
    }
    int query(shared_ptr<Node> node, int start, int end, int l, int r) {
        if (l <= start && end <= r) return node->val;
        int mid = (start + end) >> 1, ans = 0;
        pushDown(node, mid - start + 1, end - mid);
        if (l <= mid) ans += query(node->left, start, mid, l, r);
        if (r > mid) ans += query(node->right, mid + 1, end, l, r);
        return ans;
    }
    
};
```

[2407. Longest Increasing Subsequence II](https://leetcode.com/problems/longest-increasing-subsequence-ii/):

区间最值：

```c++
struct Node {
    shared_ptr<Node> left, right;
    int val = 0, add = 0; 
};
void pushUp(shared_ptr<Node> node) {
    node->val = max(node->left->val, node->right->val);
}
void pushDown(shared_ptr<Node> node) {
    if (!node->left) node->left = make_shared<Node>();
    if (!node->right) node->right = make_shared<Node>();
    if (node->add == 0) return;
    node->left->val = node->add;
    node->right->val = node->add;
    node->left->add = node->add;
    node->right->add = node->add;
    node->add = 0;
}

void update(shared_ptr<Node> node, int start, int end, int l, int r, int val) {
    if (l <= start && end <= r) {
        node->val = val;
        node->add = val;
        return;
    }
    int mid = (start + end) >> 1;
    pushDown(node);
    if (l <= mid) update(node->left, start, mid, l, r, val);
    if (r > mid) update(node->right, mid+1, end, l, r, val);
    pushUp(node);
}

int query(shared_ptr<Node> node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return node->val;
    }
    int mid = (start+end)>>1;
    pushDown(node);
    int ans = 0;
    if (l <= mid) ans = query(node->left, start, mid, l, r);
    if (r > mid) ans = max(ans, query(node->right, mid+1, end, l, r));
    return ans;
}
class Solution {
public:
    int lengthOfLIS(vector<int>& nums, int k) {
        auto node = make_shared<Node>();
        int N = *max_element(nums.begin(), nums.end());
        int ans = 1;
        for (int i = 0; i < nums.size(); i++) {
            int cnt = query(node, 0, N, max(0, nums[i]-k), nums[i]-1) + 1;
            update(node, 0, N, nums[i], nums[i], cnt);
            ans = max(ans, cnt);
        }
        return ans;
    }
};
```

