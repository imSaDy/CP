#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Factorize S into w1 >= w2 >= ... >= wk where wi are Lyndon words.
   - Find Lexicographically Smallest Cyclic Shift (using S+S).
   - A string is "Lyndon" if it is strictly smaller than all its proper suffixes.
   
   DUVAL'S ALGORITHM:
   - O(N) time, O(1) extra space.
*/

vector<string> lyndon_factorization(string s) {
    int n = s.size();
    int i = 0;
    vector<string> factorization;
    
    while (i < n) {
        int j = i + 1, k = i;
        
        // Try to extend the current Lyndon word
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j]) {
                k = i; // Reset: we found a char smaller than start, new period
            } else {
                k++; // s[k] == s[j], potential periodicity
            }
            j++;
        }
        
        // s[i...j-1] is a pre-Lyndon word s[i...k] repeated
        while (i <= k) {
            factorization.push_back(s.substr(i, j - k));
            i += j - k;
        }
    }
    return factorization;
}

// Returns the starting index of the smallest cyclic shift
int min_cyclic_shift(string s) {
    string t = s + s;
    int n = s.size();
    int i = 0, ans = 0;
    
    while (i < n) {
        ans = i; // Potential answer
        int j = i + 1, k = i;
        
        while (j < 2 * n && t[k] <= t[j]) {
            if (t[k] < t[j]) k = i;
            else k++;
            j++;
        }
        
        // Optimization: Skip repetitions
        while (i <= k) i += j - k;
    }
    return ans;
}

int main() {
    string s = "banananana";
    
    // Factorization
    vector<string> factors = lyndon_factorization(s);
    cout << "Lyndon Factors: ";
    for(auto w : factors) cout << w << " "; 
    // Output: "b" "an" "an" "an" "an" "a"
    cout << endl;
    
    // Smallest Cyclic Shift
    string s2 = "cba";
    int start = min_cyclic_shift(s2);
    cout << "Smallest shift of 'cba': " << s2.substr(start) + s2.substr(0, start) << endl; 
    // Output: "abc"
    
    return 0;
}