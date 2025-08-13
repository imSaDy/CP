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

template<typename T>
struct SegTree {
    int n;
    vector<T> lazy;

    SegTree(int n) : n(n) {
        lazy.assign(4 * n, 0);
    }

    void rangeAdd(int node, int l, int r, int ql, int qr, T val) {
        if (qr < l || ql > r) return;
        if (ql <= l && r <= qr) {
            lazy[node] += val;
            return;
        }
        int mid = (l + r) / 2;
        rangeAdd(node * 2, l, mid, ql, qr, val);
        rangeAdd(node * 2 + 1, mid + 1, r, ql, qr, val);
    }

    void rangeAdd(int l, int r, T val) {
        rangeAdd(1, 1, n, l, r, val);
    }

    T pointQuery(int node, int l, int r, int idx) {
        if (l == r) return lazy[node];
        int mid = (l + r) / 2;
        if (idx <= mid) return lazy[node] + pointQuery(node * 2, l, mid, idx);
        else return lazy[node] + pointQuery(node * 2 + 1, mid + 1, r, idx);
    }

    T pointQuery(int idx) {
        return pointQuery(1, 1, n, idx);
    }
};

int n, q; 

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> n >> q; 
    vi a(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    SegTree <ll> seg(n);
    while (q--){
        int t; 
        cin >> t; 
        if (t == 1){
            int l, r, x; 
            cin >> l >> r >> x; 
            seg.rangeAdd(l, r, x);
        }
        else {
            int idx; 
            cin >> idx; 
            cout << seg.pointQuery(idx) + a[idx] << endl; 
        }
    }
    return 0;
}



