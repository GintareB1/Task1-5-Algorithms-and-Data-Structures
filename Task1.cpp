#include <iostream>
using namespace std;

struct Point {
    double x, y;
};

struct LineSegment {
    Point p1, p2;
};

// Function to calculate cross product of vectors
double crossProduct(Point p0, Point p1, Point p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}

// Function if two line segments intersect
bool doIntersect(LineSegment l1, LineSegment l2) {
    double cp1 = crossProduct(l1.p1, l1.p2, l2.p1);
    double cp2 = crossProduct(l1.p1, l1.p2, l2.p2);
    double cp3 = crossProduct(l2.p1, l2.p2, l1.p1);
    double cp4 = crossProduct(l2.p1, l2.p2, l1.p2);

    // If the cross products have different signs, the line segments intersect
    return ((cp1 * cp2 < 0) && (cp3 * cp4 < 0));
}

// Function if a point lies on a line segment
bool isOnSegment(Point p, LineSegment l) {
    double minX = min(l.p1.x, l.p2.x);
    double maxX = max(l.p1.x, l.p2.x);
    double minY = min(l.p1.y, l.p2.y);
    double maxY = max(l.p1.y, l.p2.y);

    return (p.x >= minX && p.x <= maxX && p.y >= minY && p.y <= maxY);
}

// Function if a point is inside a quadrilateral
bool isInsideQuadrilateral(Point p, Point A, Point B, Point C, Point D) {
    LineSegment AB = {A, B};
    LineSegment BC = {B, C};
    LineSegment CD = {C, D};
    LineSegment DA = {D, A};

    return (isOnSegment(p, AB) || isOnSegment(p, BC) || isOnSegment(p, CD) || isOnSegment(p, DA));
}

// Function if two quadrilaterals intersect
bool doQuadrilateralsIntersect(Point A, Point B, Point C, Point D, Point E, Point F, Point G, Point H) {
    LineSegment AB = {A, B};
    LineSegment BC = {B, C};
    LineSegment CD = {C, D};
    LineSegment DA = {D, A};
    LineSegment EF = {E, F};
    LineSegment FG = {F, G};
    LineSegment GH = {G, H};
    LineSegment HE = {H, E};

    // Check any edge of the first quadrilateral intersects with any edge of the second quadrilateral
    if (doIntersect(AB, EF) || doIntersect(AB, FG) || doIntersect(AB, GH) || doIntersect(AB, HE) ||
        doIntersect(BC, EF) || doIntersect(BC, FG) || doIntersect(BC, GH) || doIntersect(BC, HE) ||
        doIntersect(CD, EF) || doIntersect(CD, FG) || doIntersect(CD, GH) || doIntersect(CD, HE) ||
        doIntersect(DA, EF) || doIntersect(DA, FG) || doIntersect(DA, GH) || doIntersect(DA, HE)) {
        return true;
    }

    // Check any vertex of one quadrilateral is inside the other quadrilateral
    if (isInsideQuadrilateral(A, E, F, G, H) || isInsideQuadrilateral(B, E, F, G, H) ||
        isInsideQuadrilateral(C, E, F, G, H) || isInsideQuadrilateral(D, E, F, G, H) ||
        isInsideQuadrilateral(E, A, B, C, D) || isInsideQuadrilateral(F, A, B, C, D) ||
        isInsideQuadrilateral(G, A, B, C, D) || isInsideQuadrilateral(H, A, B, C, D)) {
        return true;
    }

    return false;
}

int main() {
    Point A, B, C, D, E, F, G, H;
    cout << "Enter coordinates of quadrilateral 1 (A, B, C, D): ";
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y >> D.x >> D.y;
    cout << "Enter coordinates of quadrilateral 2 (E, F, G, H): ";
    cin >> E.x >> E.y >> F.x >> F.y >> G.x >> G.y >> H.x >> H.y;

    // Check if intersect
    if (doQuadrilateralsIntersect(A, B, C, D, E, F, G, H)) {
        cout << "Intersect\n";
    } else {
        cout << "Do Not Intersect\n";
    }

    return 0;
}
