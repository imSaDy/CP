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

template<typename Node>
struct SegTree {
    int n;
    vector<Node> tree;
    Node identity;

    SegTree(int n, Node identity) : n(n), identity(identity) {
        tree.assign(4 * n, identity);
    }

    Node merge(const Node &a, const Node &b) {
        Node ret; 
        ret.pre = max(a.pre, a.sum + b.pre); 
        ret.suf = max(b.suf, b.sum + a.suf);
        ret.sum = a.sum + b.sum; 
        ret.ans = max({a.ans, b.ans, a.suf + b.pre});
        return ret; 
    }

    void build(const vector<Node> &arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, node * 2, l, mid);
        build(arr, node * 2 + 1, mid + 1, r);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void build(const vector<Node> &arr) {
        build(arr, 1, 1, n);
    }

    void update(int node, int l, int r, int idx, Node val) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (idx <= mid) update(node * 2, l, mid, idx, val);
        else update(node * 2 + 1, mid + 1, r, idx, val);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int idx, Node val) {
        update(1, 1, n, idx, val);
    }

    Node get(int node, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) return identity;
        if (ql <= l && r <= qr) {
            return tree[node];
        }
        int mid = (l + r) / 2;
        Node leftRes = get(node * 2, l, mid, ql, qr);
        Node rightRes = get(node * 2 + 1, mid + 1, r, ql, qr);
        return merge(leftRes, rightRes);
    }

    Node get(int ql, int qr) {
        return get(1, 1, n, ql, qr);
    }
};

struct Node{
    ll pre, suf, ans, sum; 
    Node (int _pre = 0, int _suf = 0, int _ans = 0, int _sum = 0){
        pre = _pre; 
        suf = _suf;
        ans = _ans;
        sum = _sum;
    }
};

int n, m; 

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); 
    cin >> n >> m;
    SegTree <Node> seg(n, Node());
    vector <Node> vn(n + 1); 
    vi a(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
        vn[i] = Node(a[i], a[i], a[i], a[i]);
    }
    seg.build(vn);
    for (int i = 0; i < m; i++){
        int idx, x; 
        cin >> idx >> x; 
        seg.update(idx, Node(x, x, x, x));
        cout << max(seg.get(1, n).ans, 0ll) << endl;
    }
    return 0;
}



