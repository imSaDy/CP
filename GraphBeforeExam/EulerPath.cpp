#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Find a path that visits every edge exactly once.
   - Algorithm: Hierholzer's (O(E)).
   - This implementation is for DIRECTED graph.
   - For Undirected, remove multiset logic and just iterate adj, marking edges used.
*/

const int MAXN = 100005;
vector<int> adj[MAXN];
int in[MAXN], out[MAXN];
vector<int> path;

void dfs(int u) {
    // While there are outgoing edges
    while (!adj[u].empty()) {
        int v = adj[u].back();
        adj[u].pop_back(); // Remove edge
        dfs(v);
    }
    // Add to path AFTER visiting children (Reverse topological-ish)
    path.push_back(u);
}

int main() {
    int n = 3; // Nodes
    // Edges: 1->2, 2->3, 3->1, 1->3
    // Degrees:
    // 1: In 1, Out 2 (Start?)
    // 2: In 1, Out 1
    // 3: In 2, Out 1 (End?)
    
    adj[1].push_back(2); out[1]++; in[2]++;
    adj[2].push_back(3); out[2]++; in[3]++;
    adj[3].push_back(1); out[3]++; in[1]++;
    adj[1].push_back(3); out[1]++; in[3]++;
    
    // 1. Find Start Node
    int start_node = 1; // Default
    int diff_cnt = 0;
    
    for(int i=1; i<=n; i++) {
        if (out[i] - in[i] == 1) {
            start_node = i;
            diff_cnt++;
        } else if (in[i] - out[i] == 1) {
            diff_cnt++;
        } else if (in[i] != out[i]) {
            cout << "No Eulerian Path!" << endl;
            return 0;
        }
    }
    
    if (diff_cnt > 2) {
        cout << "No Eulerian Path!" << endl;
        return 0;
    }
    
    // 2. Run DFS
    dfs(start_node);
    
    // 3. Check if all edges visited (path size == E + 1)
    reverse(path.begin(), path.end());
    
    for(int u : path) cout << u << " ";
    cout << endl;
    
    return 0;
}