#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Count number of Spanning Trees of a graph.
   - Kirchhoff's Matrix Tree Theorem.
   - Determinant of Laplacian Matrix (minor).
   - Complexity: O(N^3) (Gaussian Elimination).
*/

const int MAXN = 105;
const int MOD = 1e9 + 7;

long long mat[MAXN][MAXN];

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

// Gaussian Elimination to find Determinant
long long determinant(int n) {
    long long det = 1;
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(mat[j][i]) > abs(mat[pivot][i])) pivot = j;
        }
        swap(mat[i], mat[pivot]);
        if (i != pivot) det = -det; // Swap flips sign
        
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

int main() {
    int n = 4; // Nodes
    memset(mat, 0, sizeof(mat));
    
    // Define Edges for a Square Cycle: 0-1, 1-2, 2-3, 3-0
    vector<pair<int, int>> edges = {{0,1}, {1,2}, {2,3}, {3,0}};
    
    // Build Laplacian
    for (auto e : edges) {
        int u = e.first;
        int v = e.second;
        mat[u][u]++; mat[v][v]++;
        mat[u][v]--; mat[v][u]--;
    }
    
    // Delete last row/col (reduce to n-1 size)
    // We simply pass n-1 to determinant function and it uses [0..n-2][0..n-2]
    
    // Fix negative mods
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            mat[i][j] = (mat[i][j] % MOD + MOD) % MOD;

    cout << "Spanning Trees: " << determinant(n - 1) << endl; 
    // Square cycle has 4 spanning trees (removing any one of the 4 edges)
    
    return 0;
}