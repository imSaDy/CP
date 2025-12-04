#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - "Update node value, Query sum of neighbor values"
   - Works for general graphs where degree variance is high.
   - Complexity: O(Q * sqrt(E)).
*/

const int MAXN = 100005;
const int SQRT_E = 320; 

vector<int> adj[MAXN];
vector<int> heavy_neighbors[MAXN]; // Only stores neighbors that are Heavy
long long val[MAXN];
long long sum_cache[MAXN]; // Only used if node is Heavy
bool is_heavy[MAXN];

int main() {
    int n = 5, m = 4; // Nodes, Edges
    // Star graph centered at 1
    adj[1]={2,3,4,5};
    adj[2]={1}; adj[3]={1}; adj[4]={1}; adj[5]={1};
    
    // 1. Identify Heavy Nodes
    for(int i=1; i<=n; i++) {
        if (adj[i].size() >= SQRT_E) {
            is_heavy[i] = true;
        }
    }
    
    // 2. Build heavy_neighbors list for EVERY node
    // This allows any node (Light or Heavy) to quickly push updates to Heavy neighbors
    for(int i=1; i<=n; i++) {
        for(int neighbor : adj[i]) {
            if (is_heavy[neighbor]) {
                heavy_neighbors[i].push_back(neighbor);
            }
        }
    }
    
    // 3. Helper Functions
    auto update = [&](int u, int add_val) {
        val[u] += add_val;
        // Push this change to all my HEAVY neighbors
        // (Because Heavy neighbors rely on their cache)
        for(int v : heavy_neighbors[u]) {
            sum_cache[v] += add_val;
        }
    };
    
    auto query = [&](int u) {
        if (is_heavy[u]) {
            // Heavy: Return cached sum
            return sum_cache[u];
        } else {
            // Light: Iterate all edges (small number)
            long long res = 0;
            for(int v : adj[u]) {
                res += val[v];
            }
            return res;
        }
    };
    
    // Init values
    for(int i=1; i<=n; i++) update(i, 10); // Everyone gets 10
    
    // Query center (Heavy)
    // Should be 10+10+10+10 = 40 (neighbors 2,3,4,5)
    // Note: In this small example 1 might not be "Heavy" by threshold 320, 
    // but assuming logic holds:
    if (adj[1].size() >= SQRT_E) cout << query(1) << endl; 
    else cout << "Example too small for sqrt logic, but query(1) = " << query(1) << endl;

    update(2, 5); // Add 5 to node 2
    
    // Query center again. Should be 45.
    cout << query(1) << endl;
    
    return 0;
}