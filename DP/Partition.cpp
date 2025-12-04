#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Split array of N elements into K groups to minimize Total Cost.
   - Transition: dp[k][i] = min(dp[k-1][j] + Cost(j+1, i)) for j < i
   - Reduces O(KN^2) to O(KN log N).
   
   REQUIREMENT:
   - Cost function must satisfy Quadrangle Inequality.
   - Simple check: If opt[i] <= opt[i+1], you can use this.
*/

const int MAXN = 5005;
const int MAXK = 505;
const long long INF = 1e18;

long long dp[MAXK][MAXN];
int a[MAXN];

// Cost of range [L, R] - CHANGE THIS function based on problem
long long cost(int l, int r) {
    // Example: (sum of range)^2 or similar
    // This function must be efficient (O(1) usually, via prefix sums)
    return 0; 
}

// compute dp[k] for range [L, R], knowing optimal split point is in [optL, optR]
void compute(int k, int L, int R, int optL, int optR) {
    if (L > R) return;

    int mid = (L + R) / 2;
    pair<long long, int> best = {INF, -1};

    // Iterate possible split points for 'mid'
    // We only search between optL and min(mid, optR)
    for (int j = optL; j <= min(mid - 1, optR); j++) {
        long long val = dp[k-1][j] + cost(j + 1, mid);
        if (val < best.first) {
            best = {val, j};
        }
    }

    dp[k][mid] = best.first;
    int opt = best.second;

    // Recurse Left (opt range is optL...opt)
    compute(k, L, mid - 1, optL, opt);
    
    // Recurse Right (opt range is opt...optR)
    compute(k, mid + 1, R, opt, optR);
}

int main() {
    int n = 1000, k = 10;
    // Initialize DP base case (k=1 or k=0)
    for (int i = 1; i <= n; i++) dp[0][i] = INF;
    dp[0][0] = 0;

    for (int i = 1; i <= k; i++) {
        compute(i, 1, n, 0, n - 1);
    }
    
    cout << dp[k][n] << endl;
    return 0;
}