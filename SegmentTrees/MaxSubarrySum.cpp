#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - "Find the contiguous subsegment with the maximum sum in range [L, R]"
   - Handles negative numbers correctly.
   
   LOGIC:
   Each node stores:
   1. sum: Total sum of the range.
   2. pref: Max prefix sum of the range.
   3. suff: Max suffix sum of the range.
   4. ans: Max subarray sum completely inside the range.
   
   When merging Left (L) and Right (R):
   - New Sum = L.sum + R.sum
   - New Pref = max(L.pref, L.sum + R.pref)
   - New Suff = max(R.suff, R.sum + L.suff)
   - New Ans  = max(L.ans, R.ans, L.suff + R.pref)
*/

typedef long long ll;
const ll INF = 1e18;

struct Node {
    ll sum, pref, suff, ans;
    
    // Default constructor (identity)
    Node() { sum = 0; pref = -INF; suff = -INF; ans = -INF; }
    
    // Constructor for single value
    Node(ll val) {
        sum = val;
        pref = suff = ans = max(-INF, val); // If empty subarrays allowed, use max(0LL, val)
    }
};

Node combine(Node l, Node r) {
    Node res;
    res.sum = l.sum + r.sum;
    res.pref = max(l.pref, l.sum + r.pref);
    res.suff = max(r.suff, r.sum + l.suff);
    res.ans = max({l.ans, r.ans, l.suff + r.pref});
    return res;
}

const int MAXN = 200005;
Node tree[4 * MAXN];
int arr[MAXN];

void build(int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = Node(arr[tl]);
    } else {
        int tm = (tl + tr) / 2;
        build(2 * v, tl, tm);
        build(2 * v + 1, tm + 1, tr);
        tree[v] = combine(tree[2 * v], tree[2 * v + 1]);
    }
}

void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        tree[v] = Node(new_val);
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) update(2 * v, tl, tm, pos, new_val);
        else update(2 * v + 1, tm + 1, tr, pos, new_val);
        tree[v] = combine(tree[2 * v], tree[2 * v + 1]);
    }
}

Node query(int v, int tl, int tr, int l, int r) {
    if (l > r) return Node(); // Should conceptually return "neutral" node
    if (l == tl && r == tr) return tree[v];
    
    int tm = (tl + tr) / 2;
    if (r <= tm) return query(2 * v, tl, tm, l, r);
    if (l > tm) return query(2 * v + 1, tm + 1, tr, l, r);
    
    return combine(query(2 * v, tl, tm, l, tm),
                   query(2 * v + 1, tm + 1, tr, tm + 1, r));
}

int main() {
    int n = 5;
    // Array: {1, -2, 3, 4, -5}
    arr[0]=1; arr[1]=-2; arr[2]=3; arr[3]=4; arr[4]=-5;
    
    build(1, 0, n-1);
    
    // Query range 0 to 4: Max sub is {3, 4} = 7
    cout << query(1, 0, n-1, 0, 4).ans << endl;
    
    // Query range 0 to 1: Max sub is {1} = 1
    cout << query(1, 0, n-1, 0, 1).ans << endl;
    
    return 0;
}