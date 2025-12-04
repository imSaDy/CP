#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Query: "Count numbers < K in range [L, R]"
   - Complexity: O(log N) per query (Standard Merge Sort Tree is O(log^2 N))
   - Space: O(N log N)
   
   LOGIC:
   - Standard Merge Sort Tree stores sorted vectors.
   - We add two lookup tables (toLeft, toRight) for every element.
   - toLeft[i] = index of the first element in Left Child >= sorted[i].
   - This allows us to carry the position `k` down the tree in O(1).
*/

const int MAXN = 100005; 
// Caution: This uses 3 vectors per node. Memory usage is roughly 12 * N * log N bytes.
// For N=10^5, this is ~20-30MB. For N=2*10^5, it might be tight on 64MB limits.

struct Node {
    vector<int> sorted;
    vector<int> toLeft, toRight;
} tree[4 * MAXN];

int arr[MAXN];

void build(int v, int tl, int tr) {
    if (tl == tr) {
        tree[v].sorted = {arr[tl]};
        tree[v].toLeft = {0, 0};  // Base case: Pointers don't matter, but need size
        tree[v].toRight = {0, 0};
    } else {
        int tm = (tl + tr) / 2;
        build(2 * v, tl, tm);
        build(2 * v + 1, tm + 1, tr);
        
        // Merge Step with Pointer Calculation
        auto &leftVec = tree[2 * v].sorted;
        auto &rightVec = tree[2 * v + 1].sorted;
        auto &myVec = tree[v].sorted;
        auto &L = tree[v].toLeft;
        auto &R = tree[v].toRight;
        
        int i = 0, j = 0;
        int n_left = leftVec.size();
        int n_right = rightVec.size();
        
        // Standard merge + keeping track of positions
        while (i < n_left || j < n_right) {
            if (j == n_right || (i < n_left && leftVec[i] < rightVec[j])) {
                myVec.push_back(leftVec[i]);
                // If I pick from Left, the "next element in Left" is i+1
                // The "next element in Right" is still j
                L.push_back(i + 1);
                R.push_back(j);
                i++;
            } else {
                myVec.push_back(rightVec[j]);
                // If I pick from Right, Left stays at i, Right becomes j+1
                L.push_back(i);
                R.push_back(j + 1);
                j++;
            }
        }
        
        // Add terminal pointers for when search goes out of bounds (idx == size)
        L.push_back(n_left);
        R.push_back(n_right);
    }
}

// k_idx: The index of K in the current node's sorted vector (pre-calculated)
int query(int v, int tl, int tr, int l, int r, int k_idx) {
    if (l > r) return 0;
    
    if (l == tl && r == tr) {
        // Since we carried k_idx down, it represents:
        // "How many elements in this node are < K"
        return k_idx;
    }
    
    int tm = (tl + tr) / 2;
    
    // O(1) descent using lookups
    int k_idx_left = tree[v].toLeft[k_idx];
    int k_idx_right = tree[v].toRight[k_idx];
    
    return query(2 * v, tl, tm, l, min(r, tm), k_idx_left) +
           query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, k_idx_right);
}

int main() {
    int n = 6;
    int a[] = {2, 5, 1, 8, 4, 9};
    for(int i=0; i<n; i++) arr[i] = a[i];
    
    build(1, 0, n-1);
    
    // We want to find count of numbers < 5 in range [0, 5].
    int K = 5;
    
    // 1. Initial Binary Search at Root (Only once!)
    int initial_k_idx = lower_bound(tree[1].sorted.begin(), tree[1].sorted.end(), K) 
                        - tree[1].sorted.begin();
                        
    // 2. Fast Query
    cout << query(1, 0, n-1, 0, 5, initial_k_idx) << endl; // Ans: 3 (2, 1, 4)
    
    return 0;
}