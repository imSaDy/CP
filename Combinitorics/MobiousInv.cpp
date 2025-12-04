#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Count pairs (i, j) in [1..N]x[1..M] such that gcd(i, j) = 1.
   - Formula: Sum( mu[d] * (N/d) * (M/d) ) for d from 1 to min(N, M).
   - If looking for gcd(i, j) = K, just solve for N/K, M/K with gcd=1.
*/

const int MAXN = 1000005;
int mu[MAXN];
vector<int> primes;
bool is_prime[MAXN];

// Linear Sieve to precompute Mobius Function O(N)
void sieve() {
    fill(is_prime, is_prime + MAXN, true);
    is_prime[0] = is_prime[1] = false;
    mu[1] = 1;
    
    for (int i = 2; i < MAXN; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            mu[i] = -1; // Prime has 1 factor, (-1)^1
        }
        for (int p : primes) {
            if (i * p >= MAXN) break;
            is_prime[i * p] = false;
            
            if (i % p == 0) {
                mu[i * p] = 0; // Contains square factor p^2
                break;
            } else {
                mu[i * p] = -mu[i]; // Multiply by distinct prime
            }
        }
    }
}

long long count_coprime_pairs(int n, int m) {
    long long ans = 0;
    int limit = min(n, m);
    for (int d = 1; d <= limit; d++) {
        if (mu[d] == 0) continue;
        ans += (long long)mu[d] * (n / d) * (m / d);
    }
    return ans;
}

int main() {
    sieve();
    
    // Count pairs (x, y) with 1 <= x <= 10, 1 <= y <= 10 such that gcd(x, y) = 1
    // E.g., (2,3) is ok, (2,4) is not.
    cout << count_coprime_pairs(10, 10) << endl; // Should be 63 (approx 6/pi^2 * N^2)
    
    return 0;
}