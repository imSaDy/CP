#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Lowest Common Ancestor (LCA) in O(log N).
   - Distance between two nodes: depth[u] + depth[v] - 2*depth[lca(u, v)].
   - Path property queries (static).
*/

const int MAXN = 200005;
const int LOG = 20; // Sufficient for N <= 10^6

vector<int> adj[MAXN];
int up[MAXN][LOG]; // up[u][i] is the 2^i-th ancestor of u
int depth[MAXN];

void dfs(int u, int p, int d) {
    depth[u] = d;
    up[u][0] = p; // 2^0 ancestor is parent
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, d + 1);
        }
    }
}

void build_lca(int n, int root = 1) {
    // 1. Run DFS to get immediate parents and depths
    dfs(root, root, 0); 

    // 2. Dynamic Programming for 2^i jumps
    for (int j = 1; j < LOG; j++) {
        for (int i = 1; i <= n; i++) {
            // My 2^j ancestor is my (2^(j-1)) ancestor's (2^(j-1)) ancestor
            up[i][j] = up[ up[i][j-1] ][j-1];
        }
    }
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    
    // 1. Lift u to the same depth as v
    for (int j = LOG - 1; j >= 0; j--) {
        if (depth[u] - (1 << j) >= depth[v]) {
            u = up[u][j];
        }
    }
    
    if (u == v) return u;
    
    // 2. Lift both until they are just below the LCA
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[u][j] != up[v][j]) {
            u = up[u][j];
            v = up[v][j];
        }
    }
    
    return up[u][0];
}

int get_dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
}

// Function to get the K-th ancestor of node u
int get_kth_ancestor(int u, int k) {
    for (int j = 0; j < LOG; j++) {
        if ((k >> j) & 1) {
            u = up[u][j];
        }
    }
    return u;
}

int main() {
    int n = 5;
    // Edges: 1-2, 1-3, 3-4, 3-5
    adj[1].push_back(2); adj[2].push_back(1);
    adj[1].push_back(3); adj[3].push_back(1);
    adj[3].push_back(4); adj[4].push_back(3);
    adj[3].push_back(5); adj[5].push_back(3);
    
    build_lca(n, 1);
    
    cout << "LCA(4, 5): " << get_lca(4, 5) << endl; // 3
    cout << "Dist(2, 4): " << get_dist(2, 4) << endl; // 3 (2-1-3-4)
    
    return 0;
}