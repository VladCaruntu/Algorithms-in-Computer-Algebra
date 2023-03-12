#ifndef COD_FASTFOURIERTRANSFORM_H
#define COD_FASTFOURIERTRANSFORM_H
#include <iostream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>

class FastFourierTransform {
public:
    static std::vector<double> FFT(std::vector<double>&);
    static std::vector<double> IFFT(std::vector<double>&);
};

#endif
