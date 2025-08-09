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
typedef pair<pii, int> ppi;
typedef pair<ll, pii> pip;
typedef pair<ll, ll> pll; 
typedef long double ld; 
typedef vector <int> vi;
typedef vector <ll> vll;
typedef vector <vi> vvi; 
typedef vector <pii> vp;
typedef vector <pll> vpl;
typedef vector <pair<pii, int>> vpi;
typedef vector <pair<pii, ll>> vppl;
typedef vector <bool> vb;
typedef vector <char> vch; 
typedef vector <vb> vvb;
typedef vector <vp> vvp;
typedef vector <vll> vvll;
typedef priority_queue <pll, vpl, greater<pll>> minheap; 

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

const int maxn = 1e5 + 2; 
const int mod = 1e9 + 7;
const int inf = 1e9 + 1;
const int alp = 1e5 + 2; 
const ll INF = 1e17; 

int n, m, deg[maxn], par[maxn]; 
vvi g; 
Mint dp[maxn];

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> n >> m;
    g.resize(n + 1);
    for (int i = 0; i < m; i++){
        int u, v; 
        cin >> u >> v;
        g[u].pb(v);
        deg[v]++;
    }
    vi vc; 
    for (int i = 0; i < n; i++){
        if (deg[i + 1] == 0){
            vc.pb(i + 1);
        }
    }
    dp[1] = 1; 
    while (!vc.empty()){
        int u = vc.back(); 
        vc.ppb();
        for (auto v : g[u]){
            deg[v]--; 
            if (!deg[v]){
                vc.pb(v);
            }
            dp[v] += dp[u];
        }
    }
    cout << dp[n] << endl; 
}


