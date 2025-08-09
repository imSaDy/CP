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

const int maxn = 1e5 + 2; 
const int mod = 1e9 + 7;
const int inf = 1e9 + 1;
const int alp = 1e5 + 2; 
const ll INF = 1e17; 

int n, m, deg[maxn], dp[maxn], par[maxn]; 
vvi g; 

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
            if (dp[u] && (!par[v] || dp[par[v]] < dp[u])){
                par[v] = u;
                dp[v] = dp[u] + 1;
            }
        }
    }
    if (!dp[n]){
        cout << "IMPOSSIBLE" << endl; 
    }
    else {
        cout << dp[n] << endl; 
        vi ans; 
        int cur = n; 
        ans.pb(n);
        while (cur != 1){
            cur = par[cur];
            ans.pb(cur);
        }
        while(!ans.empty()){
            cout << ans.back() << " ";
            ans.ppb();
        }
    }
}


