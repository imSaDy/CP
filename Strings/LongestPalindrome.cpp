#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Find Longest Palindromic Substring in O(N).
   - p[i] stores the "radius" of palindrome at center i.
   - String is transformed to #a#b#a# to handle even length palindromes.
*/

vector<int> manacher(string s) {
    // Transform s into t: "aba" -> "^#a#b#a#$"
    string t = "^#";
    for (char c : s) {
        t += c;
        t += "#";
    }
    t += "$";

    int n = t.size();
    vector<int> p(n, 0);
    int l = 1, r = 1;
    
    for (int i = 1; i < n - 1; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)])); // Mirror property
        
        while (t[i - p[i]] == t[i + p[i]]) // Expand
            p[i]++;
            
        if (i + p[i] > r) {
            l = i - p[i];
            r = i + p[i];
        }
    }
    
    // p[i] in 't' corresponds to length of palindrome in 's'
    // Because of #'s, the radius in t IS the length in s.
    // Subtract 1 because we counted the center '#' itself or similar logic.
    // Actually: p[i] - 1 is the length of the palindrome in original string.
    
    return p;
}

int main() {
    string s = "babad";
    vector<int> p = manacher(s);
    
    int max_len = 0;
    int center_idx = 0;
    
    for(int i=0; i<p.size(); i++) {
        if(p[i] > max_len) {
            max_len = p[i];
            center_idx = i;
        }
    }
    
    cout << "Max Palindrome Length: " << max_len - 1 << endl;
    return 0;
}