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

int n, m, k, cnt[maxn];
vvp g;

void dijkstra(){
    minheap pq; 
    pq.push({0, 1});
    vll ans;
    while (!pq.empty()){
        auto [d, u] = pq.top();
        pq.pop();
        if (cnt[u] == 10)
            continue; 
        cnt[u]++;
        if (u == n){
            if (len(ans) == k)
                break;
            ans.pb(d);
        }
        for (auto [v, w] : g[u]){
            if (cnt[v] < 10){
                pq.push({w + d, v});
            }
        }
    }
    for (auto x : ans){
        cout << x << " ";
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> n >> m >> k;
    g.resize(n + 1);
    for (int i = 0; i < m; i++){
        int u, v, w; 
        cin >> u >> v >> w;
        g[u].pb({v, w});
    }
    dijkstra();
}


