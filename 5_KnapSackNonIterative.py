"""
This problem also asks you to solve a knapsack instance, but a much bigger one.
Download the text file here. This file describes a knapsack instance, and it has the following format:
[knapsack_size][number_of_items]
[value_1] [weight_1]
[value_2] [weight_2]
...
For example, the third line of the file is "50074 834558", indicating that the second item has value 50074 and size 834558, respectively. As before, you should assume that item weights and the knapsack capacity are integers.

This instance is so big that the straightforward iterative implemetation uses an infeasible amount of time and space. So you will have to be creative to compute an optimal solution. One idea is to go back to a recursive implementation, solving subproblems --- and, of course, caching the results to avoid redundant work --- only on an "as needed" basis. Also, be sure to think about appropriate data structures for storing and looking up solutions to subproblems.

"""

import sys

f = open(sys.argv[1])
lines = f.readlines()
f.close()

W, N = map(lambda x: int(x), lines[0].split(" "))
w = [10000000]
v = [10000000]
for line in lines[1:]:
    v.append(int(line.split(" ")[0]))
    w.append(int(line.split(" ")[1]))

K = {}
sys.setrecursionlimit(2100)
def knapsack(W, N):
    global K
    if N == 0: return 0
    if (W,N) in K:
        return K[(W, N)]
    one = knapsack(W, N - 1)
    two = knapsack(W - w[N], N - 1) + v[N] if (w[N] <= W) else -1
    K[(W,N)] = max(one, two)
    return K[(W,N)]

print knapsack(W, N)
