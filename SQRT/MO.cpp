#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - "Count distinct elements in range [L, R]"
   - "Find frequency of X in range [L, R]"
   - Offline Queries ONLY.
   - Complexity: O((N+Q) * sqrt(N)).
*/

const int MAXN = 200005;
const int BLOCK_SIZE = 450; // Set to ~N / sqrt(Q) or just 450-500 for N=2e5

struct Query {
    int l, r, id;
    
    // Optimized Comparator (Hilbert Curve is better, but this is easy)
    bool operator<(const Query& o) const {
        int b1 = l / BLOCK_SIZE;
        int b2 = o.l / BLOCK_SIZE;
        if (b1 != b2) return b1 < b2;
        // Optimization: Alternate direction for even/odd blocks
        return (b1 & 1) ? (r < o.r) : (r > o.r);
    }
};

int a[MAXN];
int ans[MAXN];
int cnt[1000005]; // Frequency array (Ensure size covers max value in A)
int current_answer = 0;

// ADD element at position i
void add(int idx) {
    int val = a[idx];
    if (cnt[val] == 0) current_answer++;
    cnt[val]++;
}

// REMOVE element at position i
void remove(int idx) {
    int val = a[idx];
    cnt[val]--;
    if (cnt[val] == 0) current_answer--;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int n = 6; // Array size
    // Array: 1 1 2 1 3 2
    a[0]=1; a[1]=1; a[2]=2; a[3]=1; a[4]=3; a[5]=2;
    
    int q_count = 3;
    vector<Query> queries(q_count);
    // Queries: [0, 4], [1, 3], [2, 5]
    queries[0] = {0, 4, 0}; // Distinct: 1, 2, 3 -> Ans 3
    queries[1] = {1, 3, 1}; // Distinct: 1, 2 -> Ans 2
    queries[2] = {2, 5, 2}; // Distinct: 2, 1, 3 -> Ans 3
    
    sort(queries.begin(), queries.end());
    
    int cur_l = 0;
    int cur_r = -1; // Empty range
    
    for (const auto& q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }
        ans[q.id] = current_answer;
    }
    
    for (int i = 0; i < q_count; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}