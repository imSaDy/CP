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

struct LCA {
    int n, LOG;
    vector<vector<int>> up;
    vector<int> depth;
    vector<vector<int>> adj;

    LCA(int n) : n(n) {
        LOG = 1;
        while ((1 << LOG) <= n) LOG++;
        up.assign(n + 1, vector<int>(LOG, 0));
        depth.assign(n + 1, 0);
        adj.assign(n + 1, {});
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int v, int p) {
        up[v][0] = p;
        for (int i = 1; i < LOG; i++) {
            if (up[v][i - 1] != 0)
                up[v][i] = up[up[v][i - 1]][i - 1];
            else
                up[v][i] = 0;
        }
        for (int u : adj[v]) {
            if (u != p) {
                depth[u] = depth[v] + 1;
                dfs(u, v);
            }
        }
    }

    void init(int root = 1) {
        dfs(root, 0); // parent of root = 0 (non-existent)
    }

    int query_lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);

        int k = depth[u] - depth[v];
        u = query_kth_parent(u, k);

        if (u == v) return u;

        for (int i = LOG - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }

        return up[u][0];
    }

    int query_kth_parent(int node, int k) {
        for (int i = 0; i < LOG; i++) {
            if (k & (1 << i)) {
                node = up[node][i];
                if (node == 0) return -1;
            }
        }
        return node;
    }

    int distance(int u, int v) {
        int lca = query_lca(u, v);
        return depth[u] + depth[v] - 2 * depth[lca];
    }
};


int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, q; 
    cin >> n >> q; 
    LCA lca(n);
    for (int i = 2; i <= n; i++){
        int p; 
        cin >> p; 
        lca.add_edge(i, p);
    }
    lca.init();
    for (int i = 1; i <= q; i++){
        int u, k; 
        cin >> u >> k; 
        cout << lca.query_kth_parent(u, k) << endl;
    }
    return 0;
}



