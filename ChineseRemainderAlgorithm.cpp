#include "ChineseRemainderAlgorithm.h"
#include "ExtendedEuclideanAlgorithm.h"
#include <iostream>
#include <chrono>
#include <iomanip>

int ChineseRemainderAlgorithm::chineseRemainderAlgorithm(std::vector<std::pair<int, int>>& equations, bool flag){
    auto startTime = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

    std::vector<int> moduli;
    std::vector<int> result;

    for(auto & equation : equations){
        moduli.push_back(equation.first);
        result.push_back(equation.second);
    }

    int M = 1;
    int x = 0;
    int y, z;

    // Calculate the product of all the moduli
    for (size_t i = 0; i < result.size(); i++) {
        M *= result[i];
    }

    // Calculate each term in the sum
    int Mi;
    for (size_t i = 0; i < moduli.size(); i++) {
        Mi = M / result[i];
        ExtendedEuclideanAlgorithm::extendedEuclideanAlgorithm(Mi, result[i], y, z, false);
        x += moduli[i] * y * Mi;
    }

    auto endTime = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

    time_taken *= 1e-9;
    if(flag) {
        std::cout << "The execution of " << __FUNCTION__ << " took " << std::fixed << time_taken
                  << std::setprecision(10) << " seconds" << std::endl;
    }
    return (x % M + M) % M;
}