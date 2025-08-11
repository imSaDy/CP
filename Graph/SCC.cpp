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

struct SCC {
    int n, compCount;
    vector<vector<int>> g, gr, dag;
    vector<int> comp, order, used;

    SCC(int n) : n(n) {
        g.assign(n + 1, {});
        gr.assign(n + 1, {});
        comp.assign(n + 1, -1);
        used.assign(n + 1, 0);
        compCount = 0;
    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        gr[v].push_back(u);
    }

    void dfs1(int v) {
        used[v] = 1;
        for (int to : g[v]) if (!used[to]) dfs1(to);
        order.push_back(v);
    }

    void dfs2(int v, int cid) {
        comp[v] = cid;
        for (int to : gr[v]) if (comp[to] == -1) dfs2(to, cid);
    }

    void build() {
        order.clear();
        fill(used.begin(), used.end(), 0);
        fill(comp.begin(), comp.end(), -1);

        for (int i = 1; i <= n; i++) {
            if (!used[i]) dfs1(i);
        }

        reverse(order.begin(), order.end());
        compCount = 0;
        for (int v : order) {
            if (comp[v] == -1) {
                dfs2(v, ++compCount);
            }
        }
        // condensate dag
        dag.assign(compCount + 1, {});
        vector<unordered_set<int>> seen(compCount + 1);

        for (int u = 1; u <= n; u++) {
            for (int v : g[u]) {
                if (comp[u] != comp[v] && !seen[comp[u]].count(comp[v])) {
                    dag[comp[u]].push_back(comp[v]);
                    seen[comp[u]].insert(comp[v]);
                }
            }
        }
    }
};

int n, m;

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> n >> m;
    SCC scc(n);
    for (int i = 0; i < m; i++){
        int u, v; 
        cin >> u >> v; 
        scc.add_edge(u, v);
    }
    scc.build();
    if (scc.compCount == 1){
        cout << "YES";
    }   
}


