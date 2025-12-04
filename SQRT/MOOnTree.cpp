#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - "Count distinct values on path u-v"
   - "Sum of values on path u-v"
   - Technique: Flatten tree + Mo's Algorithm.
   - Complexity: O((N+Q) * sqrt(N)).
*/

const int MAXN = 100005;
const int BLK = 450;

vector<int> adj[MAXN];
int val[MAXN];     // Value/Color of node
int flat[2*MAXN];  // Flattened tree array
int in[MAXN], out[MAXN], timer;
int up[MAXN][20], depth[MAXN]; // LCA stuff

// Mo's State
int cnt[MAXN];      // Frequency of values
bool node_vis[MAXN]; // Is node currently in the Mo's window?
int ans[MAXN];
int curr_distinct = 0;

struct Query {
    int l, r, lca, id;
    bool operator<(const Query& o) const {
        int b1 = l / BLK;
        int b2 = o.l / BLK;
        if (b1 != b2) return b1 < b2;
        return (b1 & 1) ? (r < o.r) : (r > o.r);
    }
};

void dfs(int u, int p, int d) {
    depth[u] = d;
    up[u][0] = p;
    for(int i=1; i<20; i++) up[u][i] = up[up[u][i-1]][i-1];
    
    in[u] = ++timer;
    flat[timer] = u;
    
    for(int v : adj[u]) {
        if(v != p) dfs(v, u, d+1);
    }
    
    out[u] = ++timer;
    flat[timer] = u;
}

int get_lca(int u, int v) {
    if(depth[u] < depth[v]) swap(u, v);
    for(int i=19; i>=0; i--) {
        if(depth[u] - (1<<i) >= depth[v]) u = up[u][i];
    }
    if(u == v) return u;
    for(int i=19; i>=0; i--) {
        if(up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

// TOGGLE: If node is in set, remove it. If not, add it.
void toggle(int u) {
    int c = val[u];
    if (node_vis[u]) {
        // Removing
        cnt[c]--;
        if (cnt[c] == 0) curr_distinct--;
    } else {
        // Adding
        if (cnt[c] == 0) curr_distinct++;
        cnt[c]++;
    }
    node_vis[u] = !node_vis[u];
}

int main() {
    int n = 5;
    val[1]=1; val[2]=2; val[3]=1; val[4]=3; val[5]=2;
    adj[1].push_back(2); adj[2].push_back(1);
    adj[1].push_back(3); adj[3].push_back(1);
    adj[2].push_back(4); adj[4].push_back(2);
    adj[2].push_back(5); adj[5].push_back(2);
    
    dfs(1, 1, 0);
    
    int q_cnt = 2;
    vector<Query> qs;
    
    // Query 1: Path 4-5. Path is 4-2-5. Values: 3, 2, 2. Distinct: 2.
    // Logic to range setup:
    int u = 4, v = 5;
    if (in[u] > in[v]) swap(u, v);
    int lca = get_lca(u, v);
    if (lca == u) qs.push_back({in[u], in[v], 0, 0}); // 0 means no extra LCA needed
    else qs.push_back({out[u], in[v], lca, 0});
    
    sort(qs.begin(), qs.end());
    
    int l = 1, r = 0;
    for (auto& q : qs) {
        while (l > q.l) toggle(flat[--l]);
        while (r < q.r) toggle(flat[++r]);
        while (l < q.l) toggle(flat[l++]);
        while (r > q.r) toggle(flat[r--]);
        
        if (q.lca) toggle(q.lca); // Temporarily add LCA
        ans[q.id] = curr_distinct;
        if (q.lca) toggle(q.lca); // Remove LCA back
    }
    
    cout << "Path 4-5 distinct: " << ans[0] << endl;
    
    return 0;
}