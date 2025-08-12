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

struct BipartiteMatching {
    int n, m; // sizes of left and right sets
    vector<vector<int>> g;
    vector<int> dist, matchL, matchR;

    BipartiteMatching(int n, int m) : n(n), m(m), g(n + 1), dist(n + 1), matchL(n + 1, -1), matchR(m + 1, -1) {}

    void add_edge(int u, int v) {
        // Add edge from left node u to right node v (both 1-based)
        g[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (matchL[i] == -1) {
                dist[i] = 0;
                q.push(i);
            } else {
                dist[i] = INT_MAX;
            }
        }
        bool found = false;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                int w = matchR[v];
                if (w == -1) {
                    found = true;
                } else if (w != -1 && dist[w] == INT_MAX) {
                    dist[w] = dist[u] + 1;
                    q.push(w);
                }
            }
        }
        return found;
    }

    bool dfs(int u) {
        for (int v : g[u]) {
            int w = matchR[v];
            if (w == -1 || (dist[w] == dist[u] + 1 && dfs(w))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = INT_MAX;
        return false;
    }

    int max_matching() {
        int matching = 0;
        while (bfs()) {
            for (int i = 1; i <= n; i++) {
                if (matchL[i] == -1 && dfs(i)) {
                    matching++;
                }
            }
        }
        return matching;
    }
};

/*
Time Complexity:
- Hopcroft-Karp algorithm runs in O(sqrt(V) * E) time,
  where V = number of vertices (n + m),
  and E = number of edges.
- This is efficient for large bipartite graphs.
*/

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    int n, m, k; 
    cin >> n >> m >> k; 
    BipartiteMatching bm(n, m);
    for (int i = 1; i <= k; i++){
        int u, v; 
        cin >> u >> v; 
        bm.add_edge(u, v);
    }
    cout << bm.max_matching() << endl; 
    for (int i = 1; i <= n; i++){
        if (bm.matchL[i] != -1){
            cout << i << " " << bm.matchL[i] << endl;
        }
    }
    return 0;
}



