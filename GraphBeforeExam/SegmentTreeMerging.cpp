#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - "For each node, how many values in its subtree are > X?"
   - "Find dominant color in every subtree."
   - Merge Complexity: O(N log N) total.
*/

const int MAXN = 100005;
const int MAX_VAL = 100005;

struct Node {
    int count;
    Node *left, *right;
    Node() : count(0), left(nullptr), right(nullptr) {}
};

Node* roots[MAXN]; // SegTree root for each node
vector<int> adj[MAXN];
int ans[MAXN];
int values[MAXN]; // Value at node i

// Standard Dynamic Update
void update(Node* node, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        node->count += val;
        return;
    }
    int tm = (tl + tr) / 2;
    if (pos <= tm) {
        if (!node->left) node->left = new Node();
        update(node->left, tl, tm, pos, val);
    } else {
        if (!node->right) node->right = new Node();
        update(node->right, tm + 1, tr, pos, val);
    }
    node->count = (node->left ? node->left->count : 0) + 
                  (node->right ? node->right->count : 0);
}

// MERGE FUNCTION: Merges tree 'b' into tree 'a'. 'b' is destroyed/absorbed.
Node* merge(Node* a, Node* b, int tl, int tr) {
    if (!a) return b;
    if (!b) return a;
    
    // If leaf, combine values
    if (tl == tr) {
        a->count += b->count;
        return a;
    }
    
    int tm = (tl + tr) / 2;
    a->left = merge(a->left, b->left, tl, tm);
    a->right = merge(a->right, b->right, tm + 1, tr);
    
    a->count = (a->left ? a->left->count : 0) + (a->right ? a->right->count : 0);
    return a;
}

// Query: Count values > K
int query_greater(Node* node, int tl, int tr, int k) {
    if (!node || tr <= k) return 0; // Range is completely <= k
    if (tl > k) return node->count; // Range is completely > k
    
    int tm = (tl + tr) / 2;
    return query_greater(node->left, tl, tm, k) + 
           query_greater(node->right, tm + 1, tr, k);
}

void dfs(int u, int p) {
    // 1. Create initial tree for current node
    roots[u] = new Node();
    update(roots[u], 1, MAX_VAL, values[u], 1);
    
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            // 2. Merge child's tree into current tree
            roots[u] = merge(roots[u], roots[v], 1, MAX_VAL);
        }
    }
    
    // 3. Answer query for this subtree
    // Example: How many nodes in subtree have value > 25?
    ans[u] = query_greater(roots[u], 1, MAX_VAL, 25);
}

int main() {
    int n = 3;
    values[1] = 10; values[2] = 30; values[3] = 40;
    adj[1].push_back(2); adj[1].push_back(3);
    
    dfs(1, 0);
    
    cout << "Node 1 Subtree > 25: " << ans[1] << endl; // Should be 2 (30 and 40)
    return 0;
}