#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Range GCD Queries.
   - Point Updates (A[i] = x).
   - Complexity: O(log N * log(MaxVal)).
   - Note: GCD converges very fast, so this is efficient.
*/

typedef long long ll;

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

const int MAXN = 200005;
ll tree[4 * MAXN];
ll arr[MAXN];
int n;

void build(int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = arr[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(2 * v, tl, tm);
        build(2 * v + 1, tm + 1, tr);
        tree[v] = gcd(tree[2 * v], tree[2 * v + 1]);
    }
}

void update(int v, int tl, int tr, int pos, ll new_val) {
    if (tl == tr) {
        tree[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) update(2 * v, tl, tm, pos, new_val);
        else update(2 * v + 1, tm + 1, tr, pos, new_val);
        tree[v] = gcd(tree[2 * v], tree[2 * v + 1]);
    }
}

ll query(int v, int tl, int tr, int l, int r) {
    if (l > r) return 0; // Identity element for GCD is 0
    if (l == tl && r == tr) return tree[v];
    int tm = (tl + tr) / 2;
    return gcd(query(2 * v, tl, tm, l, min(r, tm)),
               query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r));
}

int main() {
    n = 5;
    // Array: 2, 4, 6, 8, 10
    arr[0]=2; arr[1]=4; arr[2]=6; arr[3]=8; arr[4]=10;
    
    build(1, 0, n-1);
    
    // GCD(2, 4, 6) = 2
    cout << query(1, 0, n-1, 0, 2) << endl; 
    
    // Update index 2 to 7 (Array: 2, 4, 7, 8, 10)
    update(1, 0, n-1, 2, 7);
    
    // GCD(4, 7, 8) = 1
    cout << query(1, 0, n-1, 1, 3) << endl; 
    
    return 0;
}