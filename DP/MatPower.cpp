#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Count numbers in range [0, R] satisfying a property.
   - Example property: Sum of digits = TargetSum.
   - DP State: idx (current digit position), current_sum, tight (restricted by R?), leading_zeros.
*/

string S;
long long memo[20][200][2]; // [Index][Sum][Tight]

long long dp(int idx, int current_sum, bool tight) {
    if (current_sum < 0) return 0; // Pruning
    if (idx == S.size()) {
        return (current_sum == 0); // CHANGE THIS: Base case condition
    }
    if (memo[idx][current_sum][tight] != -1) 
        return memo[idx][current_sum][tight];

    long long ans = 0;
    // If tight is true, we can place 0..S[idx].
    // If tight is false, we can place 0..9.
    int limit = tight ? (S[idx] - '0') : 9;

    for (int digit = 0; digit <= limit; digit++) {
        // New tight constraint:
        // Only tight if we were already tight AND we picked the max digit
        bool next_tight = tight && (digit == limit);
        
        ans += dp(idx + 1, current_sum - digit, next_tight);
    }

    return memo[idx][current_sum][tight] = ans;
}

long long solve(long long n, int target) {
    if (n < 0) return 0;
    if (n == 0) return 0; // Edge case
    S = to_string(n);
    memset(memo, -1, sizeof(memo));
    // Start at index 0, with target sum, tight is TRUE
    return dp(0, target, true); 
}

int main() {
    long long L = 10, R = 100;
    int target_sum = 5;
    // Ans(R) - Ans(L-1)
    cout << solve(R, target_sum) - solve(L - 1, target_sum) << endl;
    return 0;
}