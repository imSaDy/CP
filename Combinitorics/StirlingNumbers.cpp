#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - S2(n, k): Partition n distinct items into k identical non-empty sets.
   - Bell(n): Total ways to partition n distinct items.
   - Complexity: O(N*K) Precomputation.
*/

const int MAXN = 1005;
const int MOD = 1e9 + 7;

long long S2[MAXN][MAXN]; // Stirling 2nd Kind
long long B[MAXN];        // Bell Numbers

void build_stirling() {
    S2[0][0] = 1;
    for (int n = 1; n < MAXN; n++) {
        for (int k = 1; k <= n; k++) {
            // Recurrence:
            // 1. Item n forms its own new set: S(n-1, k-1)
            // 2. Item n joins one of the k existing sets: k * S(n-1, k)
            S2[n][k] = (S2[n - 1][k - 1] + k * S2[n - 1][k]) % MOD;
        }
    }
}

void build_bell() {
    // Bell(n) = Sum of S(n, k) for k=0..n
    for (int n = 0; n < MAXN; n++) {
        B[n] = 0;
        for (int k = 0; k <= n; k++) {
            B[n] = (B[n] + S2[n][k]) % MOD;
        }
    }
}

int main() {
    build_stirling();
    build_bell();
    
    int n = 4, k = 2;
    // Ways to put {1,2,3,4} into 2 identical groups:
    // {1,2,3}{4}, {1,2,4}{3}, {1,3,4}{2}, {2,3,4}{1} -> 4 ways
    // {1,2}{3,4}, {1,3}{2,4}, {1,4}{2,3} -> 3 ways
    // Total 7.
    cout << "S(4, 2): " << S2[4][2] << endl;
    
    // Total partitions of {1,2,3} -> 5
    // {1,2,3}, {1,2}{3}, {1,3}{2}, {2,3}{1}, {1}{2}{3}
    cout << "Bell(3): " << B[3] << endl;
    
    return 0;
}