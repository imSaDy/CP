#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - 2D Range Maximum Query on grid [1..N][1..M]
   - Update Point (x, y)
   - Query Rectangle (x1, y1) to (x2, y2)
   - Time: O(log N * log M)
   - Space: O(16 * N * M) -> 1000x1000 is ok, 2000x2000 is risky (128MB+).
*/

const int MAX_X = 1005;
const int MAX_Y = 1005;

int tree[4 * MAX_X][4 * MAX_Y];
int grid[MAX_X][MAX_Y];
int n, m;

// Build inner tree (Y-axis) for a specific X-range node (vx)
void build_y(int vx, int lx, int rx, int vy, int ly, int ry) {
    if (ly == ry) {
        if (lx == rx) {
            // Leaf in both X and Y: Base cell
            tree[vx][vy] = grid[lx][ly];
        } else {
            // Internal in X, Leaf in Y: Combine children from X-tree
            tree[vx][vy] = max(tree[2*vx][vy], tree[2*vx+1][vy]);
        }
    } else {
        int my = (ly + ry) / 2;
        build_y(vx, lx, rx, 2*vy, ly, my);
        build_y(vx, lx, rx, 2*vy+1, my+1, ry);
        tree[vx][vy] = max(tree[vx][2*vy], tree[vx][2*vy+1]);
    }
}

void build_x(int vx, int lx, int rx) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        build_x(2*vx, lx, mx);
        build_x(2*vx+1, mx+1, rx);
    }
    // Whether leaf or internal X-node, we build the corresponding Y-tree
    build_y(vx, lx, rx, 1, 0, m-1);
}

// Update inner tree
void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int new_val) {
    if (ly == ry) {
        if (lx == rx) {
            tree[vx][vy] = new_val;
        } else {
            tree[vx][vy] = max(tree[2*vx][vy], tree[2*vx+1][vy]);
        }
    } else {
        int my = (ly + ry) / 2;
        if (y <= my) update_y(vx, lx, rx, 2*vy, ly, my, x, y, new_val);
        else update_y(vx, lx, rx, 2*vy+1, my+1, ry, x, y, new_val);
        tree[vx][vy] = max(tree[vx][2*vy], tree[vx][2*vy+1]);
    }
}

void update_x(int vx, int lx, int rx, int x, int y, int new_val) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        if (x <= mx) update_x(2*vx, lx, mx, x, y, new_val);
        else update_x(2*vx+1, mx+1, rx, x, y, new_val);
    }
    update_y(vx, lx, rx, 1, 0, m-1, x, y, new_val);
}

int query_y(int vx, int vy, int ly, int ry, int y1, int y2) {
    if (y1 > y2) return -1e9;
    if (y1 == ly && y2 == ry) return tree[vx][vy];
    int my = (ly + ry) / 2;
    return max(query_y(vx, 2*vy, ly, my, y1, min(y2, my)),
               query_y(vx, 2*vy+1, my+1, ry, max(y1, my+1), y2));
}

int query_x(int vx, int lx, int rx, int x1, int x2, int y1, int y2) {
    if (x1 > x2) return -1e9;
    if (x1 == lx && x2 == rx) return query_y(vx, 1, 0, m-1, y1, y2);
    int mx = (lx + rx) / 2;
    return max(query_x(2*vx, lx, mx, x1, min(x2, mx), y1, y2),
               query_x(2*vx+1, mx+1, rx, max(x1, mx+1), x2, y1, y2));
}

int main() {
    n = 3; m = 3;
    // Fill grid...
    grid[1][1] = 5; grid[2][2] = 9;
    build_x(1, 0, n-1);
    
    // Query max in subgrid
    cout << query_x(1, 0, n-1, 0, 2, 0, 2) << endl; 
    return 0;
}