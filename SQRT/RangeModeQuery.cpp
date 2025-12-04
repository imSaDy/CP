#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Find Mode (Most Frequent Element) in Range [L, R].
   - Complexity: O(N * sqrt(N)).
   - Requires Coordinate Compression if values are large.
*/

const int MAXN = 100005;
const int BLK = 320; 

int a[MAXN];
vector<int> pos[MAXN]; // Stores indices for each value: pos[val] = {idx1, idx2...}
int mode_blk[320][320]; // mode_blk[i][j] stores mode of blocks i through j
int max_freq_blk[320][320]; 

// Count occurrences of val in range [l, r]
int count_val(int l, int r, int val) {
    // Upper bound - Lower bound on the sorted index list
    auto it1 = lower_bound(pos[val].begin(), pos[val].end(), l);
    auto it2 = upper_bound(pos[val].begin(), pos[val].end(), r);
    return (int)(it2 - it1);
}

void build(int n) {
    int num_blocks = (n + BLK - 1) / BLK;
    
    // Precompute Mode for every pair of blocks [i...j]
    for (int i = 0; i < num_blocks; i++) {
        int best_val = -1;
        int max_freq = -1;
        vector<int> freq(MAXN, 0); // Temporary freq array
        
        for (int j = i; j < num_blocks; j++) {
            // Add block j to the current range
            int start = j * BLK;
            int end = min((j + 1) * BLK, n);
            
            for (int k = start; k < end; k++) {
                int val = a[k];
                freq[val]++;
                if (freq[val] > max_freq) {
                    max_freq = freq[val];
                    best_val = val;
                }
            }
            mode_blk[i][j] = best_val;
            max_freq_blk[i][j] = max_freq;
        }
    }
}

int query(int l, int r) {
    int b_l = l / BLK;
    int b_r = r / BLK;
    
    int best_val = -1;
    int max_f = -1;
    
    if (b_l == b_r) {
        // Same block: Brute force
        for (int i = l; i <= r; i++) {
            int val = a[i];
            int f = count_val(l, r, val);
            if (f > max_f) { max_f = f; best_val = val; }
        }
    } else {
        // Use precomputed middle blocks [b_l+1 ... b_r-1]
        if (b_l + 1 <= b_r - 1) {
            best_val = mode_blk[b_l + 1][b_r - 1];
            max_f = max_freq_blk[b_l + 1][b_r - 1];
            // CAUTION: The precomputed frequency is for the middle blocks ONLY.
            // We need to recount this 'best_val' across the FULL range [l, r]
            // to ensure accurate comparison with tail candidates.
            // Actually, wait: We know it occurs X times in middle. We can just check tails?
            // Safer: Just get its full count in [l, r] now.
            max_f = count_val(l, r, best_val); 
        }
        
        // Check tails
        // Left tail
        for (int i = l; i < (b_l + 1) * BLK; i++) {
            int val = a[i];
            // Optimization: Only check if we haven't checked this value yet?
            // Or just check. Expensive but correct.
            int f = count_val(l, r, val);
            if (f > max_f) { max_f = f; best_val = val; }
        }
        // Right tail
        for (int i = b_r * BLK; i <= r; i++) {
            int val = a[i];
            int f = count_val(l, r, val);
            if (f > max_f) { max_f = f; best_val = val; }
        }
    }
    return best_val;
}

int main() {
    int n = 7;
    // 1 2 1 3 2 2 1
    a[0]=1; a[1]=2; a[2]=1; a[3]=3; a[4]=2; a[5]=2; a[6]=1;
    
    // Fill pos vector
    for(int i=0; i<n; i++) pos[a[i]].push_back(i);
    
    build(n);
    
    cout << "Mode [0, 6]: " << query(0, 6) << endl; // 2 or 1 (both freq 3). Returns first found.
    cout << "Mode [1, 5]: " << query(1, 5) << endl; // 2 (freq 3)
    
    return 0;
}