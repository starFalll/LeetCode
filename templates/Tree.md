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

## Segment Tree

All the following implementations are based on the update operations of finding "sum of intervals" and "addition and subtraction" of intervals. (区间和)

https://www.acwing.com/blog/content/24440/

https://leetcode.cn/problems/longest-increasing-subsequence-ii/solutions/1/by-lfool-f6vs/

```c++
struct Node {
    shared_ptr<Node> left, right;
    int val, add;
};

// Fixed interval range. 
void buildTree(shared_ptr<Node> node, int start, int end, vector<int>& arr) {
    // 到达叶子节点
    if (start == end) {
        node->val = arr[start];
        return ;
    }
    int mid = (start + end) >> 1;
    buildTree(node->left, start, mid);
    buildTree(node->right, mid + 1, end);
    // 向上更新
    pushUp(node);
}
// 向上更新
void pushUp(shared_ptr<Node> node) {
    node->val = node->left->val + node->right->val;
}

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
            cout<<cnt<<endl;
            ans = max(ans, cnt);
        }
        return ans;
    }
};
```

