#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Find all occurrences of Pattern P in Text T.
   - Both T and P can contain wildcards ('*').
   - Complexity: O(N log N) using 3 FFT passes.
*/

typedef complex<double> cd;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) for (cd & x : a) x /= n;
}

// Convolve two integer vectors A and B
vector<long long> convolve(const vector<int>& a, const vector<int>& b) {
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n); fb.resize(n);
    
    fft(fa, false); fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    
    vector<long long> res(n);
    for (int i = 0; i < n; i++) res[i] = round(fa[i].real());
    return res;
}

vector<int> solve_wildcard_matching(string t, string p) {
    int n = t.size(), m = p.size();
    if (m > n) return {};

    // 1. Prepare vectors
    // Map 'a'->1 ... 'z'->26, '*'->0
    vector<int> T1(n), T2(n), T3(n);
    vector<int> P1(m), P2(m), P3(m);

    for (int i = 0; i < n; i++) {
        int val = (t[i] == '*') ? 0 : (t[i] - 'a' + 1);
        T1[i] = val;         // T
        T2[i] = val * val;   // T^2
        T3[i] = val * val * val; // T^3
    }
    
    // Reverse Pattern for Convolution
    for (int i = 0; i < m; i++) {
        int val = (p[m - 1 - i] == '*') ? 0 : (p[m - 1 - i] - 'a' + 1);
        P1[i] = val;         // P
        P2[i] = val * val;   // P^2
        P3[i] = val * val * val; // P^3
    }

    // 2. Compute 3 parts of the expansion: sum(T^3 P - 2 T^2 P^2 + T P^3)
    // Part A: T^3 * P
    vector<long long> A = convolve(T3, P1);
    // Part B: T^2 * P^2
    vector<long long> B = convolve(T2, P2);
    // Part C: T * P^3
    vector<long long> C = convolve(T1, P3);

    vector<int> matches;
    // Check indices where pattern fully fits (0 to n - m)
    // The result of convolution at index k corresponds to shift (k - (m-1))
    // We care about convolution result at index (i + m - 1) for match starting at i
    for (int i = 0; i <= n - m; i++) {
        int idx = i + m - 1;
        long long val = A[idx] - 2 * B[idx] + C[idx];
        
        // Use epsilon for float errors if using complex<double>, but rounding usually handles it
        if (abs(val) == 0) {
            matches.push_back(i);
        }
    }
    return matches;
}

int main() {
    string text = "abacabax";
    string pattern = "a*a"; // Matches "aba", "aca", "aba"
    
    vector<int> matches = solve_wildcard_matching(text, pattern);
    
    cout << "Pattern found at indices: ";
    for (int idx : matches) cout << idx << " "; 
    // Expected: 0 (aba), 2 (aca), 4 (aba)
    cout << endl;
    return 0;
}