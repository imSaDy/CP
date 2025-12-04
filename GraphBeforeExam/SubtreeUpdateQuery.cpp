#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - "Add value to all nodes in subtree U"
   - "Query sum of values in subtree U"
   - Technique: Euler Tour (DFS Order) flattening.
   - Complexity: O(log N) per op.
*/

const int MAXN = 200005;
vector<int> adj[MAXN];
int in[MAXN], out[MAXN], timer;
int linear_tree[MAXN]; // Stores values in DFS order

// DFS to flatten the tree
void dfs(int u, int p) {
    in[u] = ++timer;
    // Map the initial value of node u to its position in linear array
    // linear_tree[in[u]] = initial_value_of_u; 
    
    for (int v : adj[u]) {
        if (v != p) dfs(v, u);
    }
    out[u] = timer;
}

// --- STANDARD SEGMENT TREE (Range Sum, Range Add) ---
long long tree[4 * MAXN], lazy[4 * MAXN];

void push(int v, int tl, int tr) {
    if (lazy[v] != 0) {
        int tm = (tl + tr) / 2;
        tree[2*v] += lazy[v] * (tm - tl + 1);
        lazy[2*v] += lazy[v];
        tree[2*v+1] += lazy[v] * (tr - tm);
        lazy[2*v+1] += lazy[v];
        lazy[v] = 0;
    }
}

void update(int v, int tl, int tr, int l, int r, int val) {
    if (l > r) return;
    if (l == tl && r == tr) {
        tree[v] += (long long)val * (r - l + 1);
        lazy[v] += val;
    } else {
        push(v, tl, tr);
        int tm = (tl + tr) / 2;
        update(2*v, tl, tm, l, min(r, tm), val);
        update(2*v+1, tm+1, tr, max(l, tm + 1), r, val);
        tree[v] = tree[2*v] + tree[2*v+1];
    }
}

long long query(int v, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    if (l == tl && r == tr) return tree[v];
    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    return query(2*v, tl, tm, l, min(r, tm)) + 
           query(2*v+1, tm+1, tr, max(l, tm+1), r);
}

int main() {
    int n = 5;
    adj[1].push_back(2); adj[1].push_back(3);
    adj[2].push_back(4); adj[2].push_back(5);
    
    timer = 0;
    dfs(1, 0); // Flatten
    
    // Add 10 to entire subtree of 2 (Nodes 2, 4, 5)
    update(1, 1, n, in[2], out[2], 10);
    
    // Query sum of subtree 1 (Should be 30, as 3 nodes got +10)
    cout << query(1, 1, n, in[1], out[1]) << endl;
    
    return 0;
}