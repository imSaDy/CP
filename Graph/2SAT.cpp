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

struct TwoSAT {
    int n;
    vector<vector<int>> g, gr;
    vector<int> comp, order, assignment, used;

    TwoSAT(int vars) : n(vars) {
        g.assign(2 * n + 2, {});
        gr.assign(2 * n + 2, {});
        comp.assign(2 * n + 2, -1);
        used.assign(2 * n + 2, 0);
        assignment.assign(n + 1, 0);
    }

    int var(int x, bool val) { 
        // x in [1..n], val=true means x is true, false means x is false
        return 2 * (x - 1) ^ (!val);
    }

    void add_implication(int a, int b) {
        g[a].push_back(b);
        gr[b].push_back(a);
    }

    void add_or(int x, bool xv, int y, bool yv) {
        add_implication(var(x, !xv), var(y, yv));
        add_implication(var(y, !yv), var(x, xv));
    }

    void dfs1(int v) {
        used[v] = 1;
        for (int u : g[v]) if (!used[u]) dfs1(u);
        order.push_back(v);
    }

    void dfs2(int v, int c) {
        comp[v] = c;
        for (int u : gr[v]) if (comp[u] == -1) dfs2(u, c);
    }

    bool solve() {
        for (int i = 0; i < 2 * n; i++)
            if (!used[i]) dfs1(i);
        reverse(order.begin(), order.end());
        int j = 0;
        for (int v : order)
            if (comp[v] == -1) dfs2(v, j++);
        for (int i = 1; i <= n; i++) {
            if (comp[var(i, true)] == comp[var(i, false)]) return false;
            assignment[i] = comp[var(i, true)] > comp[var(i, false)];
        }
        return true;
    }
};

int n, m;

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> n >> m; 
    TwoSAT sat(m);
    for (int i = 0; i < n; i++){
        char a, b;
        int c, d; 
        cin >> a >> c >> b >> d;
        sat.add_or(c, (a == '+'), d, (b == '+'));
    }
    if (!sat.solve()){
        cout << "IMPOSSIBLE";
    }
    else {
        for (int i = 1; i <= m; i++){
            cout << (sat.assignment[i] == 1 ? "+ " : "- ");
        }
    }
}


