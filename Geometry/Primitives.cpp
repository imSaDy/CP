#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Basic Geometry Primitives.
   - Line Intersection.
   - Point Distance.
   - Orientation (CCW).
*/

typedef long double ld;
const ld EPS = 1e-9;
const ld PI = acos(-1.0);

struct P {
    ld x, y;
    P(ld x = 0, ld y = 0) : x(x), y(y) {}
    
    // Basic Operators
    P operator+(const P& o) const { return P(x + o.x, y + o.y); }
    P operator-(const P& o) const { return P(x - o.x, y - o.y); }
    P operator*(ld s) const { return P(x * s, y * s); }
    P operator/(ld s) const { return P(x / s, y / s); }
    
    // Dot Product: a.x*b.x + a.y*b.y
    ld dot(const P& o) const { return x * o.x + y * o.y; }
    
    // Cross Product: a.x*b.y - a.y*b.x
    ld cross(const P& o) const { return x * o.y - y * o.x; }
    
    ld dist_sq() const { return x * x + y * y; }
    ld dist() const { return sqrt(dist_sq()); }
    
    // Rotate 90 degrees CCW
    P rot90() const { return P(-y, x); }
    
    bool operator<(const P& o) const {
        if (abs(x - o.x) > EPS) return x < o.x;
        return y < o.y - EPS;
    }
    bool operator==(const P& o) const {
        return abs(x - o.x) < EPS && abs(y - o.y) < EPS;
    }
};

// Returns: 1 if Left Turn (CCW), -1 if Right Turn (CW), 0 if Collinear
int ccw(P a, P b, P c) {
    ld cp = (b - a).cross(c - a);
    if (cp > EPS) return 1;
    if (cp < -EPS) return -1;
    return 0;
}

// Line Intersection (Line AB and Line CD)
// Returns intersection point. Check parallel before calling (cross product of direction vectors).
P line_intersect(P a, P b, P c, P d) {
    P ab = b - a;
    P cd = d - c;
    P ac = c - a;
    ld t = ac.cross(cd) / ab.cross(cd);
    return a + ab * t;
}

// Segment Intersection (Segment AB and Segment CD)
bool on_segment(P p, P a, P b) {
    return p.x >= min(a.x, b.x) - EPS && p.x <= max(a.x, b.x) + EPS &&
           p.y >= min(a.y, b.y) - EPS && p.y <= max(a.y, b.y) + EPS &&
           ccw(a, b, p) == 0;
}

bool segments_intersect(P a, P b, P c, P d) {
    int d1 = ccw(c, d, a);
    int d2 = ccw(c, d, b);
    int d3 = ccw(a, b, c);
    int d4 = ccw(a, b, d);

    // Standard crossing case
    if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) &&
        ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) return true;

    // Collinear cases
    if (d1 == 0 && on_segment(a, c, d)) return true;
    if (d2 == 0 && on_segment(b, c, d)) return true;
    if (d3 == 0 && on_segment(c, a, b)) return true;
    if (d4 == 0 && on_segment(d, a, b)) return true;
    return false;
}

int main() {
    P a(0, 0), b(2, 2);
    P c(0, 2), d(2, 0);
    
    if (segments_intersect(a, b, c, d)) {
        cout << "Intersect!" << endl;
        P inter = line_intersect(a, b, c, d);
        cout << "At: " << inter.x << ", " << inter.y << endl;
    }
    return 0;
}