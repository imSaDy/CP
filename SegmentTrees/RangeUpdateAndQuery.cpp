#include <bits/stdc++.h>
using namespace std;

/* APPLICATION: 
   - Range Updates (e.g., Add V to all elements in range [L, R])
   - Range Queries (e.g., Sum of elements in range [L, R])
   - Complexity: O(log N) per operation.

   CAUTIONS:
   - This implementation is for RANGE SUM. 
   - If doing RANGE MIN/MAX: 
     1. Change `combine` to return min(a, b).
     2. In `push` and `update`, REMOVE the multiplication `* (tm - tl + 1)`. 
        (Adding 5 to a range increases the max by 5, not by 5 * length).
   - Identity Element: Return 0 for Sum, 1e18 for Min, -1e18 for Max in `query`.
*/

typedef long long ll;
const int MAXN = 200005; // Adjust based on problem constraints

struct SegTree {
    int n;
    vector<ll> tree, lazy;

    SegTree(int n) : n(n) {
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }

    // Logic to merge two child nodes (Sum, Max, Min, GCD, etc.)
    ll combine(ll a, ll b) {
        return a + b; 
    }

    // Pushes lazy values down to children
    void push(int v, int tl, int tr) {
        if (lazy[v] != 0) {
            int tm = (tl + tr) / 2;
            
            // Apply to left child
            tree[2 * v] += lazy[v] * (tm - tl + 1); // Remove *(len) for Min/Max
            lazy[2 * v] += lazy[v];
            
            // Apply to right child
            tree[2 * v + 1] += lazy[v] * (tr - tm); // Remove *(len) for Min/Max
            lazy[2 * v + 1] += lazy[v];
            
            // Reset current node
            lazy[v] = 0;
        }
    }

    // Range Update: Add val to [l, r]
    void update(int v, int tl, int tr, int l, int r, int val) {
        if (l > r) return;
        if (l == tl && r == tr) {
            tree[v] += (ll)val * (r - l + 1); // Remove *(len) for Min/Max
            lazy[v] += val;
        } else {
            push(v, tl, tr);
            int tm = (tl + tr) / 2;
            update(2 * v, tl, tm, l, min(r, tm), val);
            update(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, val);
            tree[v] = combine(tree[2 * v], tree[2 * v + 1]);
        }
    }

    // Range Query: Get Sum of [l, r]
    ll query(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0; // CHANGE THIS: Identity element (INF for Min, 0 for Sum)
        if (l == tl && r == tr) return tree[v];
        
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        return combine(query(2 * v, tl, tm, l, min(r, tm)),
                       query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r));
    }

    // Wrapper functions for 0-indexed usage
    void update(int l, int r, int val) { update(1, 0, n - 1, l, r, val); }
    ll query(int l, int r) { return query(1, 0, n - 1, l, r); }
};

int main() {
    int n = 10;
    SegTree st(n);
    
    st.update(0, 4, 10); // Add 10 to indices 0..4
    cout << st.query(0, 9) << endl; // Output 50
    st.update(2, 6, 5);  // Add 5 to indices 2..6
    cout << st.query(2, 4) << endl; // Check overlap
    return 0;
}