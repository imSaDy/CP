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
struct SegTree {
    int n;
    vector<T> tree;

    SegTree(int n) : n(n) {
        tree.assign(4 * n, numeric_limits<T>::min());
    }

    void build(const vector<T> &arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, node * 2, l, mid);
        build(arr, node * 2 + 1, mid + 1, r);
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }

    void build(const vector<T> &arr) {
        build(arr, 1, 1, n);
    }

    void update(int node, int l, int r, int idx, T val) {
        if (l == r) {
            tree[node] += val; // add val instead of assign
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(node * 2, l, mid, idx, val);
        else update(node * 2 + 1, mid + 1, r, idx, val);
        tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int idx, T val) {
        update(1, 1, n, idx, val);
    }

    // Find smallest index with value >= x, or -1 if none
    int query(int node, int l, int r, T x) {
        if (tree[node] < x) return -1;
        if (l == r) return l;
        int mid = (l + r) / 2;
        int leftRes = query(node * 2, l, mid, x);
        if (leftRes != -1) return leftRes;
        return query(node * 2 + 1, mid + 1, r, x);
    }

    int query(T x) {
        return query(1, 1, n, x);
    }
};

int n, m; 

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> n >> m; 
    vi h(n + 1), r(m + 1);
    for (int i = 1; i <= n; i++) cin >> h[i]; 
    for (int i = 1; i <= m; i++) cin >> r[i];
    SegTree <int> seg(n);
    seg.build(h);
    for (int i = 1; i <= m; i++){
        int idx = seg.query(r[i]);
        if (idx == -1){
            cout << 0 << " ";
        }
        else {
            cout << idx << " ";
            seg.update(idx, -r[i]);
        }
    }
    return 0;
}



