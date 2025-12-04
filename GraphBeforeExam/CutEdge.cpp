#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Find Bridges (Critical Edges).
   - Build "Bridge Tree": Condense 2-Edge-Connected components into single nodes.
   - Any path in the Bridge Tree consists purely of Bridges.
   - Complexity: O(V + E).
*/

const int MAXN = 100005;
vector<int> adj[MAXN];
vector<int> tree_adj[MAXN]; // Adjacency list for the Bridge Tree

int tin[MAXN], low[MAXN], timer;
int comp_id[MAXN], comp_count; // Component ID for each node
bool is_bridge[MAXN]; // Note: This needs mapping if using edge indices
vector<pair<int, int>> bridges;
bool vis[MAXN];

// 1. DFS to find Bridges
void dfs_bridges(int u, int p = -1) {
    vis[u] = true;
    tin[u] = low[u] = ++timer;
    
    for (int v : adj[u]) {
        if (v == p) continue;
        if (vis[v]) {
            // Back-edge
            low[u] = min(low[u], tin[v]);
        } else {
            // Tree-edge
            dfs_bridges(v, u);
            low[u] = min(low[u], low[v]);
            
            if (low[v] > tin[u]) {
                // Edge u-v is a bridge
                bridges.push_back({u, v});
                // Mark edge as bridge (logic depends on how you store edges)
            }
        }
    }
}

// 2. DFS to assign Component IDs (ignoring bridges)
void dfs_comp(int u, int c) {
    comp_id[u] = c;
    for (int v : adj[u]) {
        // Optimization: Use a set or sorted vector for bridges check if N is large
        // Or store is_bridge flag in adjacency list
        bool is_bridge_edge = false;
        for(auto& b : bridges) {
            if ((b.first == u && b.second == v) || (b.first == v && b.second == u)) {
                is_bridge_edge = true; break;
            }
        }
        
        if (comp_id[v] == -1 && !is_bridge_edge) {
            dfs_comp(v, c);
        }
    }
}

void build_bridge_tree(int n) {
    timer = 0;
    fill(vis, vis + n + 1, false);
    fill(tin, tin + n + 1, -1);
    fill(low, low + n + 1, -1);
    bridges.clear();
    
    // Step 1: Find Bridges
    for(int i=1; i<=n; i++) {
        if(!vis[i]) dfs_bridges(i);
    }
    
    // Step 2: Build Components
    fill(comp_id, comp_id + n + 1, -1);
    comp_count = 0;
    for(int i=1; i<=n; i++) {
        if(comp_id[i] == -1) {
            dfs_comp(i, ++comp_count);
        }
    }
    
    // Step 3: Build Tree
    // For every bridge (u, v), add edge between Comp[u] and Comp[v]
    for(int i=1; i<=comp_count; i++) tree_adj[i].clear();
    
    for(auto& b : bridges) {
        int u = b.first;
        int v = b.second;
        int cu = comp_id[u];
        int cv = comp_id[v];
        tree_adj[cu].push_back(cv);
        tree_adj[cv].push_back(cu);
    }
}

int main() {
    int n = 6;
    // Graph: 1-2, 2-3, 3-1 (Cycle 123) -- 3-4 (Bridge) -- 4-5, 5-6, 6-4 (Cycle 456)
    adj[1]={2, 3}; adj[2]={1, 3}; adj[3]={1, 2, 4};
    adj[4]={3, 5, 6}; adj[5]={4, 6}; adj[6]={4, 5};
    
    build_bridge_tree(n);
    
    cout << "Bridges found: " << bridges.size() << endl; // Should be 1 (3-4)
    cout << "Components: " << comp_count << endl; // Should be 2 (1,2,3) and (4,5,6)
    
    return 0;
}