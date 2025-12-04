#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Point Update, Range Sum (or Min/Max/GCD).
   - Simpler than SegTree for some operations.
   - Complexity: O(1) Update, O(sqrt(N)) Query.
*/

const int MAXN = 100005;
const int BLK = 320; // ~sqrt(MAXN)

int arr[MAXN];
long long block_sum[MAXN / BLK + 5]; // Stores sum of each block
int n;

void build() {
    for (int i = 0; i < n; i++) {
        block_sum[i / BLK] += arr[i];
    }
}

void update(int idx, int val) {
    int block_idx = idx / BLK;
    block_sum[block_idx] -= arr[idx];
    arr[idx] = val;
    block_sum[block_idx] += arr[idx];
}

long long query(int l, int r) {
    long long sum = 0;
    int start_block = l / BLK;
    int end_block = r / BLK;
    
    if (start_block == end_block) {
        // Range inside single block
        for (int i = l; i <= r; i++) sum += arr[i];
    } else {
        // 1. Partial Start Block
        for (int i = l; i < (start_block + 1) * BLK; i++) 
            sum += arr[i];
            
        // 2. Full Middle Blocks
        for (int b = start_block + 1; b < end_block; b++) 
            sum += block_sum[b];
            
        // 3. Partial End Block
        for (int i = end_block * BLK; i <= r; i++) 
            sum += arr[i];
    }
    return sum;
}

int main() {
    n = 10;
    for(int i=0; i<n; i++) arr[i] = i+1; // 1 to 10
    build();
    
    cout << query(0, 9) << endl; // 55
    update(0, 10); // arr[0] becomes 10
    cout << query(0, 9) << endl; // 64
    
    return 0;
}