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

const int maxn = 1.5e5 + 2; 
const int mod = 1e9 + 7;
const int inf = 1e9 + 1;
const int alp = 31; 
const int lg = 12; 
const ll INF = 1e17; 
const int sq = 700;

int n, m, L[maxn], R[maxn], K[maxn], f[maxn], block[maxn];
vvi g; 

// answer -> O(rad n), update -> O(1) great choice for MO..
struct DS { // define globally or adjust the size of arrays..
    int cnt[maxn << 1], blcnt[(maxn << 1) / sq + 2];
    void add(int idx, int x){
        cnt[idx] += x; 
        blcnt[idx / sq] += x;  
    }
    int get(int k){
        int cur = 0; 
        while (blcnt[cur] < k){
            k -= blcnt[cur++];
        }
        for (int i = sq * cur; i < sq * (cur + 1); i++){
            if (cnt[i] >= k){
                return i; 
            }
            k -= cnt[i];
        }
        assert(false);
    }
    void clear(){
        memset(cnt, 0, sizeof cnt);
        memset(blcnt, 0, sizeof blcnt);
    }
}ds; 

void Main(){
    cin >> n >> m;
    g.resize(n + 1);
    for (int i = 0; i < m; i++){
        int u, v; 
        cin >> u >> v; 
        g[u].pb(v);
        g[v].pb(u);
    }
    int tot = 0, cur = 1; 
    for (int i = 1; i <= n; i++){
        tot += len(g[i]) + 1;
        block[i] = cur; 
        if (tot > sq){
            cur++; 
            tot = 0;
        }
    }
    int q; 
    cin >> q; 
    vi Q;
    for (int i = 1; i <= q; i++){
        cin >> L[i] >> R[i] >> K[i];
        Q.pb(i);
    }
    sort(all(Q), [&](int i, int j){
        if (block[L[i]] != block[L[j]]) return block[L[i]] < block[L[j]];
        if (block[L[i]] & 1)
            return R[i] < R[j];
        else 
            return R[i] > R[j];
    });
    int l = 0, r = -1;
    auto add = [&](int u){
        for (auto v : g[u]){
            if (l <= v && v <= r){
                ds.add(f[v], -1);
                f[v] ^= u;
                f[u] ^= v;  
                ds.add(f[v], 1);
            }
        }
        ds.add(f[u], 1);
    };
    auto del = [&](int u){
        ds.add(f[u], -1);
        for (auto v : g[u]){
            if (l <= v && v <= r){
                ds.add(f[v], -1);
                f[v] ^= u; 
                f[u] ^= v; 
                ds.add(f[v], 1);
            }
        }
    };
    fill(f, f + n + 1, 0);
    vi ans(q + 1);
    for (auto i : Q){
        while (r < R[i]){
            add(++r);
        }
        while (l > L[i]){
            add(--l);
        }
        while (r > R[i]){
            del(r--);
        }
        while (l < L[i]){
            del(l++);
        }
        ans[i] = ds.get(K[i]);
    }
    for (int i = 1; i <= q; i++){
        cout << ans[i] << "\n";
    }
    while (l <= r){
        del(l++);
    }

}


void Reset(){
    g.clear();
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int tc = 1; 
    cin >> tc;
    while (tc--){
        Main();
        Reset();
    }
    return 0;
}



