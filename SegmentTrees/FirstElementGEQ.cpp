#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - "Find the first index i in [L, R] where arr[i] >= X"
   - Complexity: O(log N) — Much faster than Binary Search + Query O(log^2 N)
   
   PREREQUISITE:
   - Tree stores MAX value of the range.
*/

const int INF = 1e9;
const int MAXN = 200005;
int tree[4 * MAXN];
int arr[MAXN];

void build(int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = arr[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(2 * v, tl, tm);
        build(2 * v + 1, tm + 1, tr);
        tree[v] = max(tree[2 * v], tree[2 * v + 1]);
    }
}

void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        tree[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) update(2 * v, tl, tm, pos, new_val);
        else update(2 * v + 1, tm + 1, tr, pos, new_val);
        tree[v] = max(tree[2 * v], tree[2 * v + 1]);
    }
}

// Returns the first index in [l, r] with value >= x. Returns -1 if none found.
int find_first(int v, int tl, int tr, int l, int r, int x) {
    // 1. If range is invalid or max value in this range is less than x, impossible.
    if (l > r || tree[v] < x) return -1;
    
    // 2. If leaf, we found it (since tree[v] >= x is checked above)
    if (tl == tr) return tl;
    
    int tm = (tl + tr) / 2;
    
    // 3. Try searching in the left intersection
    int res = find_first(2 * v, tl, tm, l, min(r, tm), x);
    
    // 4. If found in left, return it. Otherwise, search right.
    if (res != -1) return res;
    return find_first(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, x);
}

int main() {
    int n = 6;
    // Array: {1, 3, 2, 8, 4, 9}
    arr[0]=1; arr[1]=3; arr[2]=2; arr[3]=8; arr[4]=4; arr[5]=9;
    
    build(1, 0, n-1);
    
    // Find first element >= 5 in range [0, 5] -> should be index 3 (value 8)
    cout << find_first(1, 0, n-1, 0, 5, 5) << endl; 

    // Find first element >= 5 in range [0, 2] -> should be -1
    cout << find_first(1, 0, n-1, 0, 2, 5) << endl;
    
    return 0;
}