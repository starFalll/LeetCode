// refer to this link https://leetcode.cn/problems/number-of-provinces/solution/python-duo-tu-xiang-jie-bing-cha-ji-by-m-vjdr/
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

