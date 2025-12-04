#include <bits/stdc++.h>
using namespace std;

/* APPLICATION:
   - Polygon Area (Shoelace).
   - Point in Polygon (Ray Casting).
   - Works for Concave and Convex.
*/

typedef long long ll;
struct P {
    ll x, y;
};

// 2 * Area (Returns signed area)
// Positive if CCW, Negative if CW. Divide by 2.0 for actual area.
ll polygon_area_2(const vector<P>& p) {
    ll area = 0;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        area += (p[i].x * p[(i + 1) % n].y - p[(i + 1) % n].x * p[i].y);
    }
    return area;
}

// Check if point p is on segment ab
bool on_segment(P p, P a, P b) {
    return p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x) &&
           p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y) &&
           (b.x - a.x) * (p.y - a.y) == (b.y - a.y) * (p.x - a.x);
}

// 0: Outside, 1: Inside, 2: Boundary
int point_in_polygon(P p, const vector<P>& poly) {
    int n = poly.size();
    bool inside = false;
    for (int i = 0; i < n; i++) {
        P a = poly[i];
        P b = poly[(i + 1) % n];
        
        // Check boundary
        if (on_segment(p, a, b)) return 2;
        
        // Ray casting logic
        // Check intersection with horizontal ray to the right
        if ((a.y > p.y) != (b.y > p.y)) {
            // Calculate intersection X coordinate roughly
            // (b.x - a.x) * (p.y - a.y) / (b.y - a.y) + a.x > p.x
            // Using multiplication to avoid float:
            if ((ll)(b.x - a.x) * (p.y - a.y) > (ll)(p.x - a.x) * (b.y - a.y)) {
                // To handle parity correctly with edge cases
                if (a.y > b.y) { 
                    // Downward edge
                     // if logic above is satisfied, it's a valid crossing
                } 
                inside = !inside;
            }
        }
    }
    return inside ? 1 : 0;
}

int main() {
    vector<P> poly = {{0, 0}, {4, 0}, {4, 4}, {2, 2}, {0, 4}};
    
    cout << "2x Area: " << abs(polygon_area_2(poly)) << endl;
    
    P p1 = {2, 1}; // Inside
    P p2 = {2, 3}; // Outside (in the V notch)
    P p3 = {2, 2}; // Boundary
    
    cout << "P1: " << point_in_polygon(p1, poly) << endl;
    cout << "P2: " << point_in_polygon(p2, poly) << endl;
    cout << "P3: " << point_in_polygon(p3, poly) << endl;
    
    return 0;
}