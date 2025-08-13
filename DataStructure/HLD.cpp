#include <bits/stdc++.h>
using namespace std;

// ------------------ Segment Tree ------------------
template<typename T, class F = function<T(const T&, const T&)>>
struct SegTree {
    int n, N;
    T ID;
    F op;
    vector<T> seg;

    SegTree(int n_, T identity, F func) : n(n_), ID(identity), op(func) {
        N = 1;
        while (N < n) N <<= 1;
        seg.assign(2 * N, ID);
    }

    void build(const vector<T>& arr) {
        for (int i = 1; i <= n; i++) seg[N + i - 1] = arr[i];
        for (int i = N - 1; i > 0; i--)
            seg[i] = op(seg[i << 1], seg[i << 1 | 1]);
    }

    void update(int pos, T val) {
        pos += N - 1;
        seg[pos] = val;
        for (pos >>= 1; pos > 0; pos >>= 1)
            seg[pos] = op(seg[pos << 1], seg[pos << 1 | 1]);
    }

    T query(int l, int r) {
        T ansL = ID, ansR = ID;
        l += N - 1; r += N - 1;
        while (l <= r) {
            if (l & 1) ansL = op(ansL, seg[l++]);
            if (!(r & 1)) ansR = op(seg[r--], ansR);
            l >>= 1; r >>= 1;
        }
        return op(ansL, ansR);
    }
};

// ------------------ HLD ------------------
struct HLD {
    int n, timer = 1;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, pos;
    vector<long long> val;
    SegTree<long long> seg;

    HLD(int n_, const vector<long long>& values)
        : n(n_), adj(n+1), parent(n+1), depth(n+1), heavy(n+1, -1),
          head(n+1), pos(n+1), val(values),
          seg(n_, LLONG_MIN, [](long long a, long long b){ return max(a,b); }) {}

    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int dfs(int v, int p) {
        parent[v] = p;
        int size = 1, max_size = 0;
        for (int u : adj[v]) {
            if (u == p) continue;
            depth[u] = depth[v] + 1;
            int sz = dfs(u, v);
            size += sz;
            if (sz > max_size) {
                max_size = sz;
                heavy[v] = u;
            }
        }
        return size;
    }

    void decompose(int v, int h) {
        head[v] = h;
        pos[v] = timer++;
        seg.update(pos[v], val[v]);
        if (heavy[v] != -1) decompose(heavy[v], h);
        for (int u : adj[v]) {
            if (u != parent[v] && u != heavy[v])
                decompose(u, u);
        }
    }

    void build(int root = 1) {
        dfs(root, 0);
        decompose(root, root);
    }

    long long query_path(int a, int b) {
        long long res = LLONG_MIN;
        while (head[a] != head[b]) {
            if (depth[head[a]] < depth[head[b]]) swap(a, b);
            res = max(res, seg.query(pos[head[a]], pos[a]));
            a = parent[head[a]];
        }
        if (depth[a] > depth[b]) swap(a, b);
        res = max(res, seg.query(pos[a], pos[b]));
        return res;
    }

    void update_node(int v, long long x) {
        val[v] = x;
        seg.update(pos[v], x);
    }
};

// ------------------ Main ------------------
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, q;
    cin >> n >> q;
    vector<long long> values(n+1);
    for (int i = 1; i <= n; i++) cin >> values[i];

    HLD tree(n, values);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        tree.add_edge(u, v);
    }
    tree.build(1);

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int s; long long x;
            cin >> s >> x;
            tree.update_node(s, x);
        } else {
            int a, b;
            cin >> a >> b;
            cout << tree.query_path(a, b) << ' ';
        }
    }
}
