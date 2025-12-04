#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Compare substrings in O(1).
   - Check if S[i...j] is a palindrome (compare fwdHash(i,j) with revHash(i,j)).
   - Find longest common substring (Binary Search length + Hash set).
   
   CAUTION:
   - Collision probability is low but non-zero. Double hash is safe for N <= 10^5.
*/

typedef long long ll;

// Constants: Two sets of Base and Mod
const ll B1 = 313, M1 = 1e9 + 7;
const ll B2 = 317, M2 = 1e9 + 9;
const int MAXN = 200005;

ll pow1[MAXN], pow2[MAXN];
bool initialized = false;

void init_powers() {
    if (initialized) return;
    pow1[0] = pow2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        pow1[i] = (pow1[i - 1] * B1) % M1;
        pow2[i] = (pow2[i - 1] * B2) % M2;
    }
    initialized = true;
}

struct StringHash {
    vector<ll> h1, h2;

    StringHash(string& s) {
        init_powers();
        int n = s.size();
        h1.resize(n + 1, 0);
        h2.resize(n + 1, 0);
        
        for (int i = 0; i < n; i++) {
            h1[i + 1] = (h1[i] * B1 + s[i]) % M1;
            h2[i + 1] = (h2[i] * B2 + s[i]) % M2;
        }
    }

    // Returns pair {hash1, hash2} for substring s[l...r] (0-based inclusive)
    pair<ll, ll> get_hash(int l, int r) {
        ll val1 = (h1[r + 1] - h1[l] * pow1[r - l + 1]) % M1;
        if (val1 < 0) val1 += M1;
        
        ll val2 = (h2[r + 1] - h2[l] * pow2[r - l + 1]) % M2;
        if (val2 < 0) val2 += M2;
        
        return {val1, val2};
    }
};

int main() {
    string s = "banananana";
    StringHash sh(s);
    
    // Compare "nana" at index 2 with "nana" at index 4
    if (sh.get_hash(2, 5) == sh.get_hash(4, 7)) {
        cout << "Substrings match!" << endl;
    } else {
        cout << "Different!" << endl;
    }
    return 0;
}