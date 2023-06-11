#ifndef COD_INTERPOLATION_H
#define COD_INTERPOLATION_H

#include <iostream>
#include <vector>

class Interpolation {
public:
    static double linearInterpolation(std::vector<double>&, std::vector<double>&, double, bool flag = true);
};

#endif
