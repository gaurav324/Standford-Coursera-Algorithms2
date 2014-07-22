"""
In this programming problem and the next you'll code up the clustering algorithm from lecture for computing a max-spacing k-clustering. 
Download the text file here. This file describes a distance function (equivalently, a complete graph with edge costs). 
It has the following format:
    [number_of_nodes]
    [edge 1 node 1] [edge 1 node 2] [edge 1 cost]
    [edge 2 node 1] [edge 2 node 2] [edge 2 cost]
    ...
 
There is one edge (i,j) for each choice of 1.i<j.n, where n is the number of nodes.
For example, the third line of the file is "1 3 5250", indicating that the distance between 
nodes 1 and 3 (equivalently, the cost of the edge (1,3)) is 5250. You can assume that distances are positive, 
but you should NOT assume that they are distinct.
 
Your task in this problem is to run the clustering algorithm from lecture on this data set, where the target number k of clusters is set to 4.
What is the maximum spacing of a 4-clustering?
 
ADVICE: If you're not getting the correct answer, try debugging your algorithm using some small test cases. 
And then post them to the discussion forum!
 
"""
import sys
 
class UnionFind(object):
    def __init__(self, n):
        self.tree = [0] * n
        self.tree_len = [1] * n
        for i in range(n):
            self.tree[i] = i
 
    def union(self, n1, n2):
        np1 = self.parent(n1)
        np2 = self.parent(n2)
    
        # This one is just to expedite the find, by reducing
        # the length of the tree. Makes it very fast.
        if (self.tree_len[np1] < self.tree_len[np2]):
            self.tree[np1] = np2
            self.tree_len[np2] += self.tree_len[np1]
        else:
            self.tree[np2] = np1
            self.tree_len[np1] += self.tree_len[np2]
    
    def parent(self, n1):
        dad = self.tree[n1]
        if(dad != n1):
            n1 = self.parent(dad)
        return n1
 
def main():
    f = open(sys.argv[1])
    lines = f.readlines()
    f.close()
 
    uf = UnionFind(int(lines[0]))
    edges = []
    for line in lines[1:]:
        line = map(lambda x: int(x), line.strip().split(" "))
        edges.append(line[-1:] + [line[0] - 1, line[1] - 1])
   
    # Sort in increasing order.
    edges = sorted(edges)
 
    n = int(lines[0])
    clusters = n
    # Implement Kruskal's MST to find Max-Space clustering for K=4.
    for i in range(len(edges)):
        cost, n1, n2 = edges[i]
        op1 = uf.parent(n1)
        op2 = uf.parent(n2)
        uf.union(n1, n2)
        np1 = uf.parent(n1)
        np2 = uf.parent(n2)
        # If nodes have switched their parent, means 
        # cluster count has dropped by 1.
        #
        # What is spacing?
        # It is the min distance between any two clusters.
        if op1 != np1 or op2 != np2:
            clusters -= 1
            if clusters == 4:
                ans = 999999
                i += 1
                while(i < len(edges)):
                    cost, n1, n2 = edges[i]
                    if uf.parent(n1) != uf.parent(n2):
                        if cost < ans:
                            ans = cost
                    i += 1
                print "Spacing: ", ans
                break
main()
