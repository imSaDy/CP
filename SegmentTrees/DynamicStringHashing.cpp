#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Dynamic String Hashing.
   - Point Update (Change char).
   - Range Hash Query (Compare substrings).
   - Can check for palindromes if you maintain a 2nd tree for Reverse String.
*/

typedef long long ll;
const int MAXN = 200005;
const ll MOD = 1e9 + 7;
const ll BASE = 313;

ll tree[4 * MAXN];
ll power[MAXN]; // Stores BASE^k
string s;
int n;

void init_powers() {
    power[0] = 1;
    for (int i = 1; i < MAXN; i++) 
        power[i] = (power[i - 1] * BASE) % MOD;
}

void build(int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = s[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(2 * v, tl, tm);
        build(2 * v + 1, tm + 1, tr);
        
        // Hash(Left + Right) = Hash(Left) * Base^Len(Right) + Hash(Right)
        int right_len = tr - tm;
        tree[v] = (tree[2 * v] * power[right_len] + tree[2 * v + 1]) % MOD;
    }
}

void update(int v, int tl, int tr, int pos, char new_val) {
    if (tl == tr) {
        tree[v] = new_val;
        s[pos] = new_val; // Update string mainly for debugging/reference
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) update(2 * v, tl, tm, pos, new_val);
        else update(2 * v + 1, tm + 1, tr, pos, new_val);
        
        int right_len = tr - tm;
        tree[v] = (tree[2 * v] * power[right_len] + tree[2 * v + 1]) % MOD;
    }
}

ll query(int v, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    if (l == tl && r == tr) return tree[v];
    
    int tm = (tl + tr) / 2;
    // Overlap logic
    if (r <= tm) return query(2 * v, tl, tm, l, r);
    if (l > tm) return query(2 * v + 1, tm + 1, tr, l, r);
    
    // Split query
    ll hash_left = query(2 * v, tl, tm, l, tm);
    ll hash_right = query(2 * v + 1, tm + 1, tr, tm + 1, r);
    
    // Determine length of the part of the query that fell into the right child
    int right_part_len = r - tm;
    
    return (hash_left * power[right_part_len] + hash_right) % MOD;
}

int main() {
    init_powers();
    s = "bananana";
    n = s.size();
    
    build(1, 0, n-1);
    
    // Hash("nana" at index 2) vs Hash("nana" at index 4)
    if (query(1, 0, n-1, 2, 5) == query(1, 0, n-1, 4, 7)) {
        cout << "Substrings match!" << endl;
    }
    
    update(1, 0, n-1, 2, 'z'); // "bazanana"
    
    if (query(1, 0, n-1, 2, 5) != query(1, 0, n-1, 4, 7)) {
        cout << "Substrings no longer match!" << endl;
    }
    
    return 0;
}