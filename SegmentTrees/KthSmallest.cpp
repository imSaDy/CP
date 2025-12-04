#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Find K-th smallest number in a subarray [L, R].
   - Query previous versions of the array.
   
   HOW TO USE:
   1. Coordinate Compress your data if values are large (> 2*10^5).
   2. Build an initial empty tree.
   3. For every element `x` in input array, create a NEW version of the tree 
      that adds `x` to the previous version.
   4. Roots[i] stores the segment tree containing elements arr[0]...arr[i].
*/

const int MAXN = 200005;
const int MAX_NODES = MAXN * 25; // N log N space

struct Node {
    int count;
    int left, right;
} tree[MAX_NODES];

int roots[MAXN]; // Stores root index for each version/prefix
int node_cnt = 0;

int build(int tl, int tr) {
    int node = ++node_cnt;
    tree[node].count = 0;
    if (tl != tr) {
        int tm = (tl + tr) / 2;
        tree[node].left = build(tl, tm);
        tree[node].right = build(tm + 1, tr);
    }
    return node;
}

// Returns index of the new node created
int update(int prev_node, int tl, int tr, int val) {
    int node = ++node_cnt;
    tree[node] = tree[prev_node]; // Copy previous node
    tree[node].count++;
    
    if (tl == tr) return node;
    
    int tm = (tl + tr) / 2;
    if (val <= tm)
        tree[node].left = update(tree[prev_node].left, tl, tm, val);
    else
        tree[node].right = update(tree[prev_node].right, tm + 1, tr, val);
        
    return node;
}

// Find K-th smallest using two roots (Prefix R - Prefix L-1)
int query(int node_u, int node_v, int tl, int tr, int k) {
    if (tl == tr) return tl;
    
    int tm = (tl + tr) / 2;
    // How many numbers are in the left subtree added between version u and v?
    int left_count = tree[tree[node_v].left].count - tree[tree[node_u].left].count;
    
    if (k <= left_count)
        return query(tree[node_u].left, tree[node_v].left, tl, tm, k);
    else
        return query(tree[node_u].right, tree[node_v].right, tm + 1, tr, k - left_count);
}

int main() {
    // Example: Array {2, 5, 1, 8, 2}
    // Value range 1 to 10 (if larger, use coordinate compression)
    int n = 5;
    int arr[] = {0, 2, 5, 1, 8, 2}; // 1-based for convenience
    
    roots[0] = build(1, 10);
    
    for(int i = 1; i <= n; i++) {
        roots[i] = update(roots[i-1], 1, 10, arr[i]);
    }
    
    // Query: 2nd smallest number in range [2, 4] (Elements: 5, 1, 8 -> Sorted: 1, 5, 8)
    // Answer should be 5
    int L = 2, R = 4, K = 2;
    cout << query(roots[L-1], roots[R], 1, 10, K) << endl;
    
    return 0;
}