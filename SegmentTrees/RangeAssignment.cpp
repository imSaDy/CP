#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - "Set all elements in range [L, R] to V"
   - Query: Sum (can be adapted for Min/Max)
   - CRITICAL: Use a boolean flag for lazy because 0 is a valid value!
*/

typedef long long ll;
const int MAXN = 200005;

struct SegTree {
    int n;
    vector<ll> tree;
    vector<ll> lazy;
    vector<bool> has_lazy; // Critical: distinguishes "Set to 0" from "No Update"

    SegTree(int n) : n(n) {
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
        has_lazy.resize(4 * n, false);
    }

    void push(int v, int tl, int tr) {
        if (has_lazy[v]) {
            int tm = (tl + tr) / 2;
            
            // Apply to Left
            tree[2*v] = lazy[v] * (tm - tl + 1);
            lazy[2*v] = lazy[v];
            has_lazy[2*v] = true;
            
            // Apply to Right
            tree[2*v+1] = lazy[v] * (tr - tm);
            lazy[2*v+1] = lazy[v];
            has_lazy[2*v+1] = true;
            
            // Reset
            has_lazy[v] = false;
        }
    }

    void update(int v, int tl, int tr, int l, int r, int new_val) {
        if (l > r) return;
        if (l == tl && r == tr) {
            tree[v] = (ll)new_val * (r - l + 1);
            lazy[v] = new_val;
            has_lazy[v] = true;
        } else {
            push(v, tl, tr);
            int tm = (tl + tr) / 2;
            update(2*v, tl, tm, l, min(r, tm), new_val);
            update(2*v+1, tm+1, tr, max(l, tm+1), r, new_val);
            tree[v] = tree[2*v] + tree[2*v+1];
        }
    }

    ll query(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (l == tl && r == tr) return tree[v];
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        return query(2*v, tl, tm, l, min(r, tm)) +
               query(2*v+1, tm+1, tr, max(l, tm+1), r);
    }
};

int main() {
    SegTree st(10);
    // Set 0..4 to 5 -> Sum = 25
    st.update(1, 0, 9, 0, 4, 5);
    cout << st.query(1, 0, 9, 0, 9) << endl;
    
    // Set 2..6 to 0 -> This overwrites previous values!
    st.update(1, 0, 9, 2, 6, 0);
    cout << st.query(1, 0, 9, 0, 9) << endl; // Should be 10 (indices 0,1 are 5, others 0)
    
    return 0;
}