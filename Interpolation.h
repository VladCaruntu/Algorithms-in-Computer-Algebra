#ifndef COD_INTERPOLATION_H
#define COD_INTERPOLATION_H

#include <iostream>

struct Point{
    double x;
    double y;
    Point(double x, double y) : x(x), y(y){}
    Point(): x(0), y(0){}
    friend std::ostream& operator<< (std::ostream& os, const Point& p){
        os << "Point (" << p.x << ", " << p.y << ")";
        return os;
    }
};

// the value of X at a certain point (X, Y) with known Y
//OR
// the value of Y at a certain point (X, Y) with known X
class Interpolation {
public:
    static Point linearInterpolation(const Point& p1, const Point& p2, double, bool);
};

#endif
