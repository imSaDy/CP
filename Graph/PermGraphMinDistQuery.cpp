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

int n, q, go[maxn], dp[alp][maxn], deg[maxn], idcyc[maxn], ind[maxn], h[maxn], sz[maxn];
bool incyc[maxn], vis[maxn];
vvi path, cyc;
vvi gin;

void findcyc(int u, int color){
    sz[color]++;
    idcyc[u] = color; 
    if (!idcyc[go[u]]){
        ind[go[u]] = ind[u] + 1; 
        findcyc(go[u], color);
    }
}

void dfs(int u, int par = 0){
    //debug(u, par, h[u]);
    dp[0][u] = par;
    int dep = 1; 
    while (dp[dep - 1][u]){
        dp[dep][u] = dp[dep - 1][dp[dep - 1][u]];
        dep++;
    }
    for (auto v : gin[u]){
        if (!incyc[v]){
            h[v] = h[u] + 1;
            dfs(v, u);
        }
    }
}

int go_down(int u, int k){
    int dep = 0; 
    while (k){
        if (k & 1){
            u = dp[dep][u]; 
        }
        dep++;
        k >>= 1;
    }
    return u;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> n >> q;
    gin.resize(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> go[i];
        gin[go[i]].pb(i); 
    }
    fill(incyc, incyc + maxn, 1);
    vi vc; 
    for (int i = 1; i <= n; i++){
        deg[i] = len(gin[i]);
        if (gin[i].empty()){
            vc.pb(i);
        }
    }
    while (!vc.empty()){
        int u = vc.back();
        vc.ppb();
        incyc[u] = false; 
        deg[go[u]]--; 
        if (deg[go[u]] == 0){
            vc.pb(go[u]);
        }
    }
    int newcyc = 0; 
    for (int i = 1; i <= n; i++){
        if (incyc[i] && !idcyc[i]){
            newcyc++;
            findcyc(i, newcyc);
        }
    }
    for (int i = 1; i <= n; i++){
        if (incyc[i]){
            dfs(i);
        }
    }
    while (q--){
        int a, b; 
        cin >> a >> b;
        if (a == b){
            cout << 0 << endl; 
            continue;
        }
        if (incyc[a] && !incyc[b]){
            cout << -1 << endl; 
            continue; 
        }
        if (!incyc[a] && !incyc[b]){
            if (h[a] <= h[b]){
                cout << -1 << endl; 
                continue;
            }
            int c = go_down(a, h[a] - h[b]);
            cout << (c == b ? h[a] - h[b] : -1) << endl; 
        }
        if (incyc[b]){
            int c = go_down(a, h[a]);
            if (idcyc[c] != idcyc[b]){
                cout << -1 << endl; 
                continue;
            }
            int dif = 0;
            if (ind[c] <= ind[b]){
                dif = ind[b] - ind[c];
            }
            else {
                dif = sz[idcyc[c]] - ind[c] + ind[b];
            }
            cout << h[a] + dif << endl; 
        }
    }
}


