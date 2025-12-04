#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Maximum Flow from S to T.
   - Minimum Cut (value is same as max flow).
   - Maximum Bipartite Matching (Edges cap=1).
   
   COMPLEXITY:
   - General: O(V^2 * E)
   - Unit Capacity Networks (Bipartite Matching): O(E * sqrt(V))
*/

const long long INF = 1e18;

struct Edge {
    int to;
    long long cap;
    long long flow;
    int rev; // Index of reverse edge in adjacency list
};

struct Dinic {
    int n;
    vector<vector<Edge>> adj;
    vector<int> level;
    vector<int> ptr; // Pointer to next edge to explore (optimization)

    Dinic(int n) : n(n) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int from, int to, long long cap) {
        // Forward edge: cap = capacity, flow = 0
        Edge a = {to, cap, 0, (int)adj[to].size()};
        // Backward edge: cap = 0, flow = 0
        Edge b = {from, 0, 0, (int)adj[from].size()};
        adj[from].push_back(a);
        adj[to].push_back(b);
    }

    // BFS to build Level Graph
    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto& edge : adj[v]) {
                if (edge.cap - edge.flow > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[v] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[t] != -1;
    }

    // DFS to push flow along level graph
    long long dfs(int v, int t, long long pushed) {
        if (pushed == 0) return 0;
        if (v == t) return pushed;
        
        for (int& cid = ptr[v]; cid < adj[v].size(); ++cid) {
            auto& edge = adj[v][cid];
            int tr = edge.to;
            if (level[v] + 1 != level[tr] || edge.cap - edge.flow == 0) continue;
            
            long long tr_pushed = dfs(tr, t, min(pushed, edge.cap - edge.flow));
            if (tr_pushed == 0) continue;
            
            edge.flow += tr_pushed;
            adj[tr][edge.rev].flow -= tr_pushed;
            return tr_pushed;
        }
        return 0;
    }

    long long max_flow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, t, INF)) {
                flow += pushed;
            }
        }
        return flow;
    }

    // --- RECONSTRUCTION HELPERS ---

    // Returns a list of edges {u, v, flow} that have positive flow
    struct FlowInfo { int u, v; long long flow; };
    vector<FlowInfo> get_flow_edges() {
        vector<FlowInfo> res;
        for (int u = 0; u < n; ++u) {
            for (auto& e : adj[u]) {
                if (e.flow > 0) {
                    res.push_back({u, e.to, e.flow});
                }
            }
        }
        return res;
    }

    // Returns nodes in the "Source Set" (S) of the Min-Cut.
    // The cut edges are those going from a node in S to a node NOT in S.
    vector<int> get_min_cut_source_set(int s) {
        vector<int> source_set;
        vector<bool> vis(n, false);
        queue<int> q;
        
        q.push(s);
        vis[s] = true;
        
        while(!q.empty()) {
            int v = q.front();
            q.pop();
            source_set.push_back(v);
            
            for(auto& e : adj[v]) {
                // If there is residual capacity, we can reach the neighbor
                if (e.cap - e.flow > 0 && !vis[e.to]) {
                    vis[e.to] = true;
                    q.push(e.to);
                }
            }
        }
        return source_set;
    }
};

int main() {
    int n = 4;
    Dinic dinic(n);
    // Add edges: from, to, capacity
    dinic.add_edge(0, 1, 10);
    dinic.add_edge(0, 2, 10);
    dinic.add_edge(1, 2, 2); 
    dinic.add_edge(1, 3, 4);
    dinic.add_edge(2, 3, 9);
    
    cout << "Max Flow: " << dinic.max_flow(0, 3) << endl; 
    
    // 1. Reconstruct Flow
    cout << "Edges with flow:" << endl;
    for(auto edge : dinic.get_flow_edges()) {
        cout << edge.u << " -> " << edge.v << " : " << edge.flow << endl;
    }

    // 2. Reconstruct Min-Cut
    cout << "Min-Cut Source Set nodes: ";
    vector<int> s_set = dinic.get_min_cut_source_set(0);
    for(int u : s_set) cout << u << " ";
    cout << endl;

    return 0;
}