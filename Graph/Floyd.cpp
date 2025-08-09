#include <bits/stdc++.h> 

using namespace std ; 

typedef long long ll ; 
typedef pair<int, int> pii; 
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

const int maxn = 5e2 + 2; 
const int mod = 1e9 + 7;
const int inf = 1e9 + 1;
const int alp = 1e5 + 2; 
const ll INF = 1e17; 

int n, m, q; 
ll dist[maxn][maxn];

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> n >> m >> q; 
    for (int i = 0; i <= n; i++){
        fill(dist[i], dist[i] + maxn, INF);
    }
    for (int i = 0; i < m; i++){
        int u, v; 
        ll w; 
        cin >> u >> v >> w; 
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w); 
    }
    for (int i = 1; i <= n; i++){
        dist[i][i] = 0;
    }
    for (int k = 1; k <= n; k++){
        for (int u = 1; u <= n; u++){
            for (int v = 1; v <= n; v++){
                dist[u][v] = min(dist[u][v], dist[u][k] + dist[k][v]);
            }
        }
    }
    for (int i = 0; i < q; i++){
        int u, v; 
        cin >> u >> v;
        if (dist[u][v] == INF){
            cout << "-1" << endl; 
            continue;
        }
        cout << dist[u][v] << endl; 
    }
}


