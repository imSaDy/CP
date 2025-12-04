#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Find Convex Hull of a set of points.
   - Monotone Chain Algorithm (O(N log N)).
   - Output: Vector of points in CCW order (Start = End).
*/

typedef long long ll; // Use long long for coordinates to avoid precision errors
struct P {
    ll x, y;
    bool operator<(const P& o) const {
        return x < o.x || (x == o.x && y < o.y);
    }
    bool operator==(const P& o) const {
        return x == o.x && y == o.y;
    }
    P operator-(const P& o) const { return {x - o.x, y - o.y}; }
    ll cross(const P& o) const { return x * o.y - y * o.x; }
};

// Returns cross product of (b-a) and (c-a)
ll cross_product(P a, P b, P c) {
    return (b - a).cross(c - a);
}

vector<P> convex_hull(vector<P>& pts) {
    int n = pts.size(), k = 0;
    if (n <= 2) return pts;
    vector<P> h(2 * n);

    // Sort points lexicographically
    sort(pts.begin(), pts.end());

    // Build Lower Hull
    for (int i = 0; i < n; ++i) {
        // While the last two points and new point make a Right Turn (or collinear), pop
        // Use <= 0 to remove collinear points on edges. Use < 0 to keep them.
        while (k >= 2 && cross_product(h[k - 2], h[k - 1], pts[i]) <= 0) k--;
        h[k++] = pts[i];
    }

    // Build Upper Hull
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && cross_product(h[k - 2], h[k - 1], pts[i]) <= 0) k--;
        h[k++] = pts[i];
    }

    h.resize(k - 1); // Remove duplicate last point (which is same as first)
    return h;
}

int main() {
    vector<P> points = {{0, 0}, {2, 2}, {1, 1}, {2, 0}, {0, 2}, {3, 1}};
    vector<P> hull = convex_hull(points);
    
    cout << "Convex Hull Points:" << endl;
    for(auto p : hull) cout << p.x << " " << p.y << endl;
    
    return 0;
}