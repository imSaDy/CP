#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Dynamic Convex Hull Trick (Lines not sorted by slope).
   - Query: Min value at x for set of lines y = mx + c.
   - Range: X coordinates usually [-1e9, 1e9], so we use Dynamic or implicit approach.
     (This implementation assumes X is 0 to 1e6 for simplicity).
*/

typedef long long ll;
const ll INF = 2e18; // Bigger than any possible coordinate

struct Line {
    ll m, c;
    ll eval(ll x) { return m * x + c; }
};

const int MAX_COORD = 1000005; // Adjust based on problem X range
Line tree[4 * MAX_COORD];

void init() {
    for(int i=0; i<4*MAX_COORD; i++) tree[i] = {0, INF};
}

// Add a new line y = mx + c
void add_line(int v, int l, int r, Line new_line) {
    int mid = (l + r) / 2;
    bool left_better = new_line.eval(l) < tree[v].eval(l);
    bool mid_better = new_line.eval(mid) < tree[v].eval(mid);

    if (mid_better) {
        swap(tree[v], new_line); // The new line becomes the current best for mid
    }
    
    if (l == r) return;
    
    if (left_better != mid_better) {
        add_line(2 * v, l, mid, new_line);
    } else {
        add_line(2 * v + 1, mid + 1, r, new_line);
    }
}

ll query(int v, int l, int r, int x) {
    if (l == r) return tree[v].eval(x);
    
    int mid = (l + r) / 2;
    if (x <= mid)
        return min(tree[v].eval(x), query(2 * v, l, mid, x));
    else
        return min(tree[v].eval(x), query(2 * v + 1, mid + 1, r, x));
}

int main() {
    init();
    
    // Add lines
    add_line(1, 0, MAX_COORD, {2, 5});  // y = 2x + 5
    add_line(1, 0, MAX_COORD, {-1, 10}); // y = -x + 10
    
    // Query at x = 2
    // Line 1: 2(2) + 5 = 9
    // Line 2: -1(2) + 10 = 8
    // Result: 8
    cout << query(1, 0, MAX_COORD, 2) << endl;
    
    return 0;
}