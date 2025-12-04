#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Given array A of size 2^N.
   - For every mask M, find sum of A[i] where i is a submask of M.
   - i.e., F[mask] = sum(A[i]) for all i such that (i & mask) == i.
   - Time: O(N * 2^N). N <= 24 is safe (3s).
*/

const int N = 20; // Number of bits
int dp[1 << N];   // Initially stores input array A

int main() {
    // 1. Initialize dp[mask] = A[mask]
    int limit = (1 << N);
    for(int i = 0; i < limit; i++) {
        // cin >> dp[i]; 
        dp[i] = i; // Dummy data
    }

    // 2. SOS Logic
    // Iterate over each bit position
    for (int i = 0; i < N; ++i) {
        // Iterate over all masks
        for (int mask = 0; mask < limit; ++mask) {
            // If the i-th bit is ON, include the subset with i-th bit OFF
            if (mask & (1 << i)) {
                dp[mask] += dp[mask ^ (1 << i)];
            }
        }
    }

    // Now dp[mask] contains the sum of all submasks of 'mask'
    cout << dp[limit - 1] << endl;
    return 0;
}