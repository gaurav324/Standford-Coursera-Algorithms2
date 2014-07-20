/**
 * Fast minimum spanning tree using Prims Algorithm.
 * 
 * Prims algorithm as such is vey simple, we basically have to take one node randomly
 * and put it in a set called A and remaining nodes are in the set B. Then we select minimum
 * edge cost nodes that are passing between A and B and keep on moving vertices from B
 * to A one by one.
 *
 * Catch is when a node is moved from B to A, we have to track what new edges are there between
 * set A and B. A naive implementaton would be to iterate over all the nodes between set A and B
 * and find the minimum edge cost.
 *
 * This implementation maintains set B as a heap, where key is min length edge coming from 
 * set A. Any time a node is moved from set B to A, we update key of its adjacent vertices.
 * Therefore heap should be smart to re-heap itself properly.
 *
 * Author: Gaurav Nanda
 */

#include <iostream>
#include <vector>

#define MAX 30000

using namespace std;

class node {
public:
    int no;
    int key;
    vector<pair<int, int>> adjs;
    node(int n, int k) {
        this->no = n;
        this->key = k;
    }
};

class graph {
public:
    vector<node*> v;
};

class Heap {
public:
    vector<node*> v;
    vector<int> position;

    Heap(int nodes) {position.resize(nodes);}

    void update(int no, int key) {
        int i = position[no];
        node* temp = v[i];
        v[i] = v[v.size() - 1];
        position[v[i]->no] = i;
        v[v.size() - 1] = temp;
        position[v[v.size() - 1]->no] = v.size() - 1;
        v.pop_back();
    
        siftUp(i);
        heapify(i);
        temp->key = min(temp->key, key);
        insert(temp);
    }

    void insert(node* n) {
        v.push_back(n);
        position[v[v.size() - 1]->no] = v.size() - 1;
        int sz = v.size() - 1;
        siftUp(sz);
    }
    
    void siftUp(int sz) {
        while(sz > 0) {
            if (v[(sz - 1)/2]->key > v[sz]->key) {
                node* temp = v[sz];
                v[sz] = v[(sz - 1)/2];
                v[(sz - 1)/2] = temp;
                position[v[sz]->no] = sz;
                position[v[(sz - 1)/2]->no] = (sz - 1)/2;
                sz = (sz - 1) / 2;
            } else {
                break;
            }
        }
    }

    void heapify(int x) {
        while(x < v.size()) {
            int smallest = x;
            int left = 2 * (smallest + 1) - 1;
            int right = 2 * (smallest + 1);
    
            if (left < v.size() && v[left]->key < v[smallest]->key) {
                smallest = left;
            }
    
            if (right < v.size() && v[right]->key < v[smallest]->key) {
                smallest = right;
            }
    
            if (smallest != x) {
                node* temp1 = v[smallest];
                v[smallest] = v[x];
                position[v[smallest]->no] = smallest;
                v[x] = temp1;
                position[v[x]->no] = x;
            } else {
                break;
            }
    
            x = smallest;
        }
    }

    node* pop() {
        if (v.size() == 0) {
            return NULL;
        }
        if (v.size() == 1) {
            node* temp = v[0];
            v.pop_back();
            return temp;
        }
        node* temp = v[0];
        v[0] = v[v.size() - 1];
        position[v[0]->no] = 0;
        v.pop_back();

        heapify(0);
        return temp;
    }
};

int main() {
    int nodes, edges;
    cin >> nodes;
    cin >> edges;

    graph g;
    g.v.resize(nodes);

    Heap hp(nodes);

    for (int i = 0; i < edges; ++i) { 
        int n1, n2, cost; 
        cin >> n1; cin >> n2; cin >> cost; 
        n1 -= 1;
        n2 -= 1;
        
        if (g.v[n1] == NULL) {
            g.v[n1] = new node(n1, MAX);
            hp.insert(g.v[n1]);
        }
        if (g.v[n2] == NULL) {
            g.v[n2] = new node(n2, MAX);
            hp.insert(g.v[n2]);
        }
        g.v[n1]->adjs.push_back(pair<int, int>(n2, cost));
        g.v[n2]->adjs.push_back(pair<int, int>(n1, cost));
    }
    
   vector<node*> processed;
   processed.resize(nodes, NULL);
   int result = -1 * MAX;
   int done = 0;
   while(hp.v.size() > 0) {
        node* v = hp.pop();
        result += v->key;
        processed[v->no] = v;
        for (int i=0; i < v->adjs.size(); ++i) {
            if (processed[v->adjs[i].first] == NULL) {
                hp.update(v->adjs[i].first, v->adjs[i].second);
            }
        }
    }

    cout << "Cost of minimum spanning tree: " << result << endl;
}
