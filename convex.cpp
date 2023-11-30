#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Point {
    int x, y;

    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // Collinear points
    return (val > 0) ? 1 : 2; // Clockwise or Counterclockwise
}

void convexHullBruteForce(const vector<Point>& points) {
    int n = points.size();
    if (n < 3) {
        cout << "Convex hull not possible with less than 3 points.\n";
        return;
    }

    set<Point> hull;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int orientation_val = 0;
            bool allOnSameSide = true;

            for (int k = 0; k < n; k++) {
                if (k != i && k != j) {
                    int current_orientation = orientation(points[i], points[j], points[k]);
                    if (orientation_val == 0) {
                        orientation_val = current_orientation;
                    } else if (orientation_val != current_orientation) {
                        allOnSameSide = false;
                        break;
                    }
                }
            }

            cout << "Checking pair (" << points[i].x << ", " << points[i].y << ") and (" << points[j].x << ", " << points[j].y << ")\n";

            if (allOnSameSide) {
                cout << "   Added to convex hull.\n";
                hull.insert(points[i]);
                hull.insert(points[j]);
            } else {
                cout << "   Not added to convex hull.\n";
            }
        }
    }

    cout << "Convex Hull Points:\n";
    for (const Point& p : hull) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }
}

int main() {
    int numPoints;
    cout << "Enter the number of points: ";
    cin >> numPoints;

    vector<Point> allPoints;
    for (int i = 0; i < numPoints; i++) {
        Point p;
        cout << "Enter x and y coordinates for point " << i + 1 << ": ";
        cin >> p.x >> p.y;
        allPoints.push_back(p);
    }

    convexHullBruteForce(allPoints);

    return 0;
}
