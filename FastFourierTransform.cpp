#include "FastFourierTransform.h"

//the list is a coefficient representation
//the size should be a power of 2

//try boost::rational afterwards

//vector should be of the form {2, 5, 3, 1, 0 ,2}
//and the powers are like this {5, 4, 3, 2, 1, 0}
                // 2x^5, 5x^4, 3x^3, x^2, 0x^1, 2x^0

std::vector<double> FastFourierTransform::FFT(std::vector<double>& poly){
    size_t size = poly.size();
    if (size == 1)
        return poly;

    double w = pow((-1), 2 / size);
//    e ^ (pi * i) = -1

    //coefficients for the odd degree terms and the even degree terms
    std::vector<double> Pe{};
    std::vector<double> Po{};

    std::reverse(poly.begin(), poly.end());

    for(size_t i = 0; i < size; i++){
        //odd powers in Po and even powers in Pe
        if(size % 2 == 0){   //even -> the other way around
            if (i % 2 == 0){
                Po.push_back(poly[i]);
            }
            else{
                Pe.push_back(poly[i]);
            }
        }
        else{  //the normal way
            if (i % 2 == 0){
                Pe.push_back(poly[i]);
            }
            else{
                Po.push_back(poly[i]);
            }
        }
    }

    std::vector<double> ye {FFT(Pe)};
    std::vector<double> yo {FFT(Po)};
    std::vector<double> y(size * 1.0, 0);

    for(int j = 0; j < size/2; j++){
        y[j] = ye[j] + pow(w, j) * yo[j];
        y[j + size/2] = ye[j] - pow(w, j) * yo[j];
    }

    return y;
}

std::vector<double> FastFourierTransform::IFFT(std::vector<double>& poly){
    size_t size = poly.size();
    if (size == 1)
        return poly;

    double w = pow((-1), (-2 / size)) * (1 / size);
    std::vector<double> Pe{};
    std::vector<double> Po{};

    std::reverse(poly.begin(), poly.end());

    for(size_t i = 0; i < size; i++){
        if(size % 2 == 0){
            if (i % 2 == 0){
                Po.push_back(poly[i]);
            }
            else{
                Pe.push_back(poly[i]);
            }
        }
        else{
            if (i % 2 == 0){
                Pe.push_back(poly[i]);
            }
            else{
                Po.push_back(poly[i]);
            }
        }
    }

    std::vector<double> ye {IFFT(Pe)};
    std::vector<double> yo {IFFT(Po)};
    std::vector<double> y(size * 1.0, 0);

    for(int j = 0; j < size/2; j++){
        y[j] = ye[j] + pow(w, j) * yo[j];
        y[j + size/2] = ye[j] - pow(w, j) * yo[j];
    }
    return y;
}