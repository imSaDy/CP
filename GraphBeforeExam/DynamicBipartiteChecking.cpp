#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Dynamic Bipartite Checking.
   - Supports 'rollback()' to undo the last operation.
   - NO Path Compression (Uses Union by Rank only).
   - Complexity: O(log N) per operation.
*/

struct DSU_Rollback {
    vector<int> parent;
    vector<int> rank;
    vector<int> bipartite; // bipartite[u] = parity of path from u to root
    stack<tuple<int, int, int>> history; // Stores {u, v, rank_was_equal}

    DSU_Rollback(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
        rank.assign(n + 1, 0);
        bipartite.assign(n + 1, 0);
    }

    // Find returns {root, parity_relative_to_root}
    pair<int, int> find(int i) {
        if (parent[i] == i)
            return {i, 0};
        pair<int, int> root = find(parent[i]);
        // Parity is my parity to parent XOR parent's parity to root
        return {root.first, root.second ^ bipartite[i]};
    }

    // Returns false if adding this edge makes graph NON-Bipartite
    bool unite(int i, int j) {
        auto [root_i, x_i] = find(i);
        auto [root_j, x_j] = find(j);
        
        if (root_i != root_j) {
            // Union by Rank
            if (rank[root_i] < rank[root_j]) swap(root_i, root_j);
            
            parent[root_j] = root_i;
            // The edge (i, j) implies color(i) != color(j).
            // Current relative: color(i) = x_i, color(j) = x_j (relative to their roots)
            // We need: x_i ^ x_j ^ (edge weight 1) = parity between roots.
            // bipartite[root_j] stores parity of root_j relative to new parent root_i
            bipartite[root_j] = x_i ^ x_j ^ 1;
            
            history.push({root_j, rank[root_i] == rank[root_j], 1}); // 1 = merge happened
            if (rank[root_i] == rank[root_j]) rank[root_i]++;
            
            return true; // Still bipartite
        } else {
            // Same component. Check for conflict.
            if (x_i == x_j) return false; // Odd cycle detected! Not bipartite.
            
            history.push({-1, -1, 0}); // 0 = no merge happened
            return true;
        }
    }

    void rollback() {
        if (history.empty()) return;
        auto [child, rank_equal, merged] = history.top();
        history.pop();
        
        if (merged) {
            int root = parent[child];
            parent[child] = child;
            bipartite[child] = 0;
            if (rank_equal) rank[root]--;
        }
    }
};

int main() {
    DSU_Rollback dsu(5);
    // Add edges 1-2, 2-3 -> Bipartite OK
    dsu.unite(1, 2);
    dsu.unite(2, 3);
    
    // Check 1-3. Parity 1->2 is 1. 2->3 is 1. 1->3 is 0 (Same color).
    // Adding 1-3 edge should return False (Odd cycle 1-2-3-1)
    if (!dsu.unite(1, 3)) {
        cout << "Adding 1-3 creates odd cycle!" << endl;
    }
    
    // Undo the failed attempt (or the successful check depending on logic)
    dsu.rollback();
    
    return 0;
}