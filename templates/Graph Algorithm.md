# Graph Algorithm

## Prime

[1584. Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/):

```cpp
class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<bool> visited(n);
        int ans = 0, index = 0;
        int cnt = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> q;
        while (++cnt < n) {
            visited[index] = true;
            for (int i = 0; i < n; i++) {
                q.push({(abs(points[i][0] - points[index][0])
                 + abs(points[i][1] - points[index][1])), i});
            }
            while (visited[q.top().second]) q.pop();
            ans += q.top().first;
            index = q.top().second;
            q.pop();
        }
        return ans;
    }
};
```

## BFS

If a question is about how to find sortest path, we can always use BFS to solve this problem.

Note: Using BFS, we need record the shortest path among all the possible. But recording visited matrix of all the path is cost of space. One of the common way is just record the shortest path at the (row, col). For Example, [505. The Maze II](https://leetcode.com/problems/the-maze-ii/)

