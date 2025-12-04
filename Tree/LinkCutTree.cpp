#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Dynamic Tree Connectivity (Link/Cut edges).
   - Dynamic Path Queries.
   - Based on Splay Trees.
*/

struct Node {
    int p, ch[2]; // Parent, Children (0=left, 1=right)
    long long val, sum;
    bool rev;     // Reverse tag (for make_root)

    Node() { p = 0; ch[0] = ch[1] = 0; val = sum = 0; rev = 0; }
};

const int MAXN = 100005;
Node t[MAXN];

// Is x a root of its Splay Tree (Auxiliary Tree)?
bool is_root(int x) {
    return t[t[x].p].ch[0] != x && t[t[x].p].ch[1] != x;
}

void push(int x) {
    if (t[x].rev) {
        swap(t[x].ch[0], t[x].ch[1]);
        if (t[x].ch[0]) t[t[x].ch[0]].rev ^= 1;
        if (t[x].ch[1]) t[t[x].ch[1]].rev ^= 1;
        t[x].rev = 0;
    }
}

void update(int x) {
    t[x].sum = t[x].val;
    if (t[x].ch[0]) t[x].sum += t[t[x].ch[0]].sum;
    if (t[x].ch[1]) t[x].sum += t[t[x].ch[1]].sum;
}

void rotate(int x) {
    int y = t[x].p, z = t[y].p;
    int k = (t[y].ch[1] == x);
    if (!is_root(y)) t[z].ch[t[z].ch[1] == y] = x;
    t[x].p = z;
    t[y].ch[k] = t[x].ch[k ^ 1];
    if (t[x].ch[k ^ 1]) t[t[x].ch[k ^ 1]].p = y;
    t[x].ch[k ^ 1] = y;
    t[y].p = x;
    update(y); update(x);
}

void splay(int x) {
    vector<int> st;
    int u = x;
    st.push_back(u);
    while (!is_root(u)) { u = t[u].p; st.push_back(u); }
    while (!st.empty()) { push(st.back()); st.pop_back(); }
    
    while (!is_root(x)) {
        int y = t[x].p, z = t[y].p;
        if (!is_root(y))
            rotate((t[y].ch[1] == x) ^ (t[z].ch[1] == y) ? x : y);
        rotate(x);
    }
}

// Make the path from Root -> x "Preferred"
void access(int x) {
    for (int y = 0; x; y = x, x = t[x].p) {
        splay(x);
        t[x].ch[1] = y;
        update(x);
    }
}

// Make x the root of the represented tree
void make_root(int x) {
    access(x);
    splay(x);
    t[x].rev ^= 1;
}

// Find the representative root of x's component
int find_root(int x) {
    access(x);
    splay(x);
    while (t[x].ch[0]) {
        push(x);
        x = t[x].ch[0];
    }
    splay(x);
    return x;
}

// Link u and v (Edge u-v)
void link(int u, int v) {
    make_root(u);
    if (find_root(v) != u) {
        t[u].p = v;
    }
}

// Cut edge u-v
void cut(int u, int v) {
    make_root(u);
    if (find_root(v) == u && t[v].p == u && !t[v].ch[0]) {
        t[v].p = t[u].ch[1] = 0;
        update(u);
    }
}

// Query Path Sum u-v
long long query(int u, int v) {
    make_root(u);
    access(v);
    splay(v);
    return t[v].sum;
}

int main() {
    // Nodes 1..5
    t[1].val = 10; update(1);
    t[2].val = 20; update(2);
    t[3].val = 30; update(3);
    
    link(1, 2); // 1-2
    link(2, 3); // 1-2-3
    
    cout << "Path 1-3: " << query(1, 3) << endl; // 60
    
    cut(2, 3); // 1-2   3
    cout << "Path 1-3 connected? " << (find_root(1) == find_root(3)) << endl; // 0
    
    return 0;
}