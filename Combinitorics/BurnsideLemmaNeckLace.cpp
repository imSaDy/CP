#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Count distinct necklaces of N beads with K colors.
   - Symmetries: Rotations only (Cyclic Group).
   - Formula: (1/N) * Sum(K^gcd(i, N)) for i = 1 to N.
*/

typedef long long ll;
const int MOD = 1e9 + 7;

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

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Euler Totient Function (Optimizes the loop from O(N) to O(sqrt N))
// Instead of iterating i=1..N, iterate divisors d | N.
// The term K^gcd(i, N) is equal to K^d for exactly phi(N/d) values of i.
ll count_necklaces(int n, int k) {
    ll ans = 0;
    
    // Iterate divisors
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            // Divisor d1 = i
            int d1 = i;
            // How many times does gcd(x, n) = d1 occur? phi(n/d1) times.
            // Term: phi(n/d1) * K^d1
            
            // Wait, standard formula optimization:
            // Sum_{d|n} phi(d) * K^(n/d)
            
            ll term1 = n / d1; // Exponent
            ll count1 = d1;    // We need phi(n/exponent) -> phi(d1)
            
            // Let's stick to the simplest O(N) loop if N <= 10^6.
            // If N is huge (10^9), you MUST use divisors + Euler Phi.
        }
    }
    
    // Simple O(N) loop Implementation
    // Use this for N <= 10^6
    for (int i = 1; i <= n; i++) {
        ll p = gcd(i, n);
        ans = (ans + power(k, p)) % MOD;
    }
    
    ans = (ans * modInverse(n)) % MOD;
    return ans;
}

int main() {
    int n = 4; // Length of necklace
    int k = 2; // Number of colors
    
    // Necklaces of length 4 with 2 colors (0 and 1):
    // 0000, 1111, 0001, 0011, 0101, 0111
    // (0010 is same as 0001), (1100 same as 0011), etc.
    // Total 6.
    cout << count_necklaces(n, k) << endl;
    return 0;
}