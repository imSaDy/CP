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

int n;
string res;
unordered_set<string> used;

void dfs(string node) {
    for (char c : {'0', '1'}) {
        string edge = node + c;
        if (!used.count(edge)) {
            used.insert(edge);
            dfs(edge.substr(1)); // move to suffix of length n-1
            res.push_back(c);
        }
    }
}

int main() {
    cin >> n;
    string start(n - 1, '0');
    dfs(start);
    res += start; // append starting (n-1) zeros
    reverse(res.begin(), res.end());
    cout << res << "\n";
}


// second solution

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
vvp g;

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> n;
    g.resize(1 << n);
    int id = 0; 
    for (int i = 0; i < (1 << n); i++){
        int u = i >> 1; 
        int v = i; 
        if (v > (1 << (n - 1))){
            v -= (1 << (n - 1));
        }
        g[u].pb(MP(v, id++));
    }
    vi tour = euler_tour(1 << n, 1 << n, g, 0);
    for (int i = 0; i < n - 1; i++){
        cout << 0;
    }
    for (int i = 1; i < len(tour); i++){
        cout << (tour[i] & 1);
    }
}

