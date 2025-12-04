#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Offline Range Queries WITH Point Updates.
   - Complexity: O(N^(5/3)).
   - Block Size: N^(2/3) (approx 2154 for N=100,000).
*/

const int MAXN = 100005;
const int BLOCK_SIZE = 2200; // N^(2/3)

struct Query {
    int l, r, t, id;
    bool operator<(const Query& o) const {
        int b1 = l / BLOCK_SIZE;
        int b2 = o.l / BLOCK_SIZE;
        int b3 = r / BLOCK_SIZE;
        int b4 = o.r / BLOCK_SIZE;
        
        if (b1 != b2) return b1 < b2;
        if (b3 != b4) return b3 < b4;
        return t < o.t;
    }
};

struct Update {
    int pos, old_val, new_val;
};

int arr[MAXN];
int ans[MAXN];
int cnt[1000005];
int current_ans = 0;
vector<Query> qs;
vector<Update> ups;

void add(int val) {
    if (cnt[val] == 0) current_ans++;
    cnt[val]++;
}

void remove(int val) {
    cnt[val]--;
    if (cnt[val] == 0) current_ans--;
}

// Move 'time' forward: Apply update
void apply_update(int u_idx, int& cur_l, int& cur_r) {
    int pos = ups[u_idx].pos;
    int new_v = ups[u_idx].new_val;
    int old_v = ups[u_idx].old_val;
    
    // If the updated position is inside current range, adjust answer
    if (pos >= cur_l && pos <= cur_r) {
        remove(old_v);
        add(new_v);
    }
    arr[pos] = new_v;
}

// Move 'time' backward: Undo update
void undo_update(int u_idx, int& cur_l, int& cur_r) {
    int pos = ups[u_idx].pos;
    int new_v = ups[u_idx].new_val;
    int old_v = ups[u_idx].old_val;
    
    if (pos >= cur_l && pos <= cur_r) {
        remove(new_v);
        add(old_v);
    }
    arr[pos] = old_v; // Revert to old value
}

int main() {
    // Example: Distinct elements with updates
    int n = 5;
    arr[0]=1; arr[1]=2; arr[2]=3; arr[3]=4; arr[4]=5;
    
    // Queries: type 1=range, type 2=update
    // 1 0 4 (Count distinct 0..4) -> 5
    // 2 0 5 (Update arr[0] = 5) -> Array: 5 2 3 4 5
    // 1 0 4 (Count distinct 0..4) -> 4 (5 is repeated)
    
    // Construct Query and Update lists
    qs.push_back({0, 4, 0, 0}); // Time 0 (before any updates)
    ups.push_back({0, 1, 5});   // Update 0: pos 0, old 1, new 5
    qs.push_back({0, 4, 1, 1}); // Time 1 (after update 0)
    
    sort(qs.begin(), qs.end());
    
    int cur_l = 0, cur_r = -1, cur_t = -1; // cur_t is index of last APPLIED update
    
    for (const auto& q : qs) {
        // Adjust Time
        while (cur_t < q.t - 1) { cur_t++; apply_update(cur_t, cur_l, cur_r); } // Apply next
        while (cur_t >= q.t)    { undo_update(cur_t, cur_l, cur_r); cur_t--; }    // Undo current
        
        // Adjust Range
        while (cur_l > q.l) add(arr[--cur_l]);
        while (cur_r < q.r) add(arr[++cur_r]);
        while (cur_l < q.l) remove(arr[cur_l++]);
        while (cur_r > q.r) remove(arr[cur_r--]);
        
        ans[q.id] = current_ans;
    }
    
    cout << ans[0] << endl; // 5
    cout << ans[1] << endl; // 4
    
    return 0;
}