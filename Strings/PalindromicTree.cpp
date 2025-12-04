#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Count Distinct Palindromes in O(N).
   - Count occurrences of each palindrome.
   - Find longest palindromic suffix ending at each index.
   - Complexity: O(N) Time and Space.
*/

const int MAXN = 100005;

struct PalindromicTree {
    struct Node {
        int next[26];
        int len;
        int link; // Suffix link (longest proper palindromic suffix)
        int count; // Number of occurrences of this palindrome
        
        Node() {
            memset(next, 0, sizeof(next));
            len = 0; link = 0; count = 0;
        }
    };

    vector<Node> tree;
    string s;
    int cur_node; // Current node (max palindromic suffix of processed prefix)
    int ptr;      // Node count

    PalindromicTree() {
        tree.resize(MAXN + 2);
        s = "";
        
        // Node 1: Root for Odd length palindromes (len -1)
        // Node 2: Root for Even length palindromes (len 0)
        ptr = 2;
        cur_node = 2;
        
        tree[1].len = -1; tree[1].link = 1;
        tree[2].len = 0;  tree[2].link = 1;
    }

    void extend(char ch) {
        s += ch;
        int n = s.size(); 
        int char_idx = ch - 'a';
        
        // Traverse suffix links to find a valid palindrome extension X + ch + X
        int p = cur_node;
        while (true) {
            int pos = n - 1 - tree[p].len - 1;
            // Check if char at (pos) matches current char
            if (pos >= 0 && s[pos] == ch) break;
            p = tree[p].link;
        }

        // Check if node already exists
        if (tree[p].next[char_idx]) {
            cur_node = tree[p].next[char_idx];
            tree[cur_node].count++;
            return;
        }

        // Create new node
        ptr++;
        cur_node = ptr;
        tree[ptr].len = tree[p].len + 2;
        tree[p].next[char_idx] = ptr;
        tree[ptr].count = 1;

        if (tree[ptr].len == 1) {
            // Palindrome of length 1 always links to Even Root (0-len)
            tree[ptr].link = 2;
        } else {
            // Find suffix link for new node
            int q = tree[p].link; // Start searching from parent's link
            while (true) {
                int pos = n - 1 - tree[q].len - 1;
                if (pos >= 0 && s[pos] == ch) break;
                q = tree[q].link;
            }
            tree[ptr].link = tree[q].next[char_idx];
        }
    }
    
    // Propagate counts from longer palindromes to their suffixes
    // Must be called after processing the whole string
    void propagate_counts() {
        for (int i = ptr; i > 2; i--) {
            tree[tree[i].link].count += tree[i].count;
        }
    }
    
    int count_distinct() {
        return ptr - 2;
    }
};

int main() {
    PalindromicTree pt;
    string text = "abacaba";
    for(char c : text) pt.extend(c);
    
    pt.propagate_counts();
    
    cout << "Distinct Palindromes: " << pt.count_distinct() << endl; // 7
    // Access count of specific palindrome (e.g., 'a' is node 3)
    cout << "Occurrences of 'a': " << pt.tree[3].count << endl; // 4
    
    return 0;
}