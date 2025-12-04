#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Multiply two polynomials in O(N log N).
   - Combinatorics: Count ways to form sum S using two arrays.
   - MOD must be 998244353 (or other NTT-friendly primes).
   - 998244353 = 119 * 2^23 + 1. Primitive Root = 3.
*/

const int MOD = 998244353;
const int G = 3;

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

void ntt(vector<long long>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    
    for (int len = 2; len <= n; len <<= 1) {
        long long wlen = power(G, (MOD - 1) / len);
        if (invert) wlen = modInverse(wlen);
        
        for (int i = 0; i < n; i += len) {
            long long w = 1;
            for (int j = 0; j < len / 2; j++) {
                long long u = a[i + j];
                long long v = (a[i + j + len / 2] * w) % MOD;
                a[i + j] = (u + v < MOD ? u + v : u + v - MOD);
                a[i + j + len / 2] = (u - v >= 0 ? u - v : u - v + MOD);
                w = (w * wlen) % MOD;
            }
        }
    }

    if (invert) {
        long long n_inv = modInverse(n);
        for (long long& x : a) x = (x * n_inv) % MOD;
    }
}

vector<long long> multiply(vector<long long> const& a, vector<long long> const& b) {
    vector<long long> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    
    fa.resize(n); fb.resize(n);
    ntt(fa, false);
    ntt(fb, false);
    
    for (int i = 0; i < n; i++) fa[i] = (fa[i] * fb[i]) % MOD;
    
    ntt(fa, true);
    
    // Result might have trailing zeros or size N
    // Trim if needed, or just return relevant part
    return fa;
}

int main() {
    // Problem: You have bag A {1, 2} and bag B {2, 3}.
    // Ways to get sum S picking one from A and one from B.
    // Poly A: x^1 + x^2 -> Coeffs: [0, 1, 1]
    // Poly B: x^2 + x^3 -> Coeffs: [0, 0, 1, 1]
    
    vector<long long> A = {0, 1, 1};
    vector<long long> B = {0, 0, 1, 1};
    
    vector<long long> res = multiply(A, B);
    
    // Expected: 1+2=3, 1+3=4, 2+2=4, 2+3=5.
    // Sums: 3 (1 way), 4 (2 ways), 5 (1 way).
    // Result vector indices: 0, 1, 2, 3, 4, 5...
    
    for(int i=0; i<res.size(); i++) {
        if(res[i] > 0) cout << "Sum " << i << ": " << res[i] << " ways" << endl;
    }
    
    return 0;
}