#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Update: A[i] = min(A[i], val) for range [L, R]
   - Query: Range Sum
   - Complexity: O(log N) amortized (Jirawat's Trick)
   
   LOGIC:
   Nodes store: 
   - max1: Largest value
   - max2: Strictly second largest value
   - cnt: How many times max1 appears
   - sum: Range sum
   
   If val >= max1: No update needed (Break).
   If max2 < val < max1: Only max1 decreases. Math update.
   Else: Recurse down.
*/

typedef long long ll;
const int MAXN = 200005;

struct Node {
    ll sum;
    int max1, max2, cnt;
} tree[4 * MAXN];

void push_up(int v) {
    tree[v].sum = tree[2*v].sum + tree[2*v+1].sum;
    tree[v].max1 = max(tree[2*v].max1, tree[2*v+1].max1);
    
    if (tree[2*v].max1 == tree[2*v+1].max1) {
        tree[v].max2 = max(tree[2*v].max2, tree[2*v+1].max2);
        tree[v].cnt = tree[2*v].cnt + tree[2*v+1].cnt;
    } else if (tree[2*v].max1 > tree[2*v+1].max1) {
        tree[v].max2 = max(tree[2*v].max2, tree[2*v+1].max1);
        tree[v].cnt = tree[2*v].cnt;
    } else {
        tree[v].max2 = max(tree[2*v].max1, tree[2*v+1].max2);
        tree[v].cnt = tree[2*v+1].cnt;
    }
}

// Only supports updates that DECREASE values
void push_down(int v) {
    int bound = tree[v].max1;
    
    // If child's max > parent's max (which was reduced), clamp child
    if (tree[2*v].max1 > bound) {
        tree[2*v].sum -= (ll)tree[2*v].cnt * (tree[2*v].max1 - bound);
        tree[2*v].max1 = bound;
    }
    if (tree[2*v+1].max1 > bound) {
        tree[2*v+1].sum -= (ll)tree[2*v+1].cnt * (tree[2*v+1].max1 - bound);
        tree[2*v+1].max1 = bound;
    }
}

void build(int v, int tl, int tr, int* arr) {
    if (tl == tr) {
        tree[v] = { (ll)arr[tl], arr[tl], -1, 1 };
    } else {
        int tm = (tl + tr) / 2;
        build(2*v, tl, tm, arr);
        build(2*v+1, tm+1, tr, arr);
        push_up(v);
    }
}

void update_chmin(int v, int tl, int tr, int l, int r, int val) {
    if (l > r || val >= tree[v].max1) return; // Optimization 1
    
    if (l == tl && r == tr && val > tree[v].max2) { // Optimization 2 (Beats magic)
        tree[v].sum -= (ll)tree[v].cnt * (tree[v].max1 - val);
        tree[v].max1 = val;
        return;
    }
    
    push_down(v);
    int tm = (tl + tr) / 2;
    update_chmin(2*v, tl, tm, l, min(r, tm), val);
    update_chmin(2*v+1, tm+1, tr, max(l, tm+1), r, val);
    push_up(v);
}

ll query_sum(int v, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    if (l == tl && r == tr) return tree[v].sum;
    push_down(v);
    int tm = (tl + tr) / 2;
    return query_sum(2*v, tl, tm, l, min(r, tm)) + 
           query_sum(2*v+1, tm+1, tr, max(l, tm+1), r);
}

int main() {
    int arr[] = {10, 20, 30, 40, 50};
    build(1, 0, 4, arr);
    
    // Set min(val, 25) for range [0, 4]
    // Array becomes: {10, 20, 25, 25, 25}
    update_chmin(1, 0, 4, 0, 4, 25);
    
    // Sum: 105
    cout << query_sum(1, 0, 4, 0, 4) << endl;
    
    return 0;
}