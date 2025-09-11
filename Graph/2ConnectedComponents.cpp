#include <bits/stdc++.h> 

using namespace std ; 
/*
template<typename T> using vc=vector<T>;
template<typename T> using vvc=vc<vc<T>>;
template<typename T> using vvvc=vc<vvc<T>>;

using vi=vc<int>;
using vll=vc<ll>;
using vvi=vc<vi>;
using vvll=vc<vll>;*/

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
const int MOD = 998244353;
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
#define F                      first
#define S                      second
#define pb 					   push_back
#define ppb                    pop_back 
#define all(v)                 v.begin() ,v.end() 
#define len(v)                 (int) v.size()
#define uniq(v)                v.resize(unique(all(v)) - v.begin());
#define rep1(n) for(ll i=0; i<(ll)(n); ++i)
#define rep2(i,n) for(ll i=0; i<(ll)(n); ++i)
#define rep3(i,a,b) for(ll i=(ll)(a); i<(ll)(b); ++i)
#define rep4(i,a,b,c) for(ll i=(ll)(a); i<(ll)(b); i+=(c))
#define cut4(a,b,c,d,e,...) e
#define rep(...) cut4(__VA_ARGS__,rep4,rep3,rep2,rep1)(__VA_ARGS__)
#define per1(n) for(ll i=((ll)n)-1; i>=0; --i)
#define per2(i,n) for(ll i=((ll)n)-1; i>=0; --i)
#define per3(i,a,b) for(ll i=((ll)a)-1; i>=(ll)(b); --i)
#define per4(i,a,b,c) for(ll i=((ll)a)-1; i>=(ll)(b); i-=(c))
#define per(...) cut4(__VA_ARGS__,per4,per3,per2,per1)(__VA_ARGS__)
#define rep_subset(i,s) for(ll i=(s); i>=0; i=(i==0?-1:(i-1)&(s)))

template<typename T> using min_heap=priority_queue<T,vector<T>,greater<T>>;
template<typename T> using max_heap=priority_queue<T>;

const int maxn = 4e5 + 2; 
const int mod = 1e9 + 7;
const int inf = 1e9 + 1;
const int alp = 31; 
const int lg = 12; 
const ll INF = 1e17; 
const int sq = 700;

vector <vp> g; 
vi vc; 
int n, m, a[maxn], back[maxn], h[maxn]; 
bool mark[maxn]; 
bool vis[maxn];

void dfs(int u, int par = -1, int edge = 0){
    vis[u] = true;
    back[u] = h[u];  
    for (auto [v, i] : g[u]){
        if (!vis[v]){
            h[v] = h[u] + 1; 
            dfs(v, u, i);
            back[u] = min(back[u], back[v]);
        }
        else if (v == par) continue;
        else {
            back[u] = min(back[u], h[v]);
        }
    }
    if (back[u] == h[u]){
        mark[edge] = true; 
    }
}

bool dfs2(int u, int p = -1){
    vis[u] = true;
    vc.pb(a[u]);
    bool ret = false;
    for (auto [v, i] : g[u]){
        if (mark[i]) continue; 
        if (v == p) continue; 
        if (vis[v] && (h[v] % 2) == (h[u] % 2)){
            ret = true; 
        }
        else if (!vis[v]){
            h[v] = h[u] + 1;
            ret |= dfs2(v, u);
        }
    }
    return ret;
}

void Main(){
    int v; 
    cin >> n >> m >> v; 
    g.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i]; 
    for (int i = 1; i <= m; i++){
        int u, v; 
        cin >> u >> v; 
        g[u].pb({v, i});
        g[v].pb({u, i});
    }
    for (int i = 1; i <= n; i++){
        if (!vis[i])
            dfs(i);
    }
    fill(vis, vis + n + 1, false);
    fill(h, h + n + 1, 0);
    Mint ans = 1; 
    for (int i = 1; i <= n; i++){
        if (!vis[i]){
            vc.clear();
            bool odd = dfs2(i);
            sort(all(vc));
            if (vc.back() == -1){
                if (!odd){
                    ans *= v; 
                }
            }
            else {
                vi tmp = vc; 
                uniq(tmp);
                int cnt = 0; 
                for (auto x : tmp){
                    cnt += (x != -1);
                }
                if (cnt >= 2){
                    ans = 0; 
                }
                else {
                    if (odd && tmp.back() != 0){
                        ans = 0; 
                    }
                }
            }
        }
    }
    cout << ans << endl; 
    g.clear();
    for (int i = 1; i <= max(n, m); i++){
        mark[i] = false; 
        vis[i] = false; 
        h[i] = 0; 
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int tc = 1; 
    cin >> tc;
    while (tc--){
        Main();
    }
    return 0;
}