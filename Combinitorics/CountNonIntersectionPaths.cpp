#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Count K non-intersecting paths from set A to set B in a DAG.
   - Result is Det(Matrix), where Mat[i][j] = paths from A[i] to B[j].
   - Commonly used in Grid problems.
*/

const int MOD = 1e9 + 7;

long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, MOD - 2);
}

// Standard Determinant (O(K^3))
long long determinant(vector<vector<long long>>& mat) {
    int n = mat.size();
    long long det = 1;
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(mat[j][i]) > abs(mat[pivot][i])) pivot = j;
        }
        swap(mat[i], mat[pivot]);
        if (i != pivot) det = -det;
        
        if (mat[i][i] == 0) return 0;
        
        det = (det * mat[i][i]) % MOD;
        long long inv = modInverse(mat[i][i]);
        
        for (int j = i + 1; j < n; j++) {
            long long factor = (mat[j][i] * inv) % MOD;
            for (int k = i; k < n; k++) {
                mat[j][k] = (mat[j][k] - factor * mat[i][k]) % MOD;
            }
        }
    }
    return (det + MOD) % MOD;
}

// Problem Specific: Count paths from (r1, c1) to (r2, c2) in a Grid
// Only moves Right and Down allowed.
// Formula: (dr + dc) choose (dr)
long long count_paths(int r1, int c1, int r2, int c2) {
    if (r1 > r2 || c1 > c2) return 0;
    int dr = r2 - r1;
    int dc = c2 - c1;
    // Use precomputed factorials for nCr here (omitted for brevity)
    // return nCr(dr + dc, dr);
    return 1; // Dummy return
}

int main() {
    // Example: 2 Paths
    // Start A1, A2. End B1, B2.
    // Matrix:
    // [ Path(A1->B1)  Path(A1->B2) ]
    // [ Path(A2->B1)  Path(A2->B2) ]
    
    int k = 2;
    vector<vector<long long>> mat(k, vector<long long>(k));
    
    // Assume coordinates are defined
    // Fill Matrix
    // mat[0][0] = count_paths(Ax[0], Ay[0], Bx[0], By[0]);
    // ... etc
    
    cout << determinant(mat) << endl;
    
    return 0;
}