#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Calculate nCr % P.
   - Handles Large N (10^18) if P is small (< 10^5).
   - Handles Large P (10^9+7) if N is small (< 10^6) via init().
*/

typedef long long ll;

// CHANGE THIS depending on problem
const int MOD = 1000003; // Example small prime for Lucas
const int MAXN = 100005; // For precompute

ll fact[MAXN], invFact[MAXN];

ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

ll modInverse(ll n) {
    return power(n, MOD - 2);
}

// O(N) Precomputation
void init() {
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = modInverse(fact[i]);
    }
}

// Standard nCr for small N, K
ll nCr(ll n, ll k) {
    if (k < 0 || k > n) return 0;
    return (((fact[n] * invFact[k]) % MOD) * invFact[n - k]) % MOD;
}

// Lucas Theorem: nCr % P for HUGE n, k (P must be small prime)
ll lucas(ll n, ll k) {
    if (k == 0) return 1;
    // Extract last digits in base MOD
    return (lucas(n / MOD, k / MOD) * nCr(n % MOD, k % MOD)) % MOD;
}

int main() {
    init();
    
    // Example: 100 Choose 5 mod 1000003
    cout << nCr(100, 5) << endl; 
    
    // Example: 10^18 Choose 10^15 mod 1000003
    // Note: Ensure MOD is small enough for array bounds in init()
    long long huge_n = 1e18;
    long long huge_k = 1e15;
    cout << lucas(huge_n, huge_k) << endl;
    
    return 0;
}