#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Merge Sort Tree
   - Query: "How many numbers in range [L, R] are strictly smaller than K?"
   - Query: "How many numbers in range [L, R] are greater than K?"

   CAUTIONS:
   - STATIC DATA ONLY: This structure DOES NOT support updates efficiently. 
     If the array values change, you cannot use this easily.
   - MEMORY: Uses O(N log N) memory. If N = 2*10^5, this is heavy (~50MB).
   - BUILD TIME: O(N log N).
*/

const int MAXN = 200005;
vector<int> tree[4 * MAXN];
int arr[MAXN]; 

// Merges two sorted vectors into the parent
void build(int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = vector<int>(1, arr[tl]);
    } else {
        int tm = (tl + tr) / 2;
        build(2 * v, tl, tm);
        build(2 * v + 1, tm + 1, tr);
        
        // Standard STL merge (requires included <algorithm>)
        merge(tree[2 * v].begin(), tree[2 * v].end(),
              tree[2 * v + 1].begin(), tree[2 * v + 1].end(),
              back_inserter(tree[v]));
    }
}

// Query: Count elements < K in range [l, r]
int query(int v, int tl, int tr, int l, int r, int k) {
    if (l > r) return 0;
    if (l == tl && r == tr) {
        // Find first element >= k. All elements before it are < k.
        // lower_bound returns iterator to first element >= k
        return lower_bound(tree[v].begin(), tree[v].end(), k) - tree[v].begin();
    }
    int tm = (tl + tr) / 2;
    return query(2 * v, tl, tm, l, min(r, tm), k) +
           query(2 * v + 1, tm + 1, tr, max(l, tm + 1), r, k);
}

int main() {
    int n = 5;
    // Array: {5, 1, 2, 8, 3}
    arr[0]=5; arr[1]=1; arr[2]=2; arr[3]=8; arr[4]=3;

    build(1, 0, n-1);

    // Query: indices 0 to 4, count numbers < 4
    // Expected: 1, 2, 3 -> Answer 3
    cout << query(1, 0, n-1, 0, 4, 4) << endl; 
    
    return 0;
}