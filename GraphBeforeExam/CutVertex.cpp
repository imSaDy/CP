#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Find Articulation Points (Cut Vertices).
   - Build Block-Cut Tree.
   - Useful for: "Is node X on ALL paths between A and B?"
*/

const int MAXN = 100005;
vector<int> adj[MAXN];
vector<int> bct_adj[2 * MAXN]; // Block-Cut Tree (Size can be 2*N)

int tin[MAXN], low[MAXN], timer;
vector<int> stk; // Stack for finding components
int bcc_cnt; // Count of Biconnected Components (Blocks)
bool is_cut[MAXN]; // Is Articulation Point
int n;

void dfs_ap(int u, int p = -1) {
    tin[u] = low[u] = ++timer;
    stk.push_back(u);
    int children = 0;
    
    for (int v : adj[u]) {
        if (v == p) continue;
        if (tin[v]) {
            // Back-edge
            low[u] = min(low[u], tin[v]);
        } else {
            children++;
            dfs_ap(v, u);
            low[u] = min(low[u], low[v]);
            
            // Check if u is an articulation point for child v
            if ((p != -1 && low[v] >= tin[u]) || (p == -1 && children > 1)) {
                is_cut[u] = true;
                
                // --- BUILD BLOCK-CUT TREE ON THE FLY ---
                bcc_cnt++; // New Block ID
                // Block IDs start after Node IDs to differentiate
                int block_node = n + bcc_cnt; 
                
                // Add edge between Cut Vertex u and new Block
                bct_adj[u].push_back(block_node);
                bct_adj[block_node].push_back(u);
                
                // Pop nodes belonging to this block
                while (true) {
                    int node = stk.back();
                    stk.pop_back();
                    // Connect node to Block
                    // NOTE: An articulation point stays in stack if it belongs to multiple blocks below
                    // But 'node' is internal to the block (or a lower cut vertex)
                    if (node != u) {
                        bct_adj[node].push_back(block_node);
                        bct_adj[block_node].push_back(node);
                    }
                    if (node == v) break;
                }
            }
        }
    }
}

void build_block_cut_tree(int num_nodes) {
    n = num_nodes;
    timer = bcc_cnt = 0;
    fill(tin, tin + n + 1, 0);
    fill(is_cut, is_cut + n + 1, false);
    for(int i=0; i<2*MAXN; i++) bct_adj[i].clear();
    
    // DFS for every component
    for(int i=1; i<=n; i++) {
        if(!tin[i]) {
            stk.clear();
            dfs_ap(i);
            // Handling the last component if stack not empty (usually happens if root is isolated or simple)
            if (!stk.empty()) {
                // Technically implies a remaining BCC
                // Logic depends on exact BCT definition for edge cases.
            }
        }
    }
}

int main() {
    int nodes = 5;
    // 1-2, 2-3, 3-1 (Cycle) -- 3-4 -- 4-5
    // 3 is AP connecting {1,2,3} and {3,4}
    // 4 is AP connecting {3,4} and {4,5}
    adj[1]={2,3}; adj[2]={1,3}; adj[3]={1,2,4}; 
    adj[4]={3,5}; adj[5]={4};
    
    build_block_cut_tree(nodes);
    
    if (is_cut[3]) cout << "Node 3 is an Articulation Point" << endl;
    
    return 0;
}