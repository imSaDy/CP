#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Check if two nodes are connected: same(u, v)
   - Merge two sets: unite(u, v)
   - Get size of component: getSize(u)
   - Complexity: Inverse Ackermann Function (nearly O(1)).
*/

struct DSU {
    vector<int> parent;
    vector<int> size;
    int num_components;

    DSU(int n) {
        parent.resize(n + 1);
        size.assign(n + 1, 1);
        num_components = n; // Assuming 1-based or 0-based, handles both if size is N+1
        iota(parent.begin(), parent.end(), 0); // Fill 0, 1, 2...
    }

    // Find with Path Compression
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    // Unite by Size
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        
        if (root_i != root_j) {
            // Union by Size: Attach smaller tree to larger tree
            if (size[root_i] < size[root_j])
                swap(root_i, root_j);
            
            parent[root_j] = root_i;
            size[root_i] += size[root_j];
            num_components--;
            return true; // Merge successful
        }
        return false; // Already in same set
    }

    bool same(int i, int j) {
        return find(i) == find(j);
    }

    int getSize(int i) {
        return size[find(i)];
    }
};

int main() {
    int n = 5;
    DSU dsu(n);
    
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    
    cout << "1 and 2 same? " << dsu.same(1, 2) << endl; // 1 (True)
    cout << "1 and 3 same? " << dsu.same(1, 3) << endl; // 0 (False)
    
    dsu.unite(2, 4); // Merges {1,2} and {3,4} -> {1,2,3,4}
    
    cout << "Size of 1's component: " << dsu.getSize(1) << endl; // 4
    cout << "Total components: " << dsu.num_components << endl; // 2 (Set {1,2,3,4} and Set {0} or {5})
    
    return 0;
}