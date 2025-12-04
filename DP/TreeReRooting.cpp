#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Calculate "Sum of distances from root to all other nodes" for EVERY node.
   - O(N) complexity.
   - Can be adapted for other path problems (max path, etc).
*/

const int MAXN = 200005;
vector<int> adj[MAXN];
long long subtree_size[MAXN]; // Size of subtree rooted at i (in dfs1)
long long dp[MAXN];           // dp[u]: Sum of distances if u is root
int n;

// Step 1: Standard Tree DP (Bottom-Up)
// Calculate subtree sizes and answer for a FIXED root (usually node 0)
void dfs1(int u, int p) {
    subtree_size[u] = 1;
    dp[u] = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        dfs1(v, u);
        subtree_size[u] += subtree_size[v];
        // Distances in u's subtree = distances in v's subtree + 1 for each node in v
        dp[u] += dp[v] + subtree_size[v];
    }
}

// Step 2: Rerooting (Top-Down)
// Use parent's full answer to compute child's full answer
void dfs2(int u, int p) {
    for (int v : adj[u]) {
        if (v == p) continue;
        
        // --- THE REROOTING LOGIC ---
        // We know dp[u] is the answer if u is root.
        // We want dp[v] (answer if v is root).
        
        // When moving root from u to v:
        // 1. Nodes in v's subtree get 1 unit CLOSER. (Count: subtree_size[v])
        // 2. Nodes NOT in v's subtree get 1 unit FARTHER. (Count: N - subtree_size[v])
        
        dp[v] = dp[u] - subtree_size[v] + (n - subtree_size[v]);
        
        dfs2(v, u);
    }
}

int main() {
    n = 4;
    // Edges: 0-1, 1-2, 2-3 (Line graph)
    adj[0].push_back(1); adj[1].push_back(0);
    adj[1].push_back(2); adj[2].push_back(1);
    adj[2].push_back(3); adj[3].push_back(2);

    dfs1(0, -1); // Build base info
    dfs2(0, -1); // Spread info to all nodes

    for(int i = 0; i < n; i++) {
        cout << "Node " << i << ": " << dp[i] << endl;
    }
    // Expected for 0-1-2-3:
    // Node 0: 1+2+3 = 6
    // Node 1: 1+1+2 = 4
    // Node 2: 2+1+1 = 4
    // Node 3: 3+2+1 = 6
    return 0;
}