#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Maximum Bipartite Matching.
   - Complexity: O(V * E) - usually runs much faster on random graphs.
   - Note: Use Hopcroft-Karp or Dinic for N > 2000 if time is tight.
*/

const int MAXN = 1005; // Max number of nodes on ONE side
vector<int> adj[MAXN]; // Adjacency list (Left -> Right)
int matchR[MAXN];      // Stores matching for Right nodes (matchR[v] = u)
bool vis[MAXN];        // Visited array for DFS

// Tries to find an augmenting path from u
bool dfs(int u) {
    for (int v : adj[u]) {
        if (vis[v]) continue;
        vis[v] = true;
        
        // If v is not matched OR we can find a new match for v's current partner
        if (matchR[v] == -1 || dfs(matchR[v])) {
            matchR[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    int n, m, k; 
    // n = left nodes, m = right nodes, k = edges
    cin >> n >> m >> k;
    
    for (int i = 0; i < k; ++i) {
        int u, v;
        cin >> u >> v;
        // Assume input is 1-based, convert to 0-based if needed
        // u is in Left set, v is in Right set
        adj[u].push_back(v); 
    }

    fill(matchR, matchR + m + 1, -1);
    
    int result = 0;
    for (int u = 1; u <= n; ++u) { // Iterate through all Left nodes
        fill(vis, vis + m + 1, false); // Reset visited for Right nodes
        if (dfs(u)) {
            result++;
        }
    }
    
    cout << result << endl;

    // --- RECONSTRUCTION ---
    // Iterate through Right nodes (1 to m) to find their partners
    cout << "Matching Edges (Left -> Right):" << endl;
    for (int v = 1; v <= m; ++v) {
        if (matchR[v] != -1) {
            cout << matchR[v] << " " << v << endl;
        }
    }

    return 0;
}