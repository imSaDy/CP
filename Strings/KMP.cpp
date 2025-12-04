#include <bits/stdc++.h>
using namespace std;

/* APPLICATION KMP:
   - Find pattern P in text T (Use P + '#' + T).
   - Find smallest period: len - pi[len-1] (if len % period == 0).
   - Count pattern occurrences.
*/

vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

/* APPLICATION Z-ALGO:
   - Z[i] = LCP(s, s[i...]).
   - Pattern matching: S = P + "$" + T. Check if Z[i] == P.size().
*/
vector<int> z_function(string s) {
    int n = s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min(r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int main() {
    string s = "abacaba";
    vector<int> pi = prefix_function(s);
    
    cout << "Pi array: ";
    for(int x : pi) cout << x << " "; // 0 0 1 0 1 2 3
    cout << endl;
    
    // Period check
    int n = s.size();
    int len_longest_border = pi[n-1];
    int period = n - len_longest_border;
    // For "abacaba", period is 4 ("abac"), repeats? No. 7%4 != 0.
    
    return 0;
}