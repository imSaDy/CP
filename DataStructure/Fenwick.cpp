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
 
 
int n, q;
 
int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> n >> q; 
    vi a(n + 1); 
    vi vc; 
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        vc.pb(a[i]);
    }
    vi x(q), y(q);
    vch t(q);
    for (int i = 0; i < q; i++){
        cin >> t[i] >> x[i] >> y[i];
        vc.pb(y[i]);
        if (t[i] == '?')
            vc.pb(x[i]);
    }
    sort(all(vc));
    uniq(vc);
    Fenwick <int> fen(len(vc) + 2);
    for (int i = 1; i <= n; i++){
        a[i] = lower_bound(all(vc), a[i]) - vc.begin() + 1; 
        fen.add(a[i], 1);
    }
    for (int i = 0; i < q; i++){
        y[i] = lower_bound(all(vc), y[i]) - vc.begin() + 1; 
        if (t[i] == '?'){
            x[i] = lower_bound(all(vc), x[i]) - vc.begin() + 1;
            cout << fen.get(x[i], y[i]) << endl;
        }
        else {
            fen.add(a[x[i]], -1); 
            a[x[i]] = y[i]; 
            fen.add(a[x[i]], 1);
        }
    }
    return 0;
}
 