#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Convert "At Least K" counts to "Exactly K" counts.
   - S[i] = Sum of ways to satisfy subset of size i (others arbitrary).
   - Ans[k] = Sum_{j=k to N} (-1)^(j-k) * nCr(j, k) * S[j]
*/

const int MOD = 1e9 + 7;
const int MAXN = 2005;

long long C[MAXN][MAXN]; // nCr table
long long S[MAXN];       // S[i] values (Problem specific)
long long Exact[MAXN];   // The result

void build_nCr() {
    for (int i = 0; i < MAXN; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
}

int main() {
    build_nCr();
    int n = 100;

    // 1. Calculate S[i] based on problem
    // Example: Permutations with exactly K fixed points.
    // S[i] = Ways to fix specific i elements * Ways to arrange rest
    // S[i] = nCr(n, i) * (n - i)!  <-- This is actually n! / i! ? 
    // Wait, standard definition of S_i in this formula is slightly different context.
    // Let's use the definition: S[i] = sum over all subsets J of size i, of N(J)
    // where N(J) is items having properties in J.
    // For Fixed points: Choose i points. Fix them. (n-i)! ways for rest.
    // S[i] = C[n][i] * fact[n-i] = n! / i!
    
    // 2. Apply Formula
    // Calculate Exactly K for all K
    for (int k = 0; k <= n; k++) {
        long long ans = 0;
        for (int i = k; i <= n; i++) {
            long long term = (C[i][k] * S[i]) % MOD;
            if ((i - k) % 2 == 1)
                ans = (ans - term + MOD) % MOD;
            else
                ans = (ans + term) % MOD;
        }
        Exact[k] = ans;
    }
    
    return 0;
}