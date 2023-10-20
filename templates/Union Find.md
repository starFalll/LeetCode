## Union Find

[1319. Number of Operations to Make Network Connected](https://leetcode.com/problems/number-of-operations-to-make-network-connected/)

### C++

```c++
#include <vector>

using namespace std;

struct UnionFind
{
private:
    int c = 0;
    vector<int> parent;
public:
    UnionFind(int n) {
        c = n;
        parent.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    int find(int x) {
        while (x != parent[x]) {
            //Generational compression
            // The performance is relatively high, although the compression is not complete
            parent[x] = parent[parent[x]];
            // Complete compression
            // Consume more performance, but query performance is higher
            // parent[x] = find(parent[x]);
            x = parent[x];
        }
        return x;
    }

    void do_union(int x, int y) {
        int rootx = find(x);
        int rooty = find(y);
        if (rooty == rootx) return;
        parent[rootx] = rooty;
        count--;
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
    int count() {
        return c;
    }
};

```

### Python

```python
class UnionFind:
    def __init__(self):
        """
        record the parent node of each node
        """
        self.father = {}
    
    def find(self,x):
        """
        find root 
        path compression
        """
        root = x

        while self.father[root] != None:
            root = self.father[root]

        # path compression
        while x != root:
            original_father = self.father[x]
            self.father[x] = root
            x = original_father
         
        return root
    
    def merge(self,x,y,val):
        """
        merge two nodes
        """
        root_x,root_y = self.find(x),self.find(y)
        
        if root_x != root_y:
            self.father[root_x] = root_y

    def is_connected(self,x,y):
        """
        determine if two nodes are connected
        """
        return self.find(x) == self.find(y)
    
    def add(self,x):
        """
        add new node
        """
        if x not in self.father:
            self.father[x] = None


```



