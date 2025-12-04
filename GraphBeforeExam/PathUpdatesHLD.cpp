#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Path Updates and Path Queries on a Tree.
   - Examples: "Add V to all nodes on path u-v", "Max value on path u-v".
   - Complexity: O(log^2 N).
   
   REQUIRES:
   - A standard Segment Tree (included below as simplified struct).
*/

const int MAXN = 100005;
vector<int> adj[MAXN];
int parent[MAXN], depth[MAXN], heavy[MAXN], head[MAXN], pos[MAXN];
int sz[MAXN];
int cur_pos;
int n;

// --- SEGMENT TREE (Range Max Query) ---
int tree[4 * MAXN];
void update_seg(int v, int tl, int tr, int p, int val) {
    if (tl == tr) tree[v] = val;
    else {
        int tm = (tl + tr) / 2;
        if (p <= tm) update_seg(2*v, tl, tm, p, val);
        else update_seg(2*v+1, tm+1, tr, p, val);
        tree[v] = max(tree[2*v], tree[2*v+1]);
    }
}
int query_seg(int v, int tl, int tr, int l, int r) {
    if (l > r) return 0;
    if (l == tl && r == tr) return tree[v];
    int tm = (tl + tr) / 2;
    return max(query_seg(2*v, tl, tm, l, min(r, tm)),
               query_seg(2*v+1, tm+1, tr, max(l, tm+1), r));
}

// --- HLD IMPLEMENTATION ---

// 1. Calculate subtree sizes and heavy children
int dfs_sz(int u, int p) {
    sz[u] = 1;
    parent[u] = p;
    depth[u] = depth[p] + 1;
    int max_sz = 0;
    heavy[u] = -1;
    
    for (int v : adj[u]) {
        if (v != p) {
            sz[u] += dfs_sz(v, u);
            if (sz[v] > max_sz) {
                max_sz = sz[v];
                heavy[u] = v;
            }
        }
    }
    return sz[u];
}

// 2. Decompose into chains and assign positions
void dfs_hld(int u, int h) {
    head[u] = h;
    pos[u] = cur_pos++; // Assign linear index for SegTree
    
    if (heavy[u] != -1) {
        dfs_hld(heavy[u], h); // Continue chain
    }
    
    for (int v : adj[u]) {
        if (v != parent[u] && v != heavy[u]) {
            dfs_hld(v, v); // Start new chain
        }
    }
}

void init_hld(int root = 1) {
    cur_pos = 0;
    dfs_sz(root, root);
    dfs_hld(root, root);
}

// Query Max on Path u-v
int query_path(int u, int v) {
    int res = 0;
    // Jump up chains until u and v are on the same chain
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) swap(u, v);
        // Query this chain segment: head[u] to u
        res = max(res, query_seg(1, 0, n-1, pos[head[u]], pos[u]));
        u = parent[head[u]]; // Jump to parent of chain head
    }
    
    // Now on same chain
    if (depth[u] > depth[v]) swap(u, v);
    res = max(res, query_seg(1, 0, n-1, pos[u], pos[v]));
    return res;
}

// Update point u
void update_node(int u, int val) {
    update_seg(1, 0, n-1, pos[u], val);
}

int main() {
    n = 5;
    adj[1].push_back(2); adj[2].push_back(1);
    adj[1].push_back(3); adj[3].push_back(1);
    adj[3].push_back(4); adj[4].push_back(3);
    adj[3].push_back(5); adj[5].push_back(3);
    
    init_hld();
    
    update_node(2, 10);
    update_node(4, 20);
    update_node(5, 5);
    
    // Path 2-1-3-4. Max is 20 (at node 4).
    cout << query_path(2, 4) << endl; 
    
    return 0;
}