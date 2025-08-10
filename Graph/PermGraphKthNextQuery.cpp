#include <bits/stdc++.h> 
 
using namespace std ; 

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
 
int n, q, go[maxn], dp[alp][maxn];
vvi path, cyc;
vvi gin;
 
int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> n >> q;
    gin.resize(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> dp[0][i]; 
    }
    for (int i = 1; i < alp; i++){
        for (int j = 1; j <= n; j++){
            dp[i][j] = dp[i - 1][dp[i - 1][j]];
        }
    }
    while (q--){
        int u, k;
        cin >> u >> k;
        int cnt = 0; 
        while (k){
            if (k & 1){
                u = dp[cnt][u];
            }
            cnt++; 
            k >>= 1;
        }
        cout << u << endl; 
    }
}