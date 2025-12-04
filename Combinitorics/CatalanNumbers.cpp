#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Count valid parentheses, binary trees, polygon triangulations.
   - Formula: (1 / (n+1)) * nCr(2n, n).
   - Sequence: 1, 1, 2, 5, 14, 42, 132...
*/

typedef long long ll;
const int MOD = 1e9 + 7;
const int MAXN = 200005;

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

void init() {
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = modInverse(fact[i]);
    }
}

ll nCr(ll n, ll k) {
    if (k < 0 || k > n) return 0;
    return (((fact[n] * invFact[k]) % MOD) * invFact[n - k]) % MOD;
}

ll catalan(int n) {
    // C_n = nCr(2n, n) * (n+1)^-1
    ll res = nCr(2 * n, n);
    res = (res * modInverse(n + 1)) % MOD;
    return res;
}

int main() {
    init();
    int n = 3;
    // Valid parens size 2*3=6: ((())), (())(), ()()(), ()(()), (()()) -> 5
    cout << catalan(3) << endl;
    return 0;
}