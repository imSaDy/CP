#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Range Multiply AND Range Add updates.
   - Range Sum Query.
   - Handles modulo arithmetic automatically.
   
   MATH LOGIC:
   - Node stores sum.
   - Lazy stores {mul, add}.
   - Default Lazy is {1, 0} (Multiply by 1, Add 0).
   - Composition: New(mul, add) applied to Old(mul, add)
     -> Final Mul = OldMul * NewMul
     -> Final Add = OldAdd * NewMul + NewAdd
*/

typedef long long ll;
const int MOD = 1e9 + 7;
const int MAXN = 200005;

struct Lazy {
    ll mul, add;
};

ll tree[4 * MAXN];
Lazy lazy[4 * MAXN];

void build(int v, int tl, int tr, int* arr) {
    lazy[v] = {1, 0}; // Init lazy identity
    if (tl == tr) {
        tree[v] = arr[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(2 * v, tl, tm, arr);
        build(2 * v + 1, tm + 1, tr, arr);
        tree[v] = (tree[2 * v] + tree[2 * v + 1]) % MOD;
    }
}

void push(int v, int tl, int tr) {
    if (lazy[v].mul == 1 && lazy[v].add == 0) return;
    
    int tm = (tl + tr) / 2;
    long long lenL = tm - tl + 1;
    long long lenR = tr - tm;
    
    // Apply to Left Child
    // Sum = Sum * mul + add * length
    tree[2*v] = (tree[2*v] * lazy[v].mul + lazy[v].add * lenL) % MOD;
    lazy[2*v].mul = (lazy[2*v].mul * lazy[v].mul) % MOD;
    lazy[2*v].add = (lazy[2*v].add * lazy[v].mul + lazy[v].add) % MOD;
    
    // Apply to Right Child
    tree[2*v+1] = (tree[2*v+1] * lazy[v].mul + lazy[v].add * lenR) % MOD;
    lazy[2*v+1].mul = (lazy[2*v+1].mul * lazy[v].mul) % MOD;
    lazy[2*v+1].add = (lazy[2*v+1].add * lazy[v].mul + lazy[v].add) % MOD;
    
    lazy[v] = {1, 0}; // Reset
}

// type 0: Range Multiply, type 1: Range Add
void update(int v, int tl, int tr, int l, int r, int val, int type) {
    if (l > r) return;
    if (l == tl && r == tr) {
        if (type == 0) { // Multiply
            tree[v] = (tree[v] * val) % MOD;
            lazy[v].mul = (lazy[v].mul * val) % MOD;
            lazy[v].add = (lazy[v].add * val) % MOD;
        } else { // Add
            tree[v] = (tree[v] + (ll)val * (r - l + 1)) % MOD;
            lazy[v].add = (lazy[v].add + val) % MOD;
        }
    } else {
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        update(2 * v, tl, tm, l, min(r, tm), val, type);
        update(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, val, type);
        tree[v] = (tree[2 * v] + tree[2 * v + 1]) % MOD;
    }
}

ll query(int v, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    if (l == tl && r == tr) return tree[v];
    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    return (query(2 * v, tl, tm, l, min(r, tm)) +
            query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r)) % MOD;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    build(1, 0, 4, arr);
    
    // Multiply range [0, 4] by 2 -> {2, 4, 6, 8, 10}
    update(1, 0, 4, 0, 4, 2, 0);
    
    // Add 1 to range [0, 2] -> {3, 5, 7, 8, 10}
    update(1, 0, 4, 0, 2, 1, 1);
    
    // Query sum [0, 4] -> 3+5+7+8+10 = 33
    cout << query(1, 0, 4, 0, 4) << endl;
    return 0;
}