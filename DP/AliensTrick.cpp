#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Problem: Given array A of N integers, select EXACTLY K disjoint subarrays 
     to maximize the sum of their elements.
   - Constraint: N <= 10^5, K <= N.
   - Standard DP: O(N * K) -> Too slow if K is large.
   - Aliens Trick: O(N * log(Range)) -> Very fast.
   
   THE TRICK:
   We binary search for a "cost" (lambda) associated with starting a new subarray.
   If lambda is high, we will naturally pick fewer subarrays.
   If lambda is low (or negative), we pick more.
   We find lambda such that the optimal unconstrained strategy picks exactly K.
*/

typedef long long ll;
const ll INF = 1e18;

int n, k;
vector<int> a;

// DP State Pair: {Max Profit, Number of Subarrays Used}
struct State {
    ll val;
    int cnt;

    // Custom comparator to handle tie-breaking
    // If profits are equal, we prefer FEWER subarrays (or MORE, depending on needs).
    // Here we prefer MORE to ensure we reach K if possible.
    bool operator<(const State& other) const {
        if (val != other.val) return val < other.val;
        return cnt < other.cnt;
    }
};

// Solve the problem for a fixed penalty 'lambda'
// This transforms the problem to: "Maximize sum - lambda * count" (Unconstrained count)
// Complexity: O(N)
State solve_with_penalty(ll lambda) {
    // dp[0]: Max profit ending at i, currently NOT inside a subarray
    // dp[1]: Max profit ending at i, currently INSIDE a subarray
    State dp0 = {0, 0};       
    State dp1 = {-INF, 0};    
    
    for (int x : a) {
        State next_dp0, next_dp1;

        // Transition for dp0 (Not in subarray):
        // 1. Was not in subarray (dp0), stay there.
        // 2. Was in subarray (dp1), close it.
        if (dp0.val > dp1.val) next_dp0 = dp0;
        else next_dp0 = {dp1.val, dp1.cnt}; // Keep count same, we just closed it

        // Transition for dp1 (In subarray):
        // 1. Was in subarray (dp1), extend it (add x).
        // 2. Was not in subarray (dp0), start NEW one (add x, pay penalty).
        
        // Option 1: Extend
        State extend = {dp1.val + x, dp1.cnt};
        
        // Option 2: Start New (PAY PENALTY HERE)
        State start_new = {dp0.val + x - lambda, dp0.cnt + 1};

        if (start_new.val > extend.val) next_dp1 = start_new; // Pick better profit
        else if (start_new.val < extend.val) next_dp1 = extend;
        else {
            // Tie-breaking: usually pick the one with MORE subarrays 
            // to cover the 'k' case in binary search ranges.
            if (start_new.cnt > extend.cnt) next_dp1 = start_new;
            else next_dp1 = extend;
        }

        dp0 = next_dp0;
        dp1 = next_dp1;
    }

    // Result is max of ending in a subarray or not
    if (dp0.val > dp1.val) return dp0;
    else return dp1;
}

int main() {
    // Example Input
    // N = 5, Select K = 2 subarrays
    // Array: {2, -50, 2, -50, 2} -> Optimal is {2} and {2, -50, 2}? No.
    // Optimal 2 subarrays: {2} and {2} (indices 0 and 2). Sum = 4. 
    // Wait, indices 0, 2, 4 are 2. So {2}, {2} is 4. {2}, {2, -50, 2} is bad.
    
    // Let's try: {1, -1, 1, -1, 1}, K=2. Optimal: {1}, {1} (total 2).
    n = 5; k = 2;
    a = {1, -1, 1, -1, 1}; 

    // Binary Search Range for Lambda
    // Lambda represents a "cost".
    // Min cost could be negative (if we are desperate to boost count).
    // Max cost could be large positive (to discourage count).
    ll low = -1e9, high = 1e9;
    ll ans = -INF;

    while (low <= high) {
        ll mid = low + (high - low) / 2;
        
        State res = solve_with_penalty(mid);
        
        // res.cnt is the optimal number of subarrays chosen for cost 'mid'
        if (res.cnt >= k) {
            // We picked K or more. This penalty allows us to reach K.
            // Formula: Real Profit = Penalized Profit + (K * lambda)
            ans = res.val + (ll)k * mid;
            
            // We have >= K items. To reduce count to exactly K, we need to INCREASE penalty.
            // (Increase penalty -> items become more expensive -> we pick fewer)
            low = mid + 1;
        } else {
            // We picked fewer than K. The penalty is too high. Decrease it.
            high = mid - 1;
        }
    }

    cout << "Max Sum with " << k << " subarrays: " << ans << endl;
    
    // Manual verification for {1, -1, 1, -1, 1}, k=2
    // Subarrays: [1] and [1] (indices 0 and 2). Sum = 2.
    // Or [1] and [1] (indices 2 and 4). Sum = 2.
    // Output should be 2.
    
    return 0;
}