#include "EuclideanAlgorithm.h"
#include <chrono>
#include <iostream>
#include <iomanip>

int EuclideanAlgorithm::euclideanAlgorithmWithSubtractions(int num1, int num2, bool flag){
    auto startTime = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

    while(num1 != num2){
        if(num1 > num2){
            num1 -= num2;
        }
        else {
            num2 -= num1;
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

    time_taken *= 1e-9;
    if(flag) {
        std::cout << "The execution of " << __FUNCTION__ << " took " << std::fixed << time_taken
                  << std::setprecision(10) << " seconds" << std::endl;
    }
    return num1;
}

int EuclideanAlgorithm::euclideanAlgorithmWithDivisions(int num1, int num2, bool flag){
    auto startTime = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

    int temp{};
    while(num2 != 0){
        temp = num2;
        num2 = num1 % num2;
        num1 = temp;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

    time_taken *= 1e-9;
    if(flag) {
        std::cout << "The execution of " << __FUNCTION__ << " took " << std::fixed << time_taken
                  << std::setprecision(10) << " seconds" << std::endl;
    }
    return num1;
}

int EuclideanAlgorithm::euclideanAlgorithmWithRecursion(int num1, int num2, bool flag){
    auto startTime = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

    int result = euclideanAlgorithmWithRecursionRunner(num1, num2);

    auto endTime = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

    time_taken *= 1e-9;
    if(flag) {
        std::cout << "The execution of " << __FUNCTION__ << " took " << std::fixed << time_taken
                  << std::setprecision(10) << " seconds" << std::endl;
    }

    return result;
}

int EuclideanAlgorithm::euclideanAlgorithmWithRecursionRunner(int num1, int num2){
    if (num2 == 0){
        return num1;
    }
    return euclideanAlgorithmWithRecursionRunner(num2, num1 % num2);
}