#include <bits/stdc++.h>
using namespace std;

// Modular integer struct
template<int MOD, int RT> struct mint {
    static const int mod = MOD;
    int v; // Value in [0, MOD)
    
    // Constructor
    mint() : v(0) {}
    mint(long long _v) {
        v = int((-MOD < _v && _v < MOD) ? _v : _v % MOD);
        if (v < 0) v += MOD;
    }
    
    // Explicit conversion to int
    explicit operator int() const { return v; }
    
    // Arithmetic operations
    mint& operator+=(const mint& m) {
        if ((v += m.v) >= MOD) v -= MOD;
        return *this;
    }
    mint& operator-=(const mint& m) {
        if ((v -= m.v) < 0) v += MOD;
        return *this;
    }
    mint& operator*=(const mint& m) {
        v = int((long long)v * m.v % MOD);
        return *this;
    }
    mint& operator/=(const mint& m) {
        return (*this) *= inv(m);
    }
    
    // Unary negation
    mint operator-() const { return mint(-v); }
    
    // Binary operators
    friend mint operator+(mint a, const mint& b) { return a += b; }
    friend mint operator-(mint a, const mint& b) { return a -= b; }
    friend mint operator*(mint a, const mint& b) { return a *= b; }
    friend mint operator/(mint a, const mint& b) { return a /= b; }
    
    // Comparison operators
    friend bool operator==(const mint& a, const mint& b) { return a.v == b.v; }
    friend bool operator!=(const mint& a, const mint& b) { return a.v != b.v; }
    friend bool operator<(const mint& a, const mint& b) { return a.v < b.v; }
    
    // Exponentiation
    friend mint pow(mint a, long long p) {
        mint ans = 1;
        assert(p >= 0);
        for (; p; p /= 2, a *= a) if (p & 1) ans *= a;
        return ans;
    }
    
    // Modular inverse (using Fermat's little theorem for prime MOD)
    friend mint inv(const mint& a) {
        assert(a.v != 0);
        return pow(a, MOD - 2);
    }
    
    // Output
    friend ostream& operator<<(ostream& os, const mint& a) { return os << a.v; }
    
    // Input
    friend istream& operator>>(istream& is, mint& a) {
        long long x;
        is >> x;
        a = mint(x);
        return is;
    }
};

// Common moduli
const int MOD = 1e9 + 7; // or 998244353
using Mint = mint<MOD, 5>; // 5 is a primitive root for common moduli

vector<Mint> fact(1, 1);
vector<Mint> invfact(1, 1);
 
Mint C(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    while ((int) fact.size() < n + 1) {
        fact.push_back(fact.back() * (int) fact.size());
        invfact.push_back(1 / fact.back());
    }
    return fact[n] * invfact[k] * invfact[n - k];
}

// Example usage
int main() {
    Mint a = 2, b = 3;
    cout << a + b << endl; // (2 + 3) % MOD = 5
    cout << a * b << endl; // (2 * 3) % MOD = 6
    cout << pow(a, 10) << endl; // (2^10) % MOD
    cout << a / b << endl; // (2 * b^-1) % MOD, where b^-1 is modular inverse
    return 0;
}