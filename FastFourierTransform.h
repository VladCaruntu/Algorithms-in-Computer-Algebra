#ifndef COD_FASTFOURIERTRANSFORM_H
#define COD_FASTFOURIERTRANSFORM_H
#include <iostream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>

class FastFourierTransform {
public:
    static void FFT(std::vector<std::complex<double>>&, int);
    static std::vector<int> multiply (std::vector<int>&, std::vector<int>&);
};

#endif
