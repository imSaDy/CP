#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - "Find K-th smallest weight on path from u to v"
   - Complexity: O(N log N) build, O(log N) query.
   - Technique: Persistence. root[u] = update(root[parent[u]]).
*/

const int MAXN = 100005;
const int MAX_VAL = 100005; // Max value of weights (use coordinate compression if needed)

struct Node {
    int count;
    int left, right;
} tree[MAXN * 25]; // N log N nodes

int roots[MAXN];
int node_cnt = 0;
int weights[MAXN];
vector<int> adj[MAXN];

// LCA Variables
int up[MAXN][20], depth[MAXN], tin[MAXN], tout[MAXN], timer;

// Build empty tree
int build(int tl, int tr) {
    int node = ++node_cnt;
    tree[node].count = 0;
    if (tl != tr) {
        int tm = (tl + tr) / 2;
        tree[node].left = build(tl, tm);
        tree[node].right = build(tm + 1, tr);
    }
    return node;
}

// Persistent Update
int update(int prev_node, int tl, int tr, int val) {
    int node = ++node_cnt;
    tree[node] = tree[prev_node];
    tree[node].count++;
    if (tl == tr) return node;
    int tm = (tl + tr) / 2;
    if (val <= tm) tree[node].left = update(tree[prev_node].left, tl, tm, val);
    else tree[node].right = update(tree[prev_node].right, tm + 1, tr, val);
    return node;
}

// DFS to build Persistent Roots and LCA table
void dfs(int u, int p, int d) {
    depth[u] = d;
    tin[u] = ++timer;
    up[u][0] = p;
    for(int i=1; i<20; i++) up[u][i] = up[up[u][i-1]][i-1];
    
    // Create my version based on parent's version
    roots[u] = update(roots[p], 1, MAX_VAL, weights[u]);
    
    for (int v : adj[u]) {
        if (v != p) dfs(v, u, d + 1);
    }
    tout[u] = ++timer;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int get_lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = 19; i >= 0; i--) {
        if (!is_ancestor(up[u][i], v)) u = up[u][i];
    }
    return up[u][0];
}

// Query 4 roots: u, v, lca, parent(lca)
int query(int node_u, int node_v, int node_lca, int node_plca, int tl, int tr, int k) {
    if (tl == tr) return tl;
    int tm = (tl + tr) / 2;
    
    // Count items in left subtree across the path
    int cnt = tree[tree[node_u].left].count + tree[tree[node_v].left].count 
            - tree[tree[node_lca].left].count - tree[tree[node_plca].left].count;
            
    if (k <= cnt) 
        return query(tree[node_u].left, tree[node_v].left, tree[node_lca].left, tree[node_plca].left, tl, tm, k);
    else 
        return query(tree[node_u].right, tree[node_v].right, tree[node_lca].right, tree[node_plca].right, tm + 1, tr, k - cnt);
}

int main() {
    int n = 5;
    // Values: 1:10, 2:20, 3:30, 4:40, 5:50
    weights[1]=10; weights[2]=20; weights[3]=30; weights[4]=40; weights[5]=50;
    
    adj[1].push_back(2); adj[2].push_back(1);
    adj[1].push_back(3); adj[3].push_back(1);
    adj[2].push_back(4); adj[4].push_back(2);
    adj[2].push_back(5); adj[5].push_back(2);
    
    roots[0] = build(1, MAX_VAL); // Dummy root 0
    dfs(1, 0, 0);
    
    // Path 4 -> 5 is 4-2-5. Values {40, 20, 50}. Sorted: {20, 40, 50}.
    // 2nd Smallest should be 40.
    int u = 4, v = 5, k = 2;
    int lca = get_lca(u, v);
    int ans = query(roots[u], roots[v], roots[lca], roots[up[lca][0]], 1, MAX_VAL, k);
    
    cout << "2nd smallest on 4-5: " << ans << endl;
    return 0;
}