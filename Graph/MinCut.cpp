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

struct Edge {
    int to, rev;
    long long cap;
};


struct MinCut {
    int n;
    vector<vector<Edge>> g;
    vector<int> level, ptr;
    vector<bool> visited;

    MinCut(int n) : n(n), g(n + 1), level(n + 1), ptr(n + 1), visited(n + 1) {}

    void add_edge(int u, int v, long long cap) {
        g[u].push_back({v, (int)g[v].size(), cap});
        g[v].push_back({u, (int)g[u].size() - 1, 0});
    }

    bool bfs(int s, int t) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q; q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto &e : g[u]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
        return level[t] != -1;
    }

    long long dfs(int u, int t, long long flow) {
        if (u == t || flow == 0) return flow;
        for (int &i = ptr[u]; i < (int)g[u].size(); i++) {
            Edge &e = g[u][i];
            if (level[e.to] == level[u] + 1 && e.cap > 0) {
                long long pushed = dfs(e.to, t, min(flow, e.cap));
                if (pushed > 0) {
                    e.cap -= pushed;
                    g[e.to][e.rev].cap += pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    long long max_flow(int s, int t) {
        long long flow = 0;
        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, t, LLONG_MAX))
                flow += pushed;
        }
        return flow;
    }

    void dfs_reachable(int u) {
        visited[u] = true;
        for (auto &e : g[u]) {
            if (e.cap > 0 && !visited[e.to])
                dfs_reachable(e.to);
        }
    }

    // Returns edges in the min cut as pairs (u, v)
    vector<pair<int,int>> get_min_cut_edges(int s, int t) {
        max_flow(s, t);
        fill(visited.begin(), visited.end(), false);
        dfs_reachable(s);

        vector<pair<int,int>> cut_edges;
        for (int u = 1; u <= n; u++) {
            if (!visited[u]) continue;
            for (auto &e : g[u]) {
                // Check:
                // 1) Edge from reachable to non-reachable vertex
                // 2) Edge is fully saturated in forward direction (capacity zero)
                // 3) This edge is forward edge (not residual backward)
                if (!visited[e.to] && e.cap == 0) {
                    cut_edges.emplace_back(u, e.to);
                }
            }
        }
        return cut_edges;
    }
    
    /*
    Time Complexity:
    - Max Flow (Dinic's Algorithm): O(V^2 * E) worst case, often faster in practice.
    - Min Cut extraction (DFS + edge check): O(V + E).
    Overall complexity dominated by max flow.
    */
};

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, m; 
    cin >> n >> m; 
    MinCut mincut(n);     
    for (int i = 0; i < m; i++){
        int u, v; 
        cin >> u >> v;
        mincut.add_edge(u, v, 1);
        mincut.add_edge(v, u, 1);
    }
    vp ans = mincut.get_min_cut_edges(1, n);
    set<pair<int,int>> fans;
    for (auto [u, v] : ans){
        if (u > v) swap(u, v);
        fans.insert({u, v});
    }
    cout << len(fans) << endl; 
    for (auto [u, v] : fans){
        cout << u << " " << v << endl; 
    }
    return 0;
}



