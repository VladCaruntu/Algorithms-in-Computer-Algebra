#include "Interpolation.h"

Point Interpolation::linearInterpolation(const Point& p1, const Point& p2, double givenValue, bool XorY){
    double x, y;

    //if flag is true -> the input is Y, else the input is X
    if(XorY) {
        y = givenValue;
    }
    else{
        x = givenValue;
    }

    double xMax, xMin, yMax, yMin;
    xMax = (p1.x > p2.x) ? p1.x : p2.x;
    xMin = (p1.x < p2.x) ? p1.x : p2.x;
    yMax = (p1.y > p2.y) ? p1.y : p2.y;
    yMin = (p1.y < p2.y) ? p1.y : p2.y;

    if(XorY) {
        x = ((xMax - xMin) * (givenValue - yMin)) / (yMax - yMin) + xMin;
    }
    else{
        y = ((yMax - yMin) * (givenValue - xMin)) / (xMax - xMin) + yMin;
    }

    return Point{x, y};
}
