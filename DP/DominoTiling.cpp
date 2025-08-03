#include <bits/stdc++.h> 

using namespace std ; 

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


typedef long long ll ; 
typedef pair<int, int> pii; 
typedef pair<ll, ll> pll; 
typedef long double ld; 
typedef vector <int> vi;
typedef vector <ll> vll;
typedef vector <vi> vvi; 
typedef vector <pii> vp;
typedef vector <pair<pii, int>> vpi;
typedef vector <pair<pii, ll>> vpl;
typedef vector <bool> vb;
typedef vector <vb> vvb;
typedef vector <vp> vvp;

void debug_out() { cerr << endl; }
 
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
	cerr << " " << H ;
	debug_out(T...);
}

template <typename T>
inline T lowbit(T x) { return x & -x; }

#define debug(...)             cerr << "(" << #__VA_ARGS__ << "): ", debug_out(__VA_ARGS__)
#define hey                    cerr << "Ey BABA!\n"
#define MP                     make_pair
#define F                     first
#define S                     second
#define pb 					   push_back
#define ppb                    pop_back 
#define all(v)                 v.begin() ,v.end() 
#define len(v)                 (int) v.size()
#define uniq(v)                 v.resize(unique(all(v)) - v.begin());

const int maxn = 2e5 + 2; 
const int mod = 1e9 + 7;
const int inf = 1e9 + 1;
const int alp = 1e5 + 2; 
const ll INF = 1e18; 

vvi adj; 

int n, m; 

void precalc(int cur, int nxt, int row, vi& ret){
    if (row == n){
        ret.pb(nxt);
        return; 
    }
    if (cur & (1 << row)){
        precalc(cur, nxt, row + 1, ret);
        return;
    }
    if (row + 1 < n && !(cur & (1 << (row + 1)))){
        precalc(cur + (1 << row) + (1 << (row + 1)), nxt, row + 2, ret);
    }
    precalc(cur + (1 << row), nxt + (1 << row), row + 1, ret);
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> n >> m;
    adj.resize(1 << n);
    for (int mask = 0; mask < (1 << n); mask++){
        precalc(mask, 0, 0, adj[mask]);
    }

    vector <Mint> dp(1 << n, 0);
    dp[0] = 1;
    for (int col = 0; col < m; col++){
        vector <Mint> ndp(1 << n, 0);
        for (int mask = 0; mask < (1 << n); mask++){
            for (auto nxt : adj[mask]){
                ndp[nxt] += dp[mask]; 
            }
        }
        dp.swap(ndp);
    } 
    cout << dp[0]; 
}


