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

#include <bits/stdc++.h>
using namespace std;

struct Tree {
    int n, LOG;
    vector<vector<int>> adj;
    vector<int> depth, start, finish;
    vector<vector<int>> up;
    int timer;

    Tree(int n) : n(n) {
        LOG = 1;
        while ((1 << LOG) <= n) LOG++;
        adj.assign(n + 1, {});
        depth.assign(n + 1, 0);
        start.assign(n + 1, 0);
        finish.assign(n + 1, 0);
        up.assign(n + 1, vector<int>(LOG, 0));
        timer = 0;
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int v, int p) {
        start[v] = ++timer;
        up[v][0] = p;
        for (int i = 1; i < LOG; i++) {
            if (up[v][i-1] != 0) up[v][i] = up[up[v][i-1]][i-1];
            else up[v][i] = 0;
        }

        for (int u : adj[v]) {
            if (u != p) {
                depth[u] = depth[v] + 1;
                dfs(u, v);
            }
        }
        finish[v] = timer;
    }

    void init(int root = 1) {
        dfs(root, 0);
    }

    int query_lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        u = query_kth_parent(u, depth[u] - depth[v]);
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

    bool is_ancestor(int u, int v) { // check if u is ancestor of v
        return start[u] <= start[v] && finish[v] <= finish[u];
    }
};

template<typename T>
struct Fenwick {
    int n;
    vector<T> bit;
 
    Fenwick(int n) : n(n) {
        bit.assign(n + 1, 0);
    }
 
    void add(int idx, T val) { // 1-based index
        for (; idx <= n; idx += idx & -idx)
            bit[idx] += val;
    }
 
    T sum(int idx) { // prefix sum [1..idx]
        T res = 0;
        for (; idx > 0; idx -= idx & -idx)
            res += bit[idx];
        return res;
    }
 
    T get(int l, int r) { // inclusive
        return sum(r) - sum(l - 1);
    }
};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, q; 
    cin >> n >> q; 
    vi a(n + 1);
    Tree tree(n);
    Fenwick <ll> fen(n);
    for (int i = 1; i <= n; i++){
        cin >> a[i]; 
    }
    for (int i = 1; i < n; i++){
        int u, v; 
        cin >> u >> v; 
        tree.add_edge(u, v);
    }
    tree.init();
    for (int i = 1; i <= n; i++){
        fen.add(tree.start[i], a[i]);
    }
    while (q--){
        int t; 
        cin >> t; 
        if (t == 1){
            int s, x; 
            cin >> s >> x; 
            fen.add(tree.start[s], -a[s]);
            a[s] = x; 
            fen.add(tree.start[s], a[s]);
        }
        else {
            int s; 
            cin >> s; 
            cout << fen.get(tree.start[s], tree.finish[s]) << endl;
        }
    }
    return 0;
}



