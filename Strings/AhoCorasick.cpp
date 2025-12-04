#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Find multiple patterns in text T. Complexity O(|T| + sum(|P|)).
   - DP on Strings: Count strings of length L avoiding patterns.
*/

const int MAXN = 100005; // Sum of lengths of all patterns
const int K = 26;        // Alphabet size

struct AhoCorasick {
    int next[MAXN][K]; // Trie edges
    int fail[MAXN];    // Failure links
    int end[MAXN];     // Counts how many patterns end here
    int nodes;

    AhoCorasick() {
        nodes = 1;
        memset(next, -1, sizeof(next));
        memset(end, 0, sizeof(end));
    }

    void insert(string& s) {
        int u = 0;
        for (char c : s) {
            int idx = c - 'a';
            if (next[u][idx] == -1) next[u][idx] = nodes++;
            u = next[u][idx];
        }
        end[u]++;
    }

    void build() {
        queue<int> q;
        // Init level 1 (children of root)
        for (int i = 0; i < K; i++) {
            if (next[0][i] != -1) {
                fail[next[0][i]] = 0;
                q.push(next[0][i]);
            } else {
                next[0][i] = 0; // Optimization: Route non-existent root edges back to root
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            // Optimization: Accumulate "end" counts from failure link
            // (If "she" ends here, "he" also ends here)
            end[u] += end[fail[u]]; 

            for (int i = 0; i < K; i++) {
                if (next[u][i] != -1) {
                    // Standard KMP logic: fail[child] = next[fail[parent]][char]
                    fail[next[u][i]] = next[fail[u]][i];
                    q.push(next[u][i]);
                } else {
                    // Trie Graph Optimization: 
                    // Direct shortcut to failure node's child
                    // Makes transitions O(1) always.
                    next[u][i] = next[fail[u]][i];
                }
            }
        }
    }

    // Example: Count total occurrences of all patterns in Text
    int query(string& t) {
        int u = 0;
        int ans = 0;
        for (char c : t) {
            u = next[u][c - 'a']; // Always O(1) due to build optimization
            ans += end[u];
        }
        return ans;
    }
};

int main() {
    AhoCorasick ac;
    string p1 = "he", p2 = "she", p3 = "hers";
    ac.insert(p1); ac.insert(p2); ac.insert(p3);
    ac.build();
    
    string text = "ushers"; 
    // Matches: "she", "he", "he" (inside hers), "hers". 
    cout << ac.query(text) << endl; 
    return 0;
}