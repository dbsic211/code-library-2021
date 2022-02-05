//https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/

struct Point{int x, y; };
struct DoublePoint{double x, y; };
bool onSegment(Point p, Point q, Point r);
int orientation(Point p, Point q, Point r);
bool doIntersect(Point p1, Point q1, Point p2, Point q2);
DoublePoint find_intersection(Point p1, Point q1, Point p2, Point q2);
int SquareDistance(Point p, Point q);


bool onSegment(Point p, Point q, Point r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
       return true;
 
    return false;
}
int orientation(Point p, Point q, Point r) {
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0; 
    return (val > 0)? 1: 2;
}
bool doIntersect(Point p1, Point q1, Point p2, Point q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    if (o1 != o2 && o3 != o4) return true;
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
    return false;
}
DoublePoint find_intersection(Point p1, Point q1, Point p2, Point q2) {
    if(!doIntersect(p1, q1, p2, q2)) return {-101, -101};
    if(p1.x == q1.x) {
        double m = (q2.y - p2.y) * 1.0 / (q2.x - p2.x);
        double c = q2.y - q2.x * m;
        return {p1.x * 1.0, m * p1.x + c};
    }
    else if(p2.x == q2.x) {
        double m = (q1.y - p1.y) * 1.0 / (q1.x - p1.x);
        double c = q1.y - q1.x * m;
        return {p2.x * 1.0, m * p2.x + c};
    }
    else {
        double m1 = (q1.y - p1.y) * 1.0 / (q1.x - p1.x);
        double c1 = q1.y - q1.x * m1;
        double m2 = (q2.y - p2.y) * 1.0 / (q2.x - p2.x); 
        double c2 = q2.y - q2.x * m2;
        double finx = (c2 - c1) * 1.0 / (m1 - m2);
        double finy = finx * m1 + c1;
        return {finx, finy};
    }
}
int SquareDistance(Point p, Point q) {
  return (p.x - q.x) * (p.x - q.x) + (p.y - q.y) * (p.y - q.y);
}
