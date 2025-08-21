/*
Problem summary:
Undirected graph, each edge weight ∈ [li, ri].
Given node k. Check if ∃ assignment of weights s.t.
    dist(1, n) ≠ dist(1, k) + dist(k, n).
Output YES/NO.

Algorithm:
1. Run Dijkstra from k with r[i] → cops arrival times dist[u].
2. Run modified Dijkstra for robber:
      start t[1] = -dist[1]
      transition: t' = max(t + l[i], -dist[v])
      skip if dist[u] ≤ t[u]
   If robber reaches n → YES, else NO.
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<pair<int,int>>> vvp;
template<typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

const ll INF = 1e17;

void Main(){
    int n, m, k; 
    cin >> n >> m >> k; 
    vvp g(n + 1);
    vi l(m), r(m);
    for(int i=0;i<m;i++){
        int u, v; 
        cin >> u >> v >> l[i] >> r[i];
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }
    vll dist(n + 1);

    // Step 1: cops’ arrival times (shortest path from k with r[i])
    auto dijkstra1 = [&](){
        min_heap<pll> heap; 
        fill(dist.begin(), dist.end(), INF);
        dist[k] = 0; 
        heap.push({0, k}); 
        while (!heap.empty()){
            auto [d, u] = heap.top();
            heap.pop();
            if (d > dist[u]) continue; 
            for (auto [v, i] : g[u]){
                if (dist[v] > dist[u] + r[i]){
                    dist[v] = dist[u] + r[i]; 
                    heap.push({dist[v], v});
                }
            }
        }
    };
    dijkstra1();

    vll t(n + 1);

    // Step 2: robber’s modified Dijkstra
    auto dijkstra2 = [&](){
        min_heap<pll> heap; 
        fill(t.begin(), t.end(), INF);
        t[1] = -dist[1];  
        heap.push({t[1], 1}); 
        while (!heap.empty()){
            auto [d, u] = heap.top();
            heap.pop();

            if (dist[u] <= t[u]) continue;  // cops already there
            if (d > t[u]) continue; 
            if (u == n) return true;        // robber escapes

            for (auto [v, i] : g[u]){
                ll newt = max(t[u] + l[i], -dist[v]); 
                if (t[v] > newt){
                    t[v] = newt; 
                    heap.push({t[v], v});
                }
            }
        }
        return false; 
    };

    cout << (dijkstra2() ? "YES" : "NO") << "\n";
}

int main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(0);
    int tc; 
    cin >> tc;
    while (tc--){
        Main();
    }
    return 0;
}
