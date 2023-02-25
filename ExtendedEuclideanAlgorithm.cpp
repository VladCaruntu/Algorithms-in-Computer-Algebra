#include "ExtendedEuclideanAlgorithm.h"
#include <iostream>
#include <iomanip>
#include <chrono>

int ExtendedEuclideanAlgorithm::extendedEuclideanAlgorithm(int num1, int num2, int &x, int &y, bool flag){
    auto startTime = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

    int result = extendedEuclideanAlgorithmRunner(num1, num2, x, y, flag);

    auto endTime = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

    time_taken *= 1e-9;
    if(flag) {
        std::cout << "The execution of " << __FUNCTION__ << " took " << std::fixed << time_taken
                  << std::setprecision(10) << " seconds" << std::endl;
    }

    return result;
}

int ExtendedEuclideanAlgorithm::extendedEuclideanAlgorithmRunner(int num1, int num2, int &x, int &y, bool flag){
    if (num1 == 0) {
        x = 0, y = 1;
        return num2;
    }
    int x1, y1;  // to store recursive call results
    int d = extendedEuclideanAlgorithmRunner(num2 % num1, num1, x1, y1, flag);
    x = y1 - (num2 / num1) * x1;
    y = x1;
    return d;
}
