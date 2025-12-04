#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Calculate P(n) modulo M given y_0, y_1, ..., y_k.
   - P(x) is a polynomial of degree k.
   - n can be huge (10^18), k must be small (10^3 - 10^5).
   - Time Complexity: O(k) (assuming y_i are precalculated).
   
   FORMULA:
   P(n) = Sum_{i=0}^k y_i * L_i(n)
   L_i(n) = product_{j!=i} (n - j) / (i - j)
   
   OPTIMIZATION:
   We precompute prefix and suffix products of (n - j) to compute numerators in O(1).
   Denominator is (-1)^(k-i) * i! * (k-i)!
*/

const int MOD = 1e9 + 7;
const int MAX_DEG = 5005; // Maximum Degree K

long long fact[MAX_DEG], invFact[MAX_DEG];

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

void init() {
    fact[0] = 1;
    invFact[0] = 1;
    for (int i = 1; i < MAX_DEG; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = modInverse(fact[i]);
    }
}

// Given y values at x = 0, 1, ..., k. Find value at x = n.
long long lagrange(const vector<long long>& y, long long n) {
    int k = y.size() - 1;
    
    // If n is small, just return the precomputed value
    if (n <= k) return y[n];

    // Precompute prefix and suffix products of (n - i)
    // pref[i] = (n-0) * (n-1) * ... * (n-(i-1))
    vector<long long> pref(k + 1), suff(k + 1);
    
    pref[0] = 1;
    for (int i = 0; i < k; i++) {
        pref[i + 1] = (pref[i] * ((n - i) % MOD)) % MOD;
    }
    
    suff[k] = 1;
    for (int i = k; i > 0; i--) {
        suff[i - 1] = (suff[i] * ((n - i) % MOD)) % MOD;
    }

    long long ans = 0;
    for (int i = 0; i <= k; i++) {
        // Numerator: product_{j!=i} (n - j) = pref[i] * suff[i]
        long long num = (pref[i] * suff[i]) % MOD;
        
        // Denominator: i! * (-1)^(k-i) * (k-i)!
        long long den = (invFact[i] * invFact[k - i]) % MOD;
        
        long long term = (y[i] * num) % MOD;
        term = (term * den) % MOD;
        
        if ((k - i) % 2 == 1) {
            ans = (ans - term + MOD) % MOD;
        } else {
            ans = (ans + term) % MOD;
        }
    }
    return ans;
}

int main() {
    init();
    
    // Example: Sum of squares 1^2 + 2^2 + ... + N^2
    // This is a polynomial of degree 3. We need 3+1 = 4 points.
    // y_0 = 0
    // y_1 = 1
    // y_2 = 5 (1+4)
    // y_3 = 14 (1+4+9)
    vector<long long> y = {0, 1, 5, 14};
    
    long long N = 1000000000000LL;
    
    // Formula check: N(N+1)(2N+1)/6
    // Works in O(K) without knowing the formula!
    cout << lagrange(y, N) << endl;
    
    return 0;
}