#include <bits/stdc++.h> 

using namespace std ; 

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

const int maxn = 2e5 + 2; 
const int mod = 1e9 + 7;
const int inf = 1e9 + 1;
const int alp = 31; 
const ll INF = 1e17; 

int r, c;
int chess[9][9];

int dx[8] = {2, 2, -2, -2, 1, -1, 1, -1};
int dy[8] = {1, -1, 1, -1, 2, 2, -2, -2};

bool vis[9][9];

bool valid(int x){
    return 0 < x && x < 9;
}

int count(int r, int c){
    int ret = 0;
    for (int i = 0; i < 8; i++){
        int nr = r + dx[i]; 
        int nc = c + dy[i];
        if (valid(nr) && valid(nc) && !vis[nr][nc]){
            ret++;
        }
    }
    return ret;
}

bool dfs(int r, int c, int move = 1){
    chess[r][c] = move;
    if (move == 64)
        return true; 
    vis[r][c] = true;
    vector <pip> v; 
    for (int i = 0; i < 8; i++){
        int nr = r + dx[i]; 
        int nc = c + dy[i];
        if (valid(nr) && valid(nc) && !vis[nr][nc]){
            v.pb({count(nr, nc), {nr, nc}});
        }
    }
    sort(all(v));
    for (auto [cnt, p] : v){
        auto [nr, nc] = p;
        if (dfs(nr, nc, move + 1))
            return true;
    }
    vis[r][c] = false; 
    return false;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> c >> r; 
    dfs(r, c);
    for (int i = 1; i < 9; i++){
        for (int j = 1; j < 9; j++){
            cout << chess[i][j] << " "; 
        }
        cout << endl; 
    }
}

/*
    Heuristic Minimal options leads to O(n^3)
*/

