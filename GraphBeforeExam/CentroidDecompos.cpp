#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Count paths with specific properties (length K, etc).
   - "Divide and Conquer" on trees.
   - Complexity: O(N log N).
*/

const int MAXN = 100005;
vector<int> adj[MAXN];
bool removed[MAXN]; // Tracks removed centroids
int sub_sz[MAXN];
int n;

// 1. Calculate subtree sizes
void calc_sz(int u, int p) {
    sub_sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !removed[v]) {
            calc_sz(v, u);
            sub_sz[u] += sub_sz[v];
        }
    }
}

// 2. Find Centroid
int find_centroid(int u, int p, int tree_size) {
    for (int v : adj[u]) {
        if (v != p && !removed[v] && sub_sz[v] > tree_size / 2) {
            return find_centroid(v, u, tree_size);
        }
    }
    return u;
}

// 3. Problem specific processing
// Example: Collect distances from centroid to all nodes in current component
void get_dists(int u, int p, int depth, vector<int>& dists) {
    dists.push_back(depth);
    for (int v : adj[u]) {
        if (v != p && !removed[v]) {
            get_dists(v, u, depth + 1, dists);
        }
    }
}

long long ans = 0;
int K = 2; // Target path length

// 4. Main Decomposition Function
void decompose(int u) {
    calc_sz(u, -1);
    int centroid = find_centroid(u, -1, sub_sz[u]);
    
    // --- SOLVE FOR PATHS PASSING THROUGH CENTROID ---
    // Example: Count paths of length K
    vector<int> total_dists;
    total_dists.push_back(0); // Centroid itself
    
    // For each child subtree...
    for (int v : adj[centroid]) {
        if (!removed[v]) {
            vector<int> child_dists;
            get_dists(v, centroid, 1, child_dists);
            
            // Check pairs: (d from child) + (d from total) == K
            for (int d : child_dists) {
                // In full implementation, use a frequency array or hash map for O(1) check
                // Here brute force O(N^2) for clarity, but you MUST optimize this part.
                for (int existing : total_dists) {
                    if (d + existing == K) ans++;
                }
            }
            // Add current subtree to total
            for(int d : child_dists) total_dists.push_back(d);
        }
    }
    // ------------------------------------------------
    
    removed[centroid] = true;
    
    for (int v : adj[centroid]) {
        if (!removed[v]) {
            decompose(v);
        }
    }
}

int main() {
    n = 3;
    adj[1].push_back(2); adj[2].push_back(1);
    adj[2].push_back(3); adj[3].push_back(2);
    
    decompose(1);
    cout << "Paths of length " << K << ": " << ans << endl; // Path 1-2-3 (Length 2)
    return 0;
}