#include <bits/stdc++.h> 

using namespace std ; 

typedef long long ll ; 
typedef pair<int, int> pii; 
typedef pair<pii, int> ppi;
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

const int maxn = 25e2 + 2; 
const int mod = 1e9 + 7;
const int inf = 1e9 + 1;
const int alp = 1e5 + 2; 
const ll INF = 1e17; 

int n, m;
vpi e; 

bool reach[maxn];
vvp g; 

void dfs(int u){
    reach[u] = true; 
    for (auto [v, w] : g[u]){
        if (!reach[v]){
            dfs(v);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> n >> m; 
    g.resize(n + 1);
    for (int i = 0; i < m; i++){
        int u, v, w; 
        cin >> u >> v >> w; 
        e.pb({{u, v}, -w});
        g[v].pb({u, w});
    }
    dfs(n);
    vll dist(n + 1, INF);
    dist[1] = 0;
    for (int i = 0; i < n - 1; i++){
        for (auto [p, w] : e){
            int u, v;
            tie(u, v) = p;
            if (dist[u] != INF && dist[u] + w < dist[v]){
                dist[v] = dist[u] + w;
            }
        }
    }
    bool cycle = false;
    for (auto [p, w] : e){
        int u, v;
        tie(u, v) = p;
        if (dist[u] != INF && dist[u] + w < dist[v] && reach[v]){
            cycle = true;
        }
    }
    cout << (cycle ? -1 : -dist[n]);
}

// dfs is used for checking a negative cycle in the path between 1 and n. also reverting sign for longest path application. 
