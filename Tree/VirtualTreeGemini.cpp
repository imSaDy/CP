#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Process queries on a subset of K nodes in a large tree.
   - Build a compressed tree with K nodes + their LCAs.
   - Complexity: O(K log K) per query. Total O(N log N) prep.
*/

const int MAXN = 200005;
vector<int> adj[MAXN];
int in[MAXN], out[MAXN], timer;
int up[MAXN][20], depth[MAXN];

// LCA & Prep
void dfs(int u, int p, int d) {
    in[u] = ++timer;
    depth[u] = d;
    up[u][0] = p;
    for(int i=1; i<20; i++) up[u][i] = up[up[u][i-1]][i-1];
    for(int v : adj[u]) if(v!=p) dfs(v, u, d+1);
    out[u] = ++timer;
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = 19; i >= 0; i--)
        if (depth[u] - (1 << i) >= depth[v]) u = up[u][i];
    if (u == v) return u;
    for (int i = 19; i >= 0; i--)
        if (up[u][i] != up[v][i]) u = up[u][i], v = up[v][i];
    return up[u][0];
}

// VIRTUAL TREE STRUCTURE
vector<int> vadj[MAXN]; // Adjacency for Virtual Tree
bool is_marked[MAXN];   // Helper

// Comparator for DFS order
bool cmp_dfs(int u, int v) { return in[u] < in[v]; }

// Build Virtual Tree from a subset of nodes 'k_nodes'
int build_virtual_tree(vector<int>& nodes) {
    // 1. Sort by DFS entry time
    sort(nodes.begin(), nodes.end(), cmp_dfs);
    
    // 2. Add LCAs of adjacent sorted nodes to ensure connectivity
    int k = nodes.size();
    for (int i = 0; i < k - 1; i++) {
        nodes.push_back(get_lca(nodes[i], nodes[i+1]));
    }
    
    // 3. Sort again and remove duplicates
    sort(nodes.begin(), nodes.end(), cmp_dfs);
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
    
    // 4. Build edges using a stack
    // Stack maintains the "current path" from root
    vector<int> st;
    st.push_back(nodes[0]);
    
    // Clear previous virtual edges (only for nodes we are using)
    for(int u : nodes) vadj[u].clear();
    
    for (int i = 1; i < nodes.size(); i++) {
        int u = nodes[i];
        while (st.size() > 1) {
            int top = st.back();
            int lca = get_lca(u, top);
            if (lca == top) break; // u is in subtree of top
            st.pop_back();
        }
        // The top of stack is now the parent of u in Virtual Tree
        int parent = st.back();
        vadj[parent].push_back(u);
        vadj[u].push_back(parent); // Remove if Directed Virtual Tree desired
        st.push_back(u);
    }
    
    return nodes[0]; // Return root of virtual tree
}

// Example DP on Virtual Tree: Count marked nodes in subtree
int dp_cnt[MAXN];
void v_dfs(int u, int p) {
    dp_cnt[u] = is_marked[u] ? 1 : 0;
    for (int v : vadj[u]) {
        if (v != p) {
            v_dfs(v, u);
            dp_cnt[u] += dp_cnt[v];
        }
    }
}

int main() {
    // Setup Main Tree
    adj[1]={2,3}; adj[2]={1,4,5}; adj[3]={1}; adj[4]={2}; adj[5]={2};
    dfs(1, 1, 0); // Precompute LCA info
    
    // Query: Subset {4, 5}
    vector<int> subset = {4, 5};
    for(int x : subset) is_marked[x] = true;
    
    int v_root = build_virtual_tree(subset);
    
    // Run DP on virtual tree
    v_dfs(v_root, -1);
    
    // LCA of 4 and 5 is 2. Virtual Tree has nodes {2, 4, 5}.
    // dp_cnt[2] should be 2.
    cout << "Marked nodes in subtree of 2: " << dp_cnt[2] << endl;
    
    return 0;
}