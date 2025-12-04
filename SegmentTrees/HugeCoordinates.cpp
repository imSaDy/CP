#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - When the array indices are huge (e.g., up to 10^9 or 10^18)
   - But the number of queries/updates is reasonable (N <= 2*10^5).
   - "Sparse" Segment Tree: Nodes are created only when accessed.

   CAUTIONS:
   - MEMORY: This uses pointers. If memory is tight (<= 64MB), this might TLE/MLE.
   - Pointers: Always check `if (!node)` before accessing children.
   - Garbage Collection: This implementation does NOT delete nodes. In a multi-testcase 
     problem, you must manually clear `root` or use a node pool array.
*/

typedef long long ll;

struct Node {
    ll val;
    Node *left, *right;
    Node() : val(0), left(nullptr), right(nullptr) {}
};

const int MIN_RANGE = 0;
const int MAX_RANGE = 1e9 + 7; // Define the huge range limit

// Global root for the current tree
Node* root = new Node();

// Point Update: set index `pos` to `new_val` (or add to it)
void update(Node* node, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        node->val += val; // Example: Point Addition
        return;
    }
    int tm = tl + (tr - tl) / 2;
    if (pos <= tm) {
        if (!node->left) node->left = new Node();
        update(node->left, tl, tm, pos, val);
    } else {
        if (!node->right) node->right = new Node();
        update(node->right, tm + 1, tr, pos, val);
    }
    
    // Combine logic (Sum)
    ll leftVal = node->left ? node->left->val : 0;
    ll rightVal = node->right ? node->right->val : 0;
    node->val = leftVal + rightVal;
}

// Range Query: Sum from L to R
ll query(Node* node, int tl, int tr, int l, int r) {
    if (!node || l > r) return 0; // Identity
    if (l == tl && r == tr) return node->val;
    
    int tm = tl + (tr - tl) / 2;
    return query(node->left, tl, tm, l, min(r, tm)) +
           query(node->right, tm + 1, tr, max(l, tm + 1), r);
}

int main() {
    // Example usage
    // No need to "build", just start updating
    update(root, MIN_RANGE, MAX_RANGE, 5, 100);       // index 5 gets +100
    update(root, MIN_RANGE, MAX_RANGE, 1000000, 20);  // index 1,000,000 gets +20
    
    cout << query(root, MIN_RANGE, MAX_RANGE, 0, 1000005) << endl; // 120
    cout << query(root, MIN_RANGE, MAX_RANGE, 0, 10) << endl;      // 100
    return 0;
}