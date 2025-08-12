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

vector<int> euler_tour(int n, int m, vector<vector<pair<int,int>>>& g, int start) {
    vector<int> tour;
    vector<bool> used_edge(m, false); // size = number of edges
    
    stack<int> st;
    st.push(start);

    while (!st.empty()) {
        int u = st.top();
        // Remove used edges from adjacency
        while (!g[u].empty() && used_edge[g[u].back().second]) {
            g[u].pop_back();
        }
        if (g[u].empty()) {
            tour.push_back(u);
            st.pop();
        } else {
            auto [v, id] = g[u].back();
            g[u].pop_back();
            if (!used_edge[id]) {
                used_edge[id] = true;
                st.push(v);
            }
        }
    }

    reverse(tour.begin(), tour.end());
    return tour;
}

int n, m;
vvp g, gr;

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> n >> m;
    g.resize(n + 1);
    gr.resize(n + 1);
    for (int i = 0; i < m; i++){
        int u, v; 
        cin >> u >> v; 
        g[u].pb({v, i});
        gr[v].pb({u, i});
    }
    bool ok = true; 
    for (int i = 1; i <= n; i++){
        if (i == 1){
            if (len(g[i]) != len(gr[i]) + 1) ok = false;
        }
        else if (i == n){
            if (len(g[i]) != len(gr[i]) - 1) ok = false;
        }
        else {
            if (len(g[i]) != len(gr[i])) ok = false; 
        }
    }
    vi tour = euler_tour(n, m, g, 1);
    if (len(tour) != m + 1 || tour.back() != n || !ok)
        return cout << "IMPOSSIBLE", 0;
    for (auto v : tour) cout << v << " ";
}


/*
    remember to check the existance conditions of euler tour...
*/