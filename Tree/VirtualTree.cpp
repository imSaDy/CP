#include <bits/stdc++.h>
#include <ios>
#include <iterator>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

void debug_out() { cerr << endl; }

template <typename H, typename... T> void debug_out(H h, T... t) {
    cerr << " " << h;
    debug_out(t...);
}

#define debug(...) cerr << "(" << #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#define F first
#define S second
#define all(x) x.begin(), x.end()
#define MP(x, y) make_pair(x, y)

const int maxn = 2e5 + 10;
const int lg = 20;
const int mod = 1e9 + 7;
const int inf = 2e9;

int n, k, c[maxn], w[maxn], st[maxn], en[maxn], tme, h[maxn];
int par[lg][maxn];
vector<int> g[maxn], ver[maxn], col[maxn];

void dfs(int u, int p = -1) {
    par[0][u] = p;
    st[u] = ++tme;
    for (int i = 1; i < lg; i++) {
        par[i][u] = -1;
        if (par[i - 1][u] != -1)
            par[i][u] = par[i - 1][par[i - 1][u]];
    }
    for (auto v : g[u]) {
        if (v != p) {
            h[v] = h[u] + 1;
            dfs(v, u);
        }
    }
    en[u] = tme;
}

int get_par(int u, int x) {
    for (int i = 0; i < lg; i++) {
        if ((x >> i) & 1)
            u = par[i][u];
    }
    return u;
}

int lca(int u, int v) {
    if (h[u] < h[v])
        swap(u, v);
    u = get_par(u, h[u] - h[v]);
    if (u == v)
        return u;
    for (int i = lg - 1; ~i; i--) {
        if (par[i][u] != par[i][v]) {
            u = par[i][u];
            v = par[i][v];
        }
    }
    return par[0][v];
}

bool cmp(int u, int v) { return st[u] < st[v]; }

void vert(int idx, vector<int> nodes) {
    if (nodes.empty())
        return;
    sort(all(nodes), cmp);

    int sz = nodes.size();

    for (int i = 1; i < sz; i++) {
        int x = lca(nodes[i - 1], nodes[i]);
        nodes.push_back(x);
    }

    sort(all(nodes), cmp);
    nodes.resize(distance(nodes.begin(), unique(all(nodes))));

    for (auto u : nodes) {
        col[u].push_back(idx);
    }
}

void dfs2(int u, int p = -1) {
    if (c[u] == 0) {
        if (p == -1)
            c[u] = 1;
        else
            c[u] = c[par[0][u]];
    }
    for (auto v : g[u]) {
        if (v != p) {
            dfs2(v, u);
        }
    }
}

int Main() {
    cin >> n >> k;

    tme = 0;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        col[i].clear();
    }
    for (int i = 1; i <= k; i++) {
        ver[i].clear();
    }

    for (int i = 1; i <= n; i++) {
        cin >> w[i];
    }

    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        ver[c[i]].push_back(i);
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    h[1] = 0;
    dfs(1);

    for (int i = 1; i <= k; i++) {
        vert(i, ver[i]);
    }

    ll ans = 0;
    for (int u = 1; u <= n; u++) {
        if (col[u].size() > 1)
            ans += w[u];
        if (c[u] == 0 && !col[u].empty()) {
            c[u] = col[u][0];
        }
    }

    dfs2(1);

    cout << ans << '\n';

    for (int u = 1; u <= n; u++) {
        cout << c[u] << ' ';
    }

    cout << '\n';

    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T = 1;
    cin >> T;

    while (T--) {
        Main();
    }
}
