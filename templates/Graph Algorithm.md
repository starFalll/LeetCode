# Graph Algorithm

https://www.acwing.com/blog/content/27/

1. **Dijkstra’s algorithm finds the shortest path, but Prim’s algorithm finds the MST(Minimum Spanning Tree)**.
2. Dijkstra’s algorithm can work on both directed and undirected graphs, but Prim’s algorithm only works on undirected graphs
3. Prim’s algorithm can handle negative edge weights, but Dijkstra’s algorithm may fail to accurately compute distances if at least one negative edge weight exists

![dijkstra](https://www.baeldung.com/wp-content/uploads/sites/4/2020/01/dijkstra.jpg)



![prim](https://www.baeldung.com/wp-content/uploads/sites/4/2020/01/prim.jpg)

### Dijkstra

Dijkstra’s algorithm may fail to accurately compute distances if at least one negative edge weight exists.

Version 1: Get all shortest paths from start.

```c++

struct State {
    // id of graph node
    int id;
    // The distance from the start node to the current node
    int distFromStart;

    State(int id, int distFromStart) {
        this->id = id;
        this->distFromStart = distFromStart;
    }
};

// smallest element on top
struct Comparator {
  bool operator()(const State& a, const State& b) {
    return a.distFromStart > b.distFromStart
  }
};

// Returns the weight of the edge between node from and node to
int weight(int from, int to);

// Input node s returns the adjacent nodes of s
vector<int> adj(int s);

// Enter a picture and a starting point start, and calculate the shortest distances from start to other nodes.
vector<int> dijkstra(int start, vector<int> graph[]) {
    // The number of nodes in the graph
    int V = graph.size();
    // Record the weight of the shortest path, you can understand it as dp table
    // Definition: The value of distTo[i] is the weight of the shortest path from node start to node i
    int distTo[V];
    // Find the minimum value, so dp table is initialized to positive infinity
    memset(distTo, INT_MAX, sizeof(distTo));
    // base case, the shortest distance from start to start is 0
    distTo[start] = 0;

    // Priority queue, the one with smaller distFromStart comes first
    priority_queue<State, vector<State>, Comparator> pq();

    // Start BFS from the starting point start
    pq.push(State(start, 0));

    while (!pq.empty()) {
        State curState = pq.top();
        pq.pop();
        int curNodeID = curState.id;
        int curDistFromStart = curState.distFromStart;

        if (curDistFromStart > distTo[curNodeID]) {
            // There is already a shorter path to the curNode node
            continue;
        }
        // Enqueue adjacent nodes of curNode
        for (int nextNodeID: adj(curNodeID)) {
            //See if the distance from curNode to nextNode will be shorter
            int distToNextNode = distTo[curNodeID] + weight(curNodeID, nextNodeID);
            if (distTo[nextNodeID] > distToNextNode) {
                // Update dp table
                distTo[nextNodeID] = distToNextNode;
                // Put this node and distance into the queue
                pq.push(State(nextNodeID, distToNextNode));
            }
        }
    }
    vector<int> result;
    for (int i = 0; i < V; i++) {
        result.push_back(distTo[i]);
    }
    return result;
}
```

Version 2: Get one shortest path from start to end.

```c++
// Enter the starting point start and end point end, and calculate the shortest distance from the starting point to the end point.
int dijkstra(int start, int end, vector<int>* graph) {

    // ...

    while (!pq.empty()) {
        State curState = pq.top();
        pq.pop();
        int curNodeID = curState.id;
        int curDistFromStart = curState.distFromStart;

        // Just add a judgment here, no need to change other codes.
        if (curNodeID == end) {
            return curDistFromStart;
        }

        if (curDistFromStart > distTo[curNodeID]) {
            continue;
        }

        // ...
    }

    // If you run to this point, it means that you cannot go from start to end.
    return INT_MAX;
}

```

### Prime

template:

适用于稠密图，时间复杂度 O(n2)

核心思想：每次挑一条与当前集合相连的最短边。

```c++
// st[i] 表示点i是否在当前生成树集合中
// dist[i] 表示点i到当前集合的最短边的长度
// g[i][j] 表示点i和点j之间边的长度
// 返回值：最小生成树中所有边的总长度
int Prim()
{
    int res = 0;
    for (int i = 1; i <= n; i ++ )
    {
        dist[i] = INF;
        st[i] = false;
    }
    dist[1] = 0;
    for (int i = 1; i <= n; i ++ )
    {
        int id = -1, min_dist = INF;
        // 寻找最短边
        for (int j = 1; j <= n; j ++ )
            if (!st[j] && dist[j] < min_dist)
            {
                id = j;
                min_dist = dist[j];
            }
        st[id] = true;
        res += dist[id];
        // 用新加入的点更新其余点到生成树的最短边
        for (int j = 1; j <= n; j ++ )
            if (!st[j])
                dist[j] = min(dist[j], g[id][j]);
    }
    return res;
}
```



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

### Bellman-Ford

The Bellman-Ford algorithm is an algorithm for dealing with the shortest path problem of units with negative weight edges. Solve the problem of **negative weight edges** that cannot be found by Dijkstra. 

**When changing path to opposite number, it can be used to deal with longest path problem**

[787. Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/)	

```c++
int dist[N],backup[N];//dist距离，backup用来存上一次的结果。
struct edge//用来存边
{
    int a;
    int b;
    int w;
}Edge[M];
int Bellman_Ford()
{
    memset(dist, 0x3f, sizeof dist);
    dist[1] = 0;//初始化
    for(int i = 0 ; i < k ; i++)//遍历k次
    {
        memcpy(backup,dist,sizeof dist);//存上一次答案。
        for(int j = 0 ; j < m ; j++)
        {
            int a = Edge[j].a, b = Edge[j].b, w = Edge[j].w;
            dist[b] = min(dist[b],backup[a] + w);
        }//遍历所有边
    }
    if(dist[n] > 0x3f3f3f3f/2) return -1;
    /*这里不像Dijkstra写等于正无穷是因为可能有负权边甚至是负环的存在，
    使得“正无穷”在迭代过程中受到一点影响。*/
    return dist[n];
}
```



## BFS

If a question is about how to find sortest path, we can always use BFS to solve this problem.

Note: Using BFS, we need record the shortest path among all the possible. But recording visited matrix of all the path is cost of space. One of the common way is just record the shortest path at the (row, col). For Example, [505. The Maze II](https://leetcode.com/problems/the-maze-ii/)

If can or cannot arrive at one place defined by mutiply factors, for two factors (path len  + other), we can add a new matrix to record the other factor, only if it can update or equal to current min/max val in the position of the matrix, then can continue. Moreover, we use queue to store vector(row, col, pathlen, other).  [1293. Shortest Path in a Grid with Obstacles Elimination](https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/)

If there are many status in one position, only different status can revisit position, we can use a 3D vector to store. The third dimension is the list of different status (maybe as bit vector) [864. Shortest Path to Get All Keys](https://leetcode.com/problems/shortest-path-to-get-all-keys/)

BFS/DFS, when there are many status, we just need to add dimensions to memory them.

## DFS

DFS Iterator version: similar with BFS, but using `Stack` rather than `Queue`

DFS+memory: One way ro reduce time complexity from exponential level to linear of grid is using memory.

[1463. Cherry Pickup II](https://leetcode.com/problems/cherry-pickup-ii/) (three dimensions)

[329. Longest Increasing Path in a Matrix](https://leetcode.com/problems/longest-increasing-path-in-a-matrix/): (two dimensions)

```c++
class Solution {
private:
    vector<int> nx = {0, 1, 0, -1, 0};
    int DFS(vector<vector<int>>& matrix, int row, int col, vector<vector<int>>& dp) {
        if (dp[row][col] > 0) return dp[row][col];
        int len = 1;
        for (int i = 0; i < 4; i++) {
            int n_i = row + nx[i];
            int n_j = col + nx[i+1];
            if (n_i >= 0 && n_i < matrix.size() && n_j >=0 
                && n_j < matrix[0].size() && matrix[n_i][n_j] > matrix[row][col]) {
                    len = max(len, DFS(matrix, n_i, n_j, dp)+1);
                }
        }
        dp[row][col] = len;
        return len;
    }

public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));
        int res = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res = max(res, DFS(matrix, i, j, dp));
            }
        }
        return res;
    }
};
```

