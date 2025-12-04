#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Minimum Cost Maximum Flow.
   - Can handle negative edge costs (but NO negative cycles).
   - Uses SPFA (Shortest Path Faster Algorithm) which is generally O(kE) on random graphs.
*/

const long long INF = 1e18;

struct Edge {
    int to;
    long long cap, flow, cost;
    int rev;
};

struct MCMF {
    int n;
    vector<vector<Edge>> adj;
    vector<long long> dist;
    vector<int> parent_edge;
    vector<int> parent_node;
    vector<bool> in_queue;

    MCMF(int n) : n(n) {
        adj.resize(n);
        dist.resize(n);
        parent_edge.resize(n);
        parent_node.resize(n);
        in_queue.resize(n);
    }

    void add_edge(int from, int to, long long cap, long long cost) {
        Edge a = {to, cap, 0, cost, (int)adj[to].size()};
        Edge b = {from, 0, 0, -cost, (int)adj[from].size()}; // Reverse edge has negative cost
        adj[from].push_back(a);
        adj[to].push_back(b);
    }

    // SPFA to find path with minimum cost
    bool spfa(int s, int t, long long &flow, long long &cost) {
        fill(dist.begin(), dist.end(), INF);
        fill(parent_node.begin(), parent_node.end(), -1);
        fill(in_queue.begin(), in_queue.end(), false);
        
        queue<int> q;
        dist[s] = 0;
        q.push(s);
        in_queue[s] = true;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            in_queue[v] = false;

            for (int i = 0; i < adj[v].size(); ++i) {
                Edge &e = adj[v][i];
                if (e.cap - e.flow > 0 && dist[e.to] > dist[v] + e.cost) {
                    dist[e.to] = dist[v] + e.cost;
                    parent_node[e.to] = v;
                    parent_edge[e.to] = i;
                    if (!in_queue[e.to]) {
                        q.push(e.to);
                        in_queue[e.to] = true;
                    }
                }
            }
        }

        if (dist[t] == INF) return false;

        long long push = INF;
        int curr = t;
        while (curr != s) {
            int prev = parent_node[curr];
            int idx = parent_edge[curr];
            push = min(push, adj[prev][idx].cap - adj[prev][idx].flow);
            curr = prev;
        }

        flow += push;
        cost += push * dist[t];
        curr = t;
        while (curr != s) {
            int prev = parent_node[curr];
            int idx = parent_edge[curr];
            adj[prev][idx].flow += push;
            int rev_idx = adj[prev][idx].rev;
            adj[curr][rev_idx].flow -= push;
            curr = prev;
        }

        return true;
    }

    pair<long long, long long> min_cost_max_flow(int s, int t) {
        long long flow = 0;
        long long cost = 0;
        while (spfa(s, t, flow, cost));
        return {flow, cost};
    }
};

int main() {
    MCMF mcmf(4);
    // from, to, capacity, cost
    mcmf.add_edge(0, 1, 10, 2);
    mcmf.add_edge(0, 2, 10, 5);
    mcmf.add_edge(1, 3, 10, 1);
    mcmf.add_edge(2, 3, 10, 1);
    
    // We want to send max flow, prioritizing low cost.
    // Path 0->1->3 costs 2+1=3 per unit.
    // Path 0->2->3 costs 5+1=6 per unit.
    pair<long long, long long> res = mcmf.min_cost_max_flow(0, 3);
    
    cout << "Flow: " << res.first << " Cost: " << res.second << endl;
    return 0;
}