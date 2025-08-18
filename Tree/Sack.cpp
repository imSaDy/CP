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

struct Sack {
    int n;
    vector<int> color, sz, ans;
    vector<vector<int>> G;
    vector<map<int,int>*> cnt;

    Sack(int n) : n(n) {
        color.resize(n + 1);
        sz.resize(n + 1);
        ans.resize(n + 1);
        G.assign(n + 1, {});
        cnt.resize(n + 1);
    }

    void add_edge(int u, int v) {
        G[u].push_back(v);
        G[v].push_back(u);
    }

    void dfs_size(int u, int p) {
        sz[u] = 1;
        for (auto v : G[u]) {
            if (v == p) continue;
            dfs_size(v, u);
            sz[u] += sz[v];
        }
    }

    void dfs_sack(int u, int p) {
        int big = -1, mx = -1;
        for (auto v : G[u]) {
            if (v == p) continue;
            if (sz[v] > mx) {
                mx = sz[v];
                big = v;
            }
        }

        if (big != -1) {
            dfs_sack(big, u);
            cnt[u] = cnt[big];
        } else {
            cnt[u] = new map<int,int>();
        }

        for (auto v : G[u]) {
            if (v == p || v == big) continue;
            dfs_sack(v, u);
            for (auto &x : *cnt[v]) {
                (*cnt[u])[x.first] += x.second;
            }
        }

        (*cnt[u])[color[u]]++;
        ans[u] = (int)cnt[u]->size();
    }

    void solve() {
        dfs_size(1, 0);
        dfs_sack(1, 0);
    }

    void print_answers() {
        for (int i = 1; i <= n; i++) {
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
};

int n; 

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n; 
    Sack sack(n);
    for (int i = 1; i <= n; i++) cin >> sack.color[i];
    for (int i = 1; i < n; i++){
        int u, v; 
        cin >> u >> v; 
        sack.add_edge(u, v);
    }
    sack.solve();
    sack.print_answers();
    return 0;
}



