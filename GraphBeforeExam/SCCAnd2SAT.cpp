#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Find Strongly Connected Components (SCC).
   - Solve 2-SAT Problems.
   - Condense Graph into DAG.
   - Complexity: O(V + E).
*/

const int MAXN = 200005; // Nodes
vector<int> adj[MAXN];
int dfs_num[MAXN], dfs_low[MAXN], visited[MAXN];
vector<int> st; // Stack
int timer, scc_count;
int scc_id[MAXN]; // Stores which SCC each node belongs to

void tarjan(int u) {
    dfs_low[u] = dfs_num[u] = ++timer;
    visited[u] = 1; // On Stack
    st.push_back(u);

    for (int v : adj[u]) {
        if (dfs_num[v] == 0) { // Not visited
            tarjan(v);
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (visited[v]) { // Back-edge to node on stack
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }

    if (dfs_low[u] == dfs_num[u]) { // Root of SCC found
        scc_count++;
        while (true) {
            int v = st.back();
            st.pop_back();
            visited[v] = 0; // Off Stack
            scc_id[v] = scc_count;
            if (u == v) break;
        }
    }
}

void find_scc(int n) {
    timer = scc_count = 0;
    fill(dfs_num, dfs_num + n + 1, 0);
    fill(visited, visited + n + 1, 0);
    for (int i = 1; i <= n; i++) {
        if (dfs_num[i] == 0) tarjan(i);
    }
}

// --- 2-SAT SOLVER WRAPPER ---
// Variables are 0..vars-1. 
// Nodes in graph: 2*i is X_i, 2*i+1 is NOT X_i.
struct TwoSAT {
    int n;
    TwoSAT(int vars) : n(vars * 2) {
        for(int i=0; i<=n; i++) adj[i].clear();
    }

    // Add clause (x OR y)
    // is_x_true: true if we want X, false if we want NOT X
    void add_clause(int x, bool is_x_true, int y, bool is_y_true) {
        int u = 2 * x + (is_x_true ? 0 : 1); // If x true, use node 2x. If not x, use 2x+1
        int v = 2 * y + (is_y_true ? 0 : 1);
        
        // (x v y) <=> (!x -> y) AND (!y -> x)
        // NOT u is (u ^ 1)
        adj[u ^ 1].push_back(v);
        adj[v ^ 1].push_back(u);
    }

    bool solve(vector<bool>& assignment) {
        find_scc(n);
        assignment.assign(n / 2, false);
        for (int i = 0; i < n / 2; i++) {
            // If X and !X are in same SCC, impossible
            if (scc_id[2 * i] == scc_id[2 * i + 1]) return false;
            
            // In condensation graph, if SCC(!X) comes after SCC(X) topologically,
            // X is false. (Tarjan generates reverse topological order).
            // Actually simpler: If scc_id[2*i] < scc_id[2*i+1], then X is TRUE.
            // (Depends on Tarjan implementation, usually reverse topo).
            // The standard rule: value is TRUE if SCC(X) is topologically BEFORE SCC(!X).
            // In Tarjan, SCC IDs form reverse topological order. 
            // So if ID(X) < ID(!X), then SCC(X) appears LATER -> SCC(!X) -> SCC(X).
            // This means !X implies X. So X must be true.
            assignment[i] = scc_id[2 * i] < scc_id[2 * i + 1];
        }
        return true;
    }
};

int main() {
    // Example: (x0 OR x1) AND (!x0 OR !x1)
    // Solution: x0 = true, x1 = false OR x0 = false, x1 = true.
    int vars = 2;
    TwoSAT ts(vars);
    
    ts.add_clause(0, true, 1, true);   // (x0 v x1)
    ts.add_clause(0, false, 1, false); // (!x0 v !x1)
    
    vector<bool> result;
    if (ts.solve(result)) {
        cout << "Satisfiable! Assignment: ";
        for(bool b : result) cout << b << " ";
        cout << endl;
    } else {
        cout << "Impossible" << endl;
    }
    return 0;
}