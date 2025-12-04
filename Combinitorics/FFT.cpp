#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Multiply two polynomials A(x) and B(x) in O(N log N).
   - "Given set A and set B, find count of pairs (a, b) such that a + b = S for all S."
   - Big Integer Multiplication.
   
   PRECISION WARNING:
   - Uses `double`. Accurate results up to answers ~10^14.
   - For exact large integer modular arithmetic, use NTT.
*/

typedef complex<double> cd;
const double PI = acos(-1);

// FFT Core Function
void fft(vector<cd> & a, bool invert) {
    int n = a.size();

    // 1. Bit-reversal permutation
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    // 2. Butterfly Operations
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

    // 3. Normalize if inverse transform
    if (invert) {
        for (cd & x : a) x /= n;
    }
}

// Polynomial Multiplication
vector<long long> multiply(vector<int> const& a, vector<int> const& b) {
    // 1. Convert to Complex
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    
    // 2. Pad to power of 2
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    // 3. Transform -> Pointwise Multiply -> Inverse Transform
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    // 4. Round to integers
    vector<long long> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = round(fa[i].real());
    }
    
    // Optional: Trim trailing zeros or handle carries for Big Ints here
    return result;
}

int main() {
    // Application: "Two Bags" Problem
    // Bag A: {1, 2} -> Poly: x^1 + x^2 -> Coeffs: [0, 1, 1]
    // Bag B: {2, 3} -> Poly: x^2 + x^3 -> Coeffs: [0, 0, 1, 1]
    
    vector<int> A = {0, 1, 1};
    vector<int> B = {0, 0, 1, 1};
    
    vector<long long> res = multiply(A, B);
    
    // Result P(x) = (x + x^2)(x^2 + x^3) = x^3 + x^4 + x^4 + x^5 = x^3 + 2x^4 + x^5
    // Coeffs should be: [0, 0, 0, 1, 2, 1]
    
    cout << "Sum counts:" << endl;
    for(int i=0; i<res.size(); i++) {
        if(res[i] > 0) cout << "Sum " << i << ": " << res[i] << " ways" << endl;
    }
    
    return 0;
}