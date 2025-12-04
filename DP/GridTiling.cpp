#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Count ways to tile an N x M grid with 2x1 dominoes.
   - Constraint: M is small (<= 20), N can be large.
   - Complexity: O(N * M * 2^M).
   
   LOGIC:
   - We process cells one by one (r, c).
   - The mask represents the state of the "cut" boundary.
   - If j-th bit is 0: The cell at the border is EMPTY.
   - If j-th bit is 1: The cell at the border is FILLED.
*/

long long dp[2][1 << 10]; // Toggle between [0] and [1] to save space
int n, m;

int main() {
    // Example: 10 rows, 3 columns
    n = 10; m = 3; 

    // Base case: Before starting, the "0-th" cell has empty profile (mask 0)
    memset(dp, 0, sizeof(dp));
    int cur = 0;
    dp[cur][0] = 1;

    for (int i = 0; i < n; ++i) {      // Rows
        for (int j = 0; j < m; ++j) {  // Columns
            int next = cur ^ 1;
            memset(dp[next], 0, sizeof(dp[next]));
            
            for (int mask = 0; mask < (1 << m); ++mask) {
                long long ways = dp[cur][mask];
                if (ways == 0) continue;

                // Check if current cell (i, j) is already covered by a previous domino
                // This corresponds to bit 'j' in the mask.
                if (mask & (1 << j)) {
                    // Case 1: Current cell is already occupied (by a horizontal domino from left 
                    // or vertical from top). We must leave it alone.
                    // Transition: Turn off bit j (it moves out of the profile window).
                    dp[next][mask ^ (1 << j)] += ways;
                } else {
                    // Case 2: Current cell is empty. We MUST cover it.
                    
                    // Option A: Place Vertical Domino (cover (i, j) and (i+1, j))
                    // This makes the NEXT cell (in row i+1) occupied. 
                    // But in our "broken profile" view, this looks like keeping bit 'j' as 1 
                    // for the next state? No. 
                    // In cell-by-cell, placing vertical means we occupy (i, j) now, 
                    // and we mark (i+1, j) as occupied for the future.
                    // The mask bit 'j' becomes 1 for the *next* step.
                    dp[next][mask | (1 << j)] += ways;

                    // Option B: Place Horizontal Domino (cover (i, j) and (i, j+1))
                    // Only possible if we are not at the last column AND next cell is empty.
                    // Next cell empty means bit (j+1) is 0 in current mask.
                    if (j + 1 < m && !(mask & (1 << (j + 1)))) {
                        // We cover (i, j) and (i, j+1).
                        // Both bits j and j+1 in the mask will be 0 for the NEXT state 
                        // (because we effectively skipped past them for the boundary).
                        // Wait - simpler logic:
                        // Current state has j=0, j+1=0.
                        // We fill both. In the next profile (stepping to j+1), 
                        // the bit j becomes irrelevant (0), and bit j+1 is effectively "filled" 
                        // by us now, but since we step *to* j+1 next, we handle it then.
                        // Actually, standard implementation: 
                        // Just set bit (j+1) to 1 in the mask and bit j to 0? 
                        // No, for horizontal, we occupy j and j+1. 
                        // The state transition takes us from (i, j) to (i, j+1).
                        // At (i, j+1), we will see that it is already occupied.
                        // So we essentially set the (j+1) bit to 1 in the *next* mask.
                        dp[next][mask | (1 << (j + 1))] += ways;
                    }
                }
            }
            cur = next;
        }
    }

    // Answer is the state where all cells are processed and profile is empty (0)
    cout << dp[cur][0] << endl;
    return 0;
}