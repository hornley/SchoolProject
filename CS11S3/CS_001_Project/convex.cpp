#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

/*
This struct or structure stores the inputted x and y points.
The boolean operator const function is for another variable to use for its position
Without this function, the program will meet an error with the insert function for the 'set'.
*/
struct Point {
    int x, y;

    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // Collinear points
    /*
    Ternary operator
    If val is greater than 0, returns 1 which means the line is going clockwise
    otherwise (less than 0), return 2 which means the line is going counterclockwise
    */
    return (val > 0) ? 1 : 2;
}

void convexHullBruteForce(const vector<Point>& points) {
    int n = points.size(); // Stores the value of the size of the vector
    set<Point> hull; // This is where the function will store the points that are in the convex hull

    /*
    The first for loop (int i) will loop with respect to the vector's size
    The second for loop (int j) will loop with respect to the vector's size but its starting value is always an increment of 'i'
    Two dummy/temporary variables are initialized and declared, 'orientation_val' and 'allOnSameSide'

    The third for loop will use the remaining points that are not the same with the points i and j
    Another temporary variable will be initialized and declared, 'current_orientation' with a value from the returning function
    oriention with the three parameters, current i, j and k points.

    For the first time of the third loop, the value of 'orientation_val' will be revalued to the value of 'current_orientation'
    Since this for loop tries all the remaining points, it will check if the current orientation is the same...
    with the new value of 'orientation_val'
    If yes, it continues with the loop
    If not, it changes the value of 'allOnSameSide' to false and breaks out of the loop

    After the third for loop, if the value of 'allOnSameSide' is true, it will be added to the convex hull
    If the value of 'allOnSameSide' is false, it will not be added to the convex hull.
    */

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

    // After that, it's now time to display the points that are in the convex hull.

    cout << "Convex Hull Points:\n";
    for (const Point& p : hull) {
        cout << "(" << p.x << ", " << p.y << ")\n";
    }
}

int main() {
    int numPoints;
    cout << "Enter the number of points: ";
    cin >> numPoints;
    if (numPoints < 3) {
        cout << "Convex hull not possible with less than 3 points.\n";
        return 0;
    }

    vector<Point> allPoints; // Temporary vector to store our inputted points with its x and y coordinates
    for (int i = 0; i < numPoints; i++) {
        Point p;
        cout << "Enter x coordinates for point " << i + 1 << ": ";
        cin >> p.x;
        cout << "Enter y coordinates for point " << i + 1 << ": ";
        cin >> p.y;
        cout << endl;
        allPoints.push_back(p);
    }

    convexHullBruteForce(allPoints);

    return 0;
}
