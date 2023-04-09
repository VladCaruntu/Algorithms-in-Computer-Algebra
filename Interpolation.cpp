#include "Interpolation.h"
#include <chrono>
#include <iomanip>

//Lagrange method
double Interpolation::linearInterpolation(std::vector<double>& x, std::vector<double>& y, double wantedX, bool flag){
    auto startTime = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

    double yi = 0;
    double currentValue;

    int size = x.size();
    for (int i = 0; i < size; i++){
        currentValue = 1; // the value of the i-th polynomial at the current x
        for (int j = 0; j < size; j++) {
            if (i != j) {
                currentValue *= (wantedX - x[j]) / (x[i] - x[j]);
            }
        }
        yi += y[i] * currentValue;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

    time_taken *= 1e-9;
    if(flag) {
        std::cout << "The execution of " << __FUNCTION__ << " took " << std::fixed << time_taken
                  << std::setprecision(10) << " seconds" << std::endl;
    }
    return yi;
}
