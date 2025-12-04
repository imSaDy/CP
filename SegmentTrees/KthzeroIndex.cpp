#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Find the index of the K-th Zero (or K-th One, or K-th free spot).
   - Point Update (Change value, which might change zero count).
   - Complexity: O(log N).
*/

const int MAXN = 200005;
int tree[4 * MAXN]; // Stores count of zeros
int arr[MAXN];
int n;

void build(int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = (arr[tl] == 0 ? 1 : 0);
    } else {
        int tm = (tl + tr) / 2;
        build(2 * v, tl, tm);
        build(2 * v + 1, tm + 1, tr);
        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }
}

void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        arr[pos] = new_val;
        tree[v] = (arr[pos] == 0 ? 1 : 0);
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) update(2 * v, tl, tm, pos, new_val);
        else update(2 * v + 1, tm + 1, tr, pos, new_val);
        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }
}

// Returns the 0-based index of the k-th zero (1-based k)
// Returns -1 if fewer than k zeros exist
int find_kth_zero(int v, int tl, int tr, int k) {
    if (k > tree[v]) return -1;
    if (tl == tr) return tl;
    
    int tm = (tl + tr) / 2;
    // Check how many zeros are in the left child
    if (tree[2 * v] >= k) {
        return find_kth_zero(2 * v, tl, tm, k);
    } else {
        return find_kth_zero(2 * v + 1, tm + 1, tr, k - tree[2 * v]);
    }
}

int main() {
    n = 6;
    // Array: 1, 0, 1, 0, 0, 1
    // Zeros at indices: 1, 3, 4
    arr[0]=1; arr[1]=0; arr[2]=1; arr[3]=0; arr[4]=0; arr[5]=1;
    
    build(1, 0, n-1);
    
    cout << "2nd Zero is at index: " << find_kth_zero(1, 0, n-1, 2) << endl; // 3
    
    update(1, 0, n-1, 1, 5); // Change index 1 to 5 (no longer zero)
    // Array: 1, 5, 1, 0, 0, 1
    // Zeros at: 3, 4
    
    cout << "2nd Zero is at index: " << find_kth_zero(1, 0, n-1, 2) << endl; // 4
    
    return 0;
}