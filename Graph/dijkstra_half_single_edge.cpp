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

const int maxn = 25e2 + 2; 
const int mod = 1e9 + 7;
const int inf = 1e9 + 1;
const int alp = 1e5 + 2; 
const ll INF = 1e17; 

int n, m;
vvp g; 

void dijkstra(int src){
    vvll dist(n + 1, vll(2, INF));
    dist[src][0] = 0;
    priority_queue<pip, vector <pip>, greater<pip>> heap;
    heap.push({0, {src, 0}});
    while (!heap.empty()){
        auto [d, p] = heap.top();
        auto [u, s] = p;
        heap.pop();
        if (dist[u][s] < d)
            continue;
        for (auto [v, w] : g[u]){
            if (s == 0){
                if (dist[v][0] > dist[u][0] + w){
                    dist[v][0] = dist[u][0] + w; 
                    heap.push({dist[v][0], {v, 0}});
                }
                if (dist[v][1] > dist[u][0] + w / 2){
                    dist[v][1] = dist[u][0] + w / 2; 
                    heap.push({dist[v][1], {v, 1}});
                }
            }
            else {
                if (dist[v][1] > dist[u][1] + w){
                    dist[v][1] = dist[u][1] + w; 
                    heap.push({dist[v][1], {v, 1}});
                }
            }
        }
    }
    cout << dist[n][1];
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> n >> m; 
    g.resize(n + 1);
    for (int i = 0; i < m; i++){
        int u ,v, w;
        cin >> u >> v >> w;
        g[u].pb({v, w});
    }
    dijkstra(1);
}


