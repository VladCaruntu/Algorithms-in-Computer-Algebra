#include "ChineseRemainderAlgorithm.h"
#include <iostream>

int ChineseRemainderAlgorithm::chineseRemainderAlgorithm(std::vector<std::pair<int, int>>& equations){
    int M{1}; // the value of the product of the moduli
    std::vector<int> mValues{}; // this will contain the values of m1, m2, m3 ... and so on
    std::vector<int> mInverses{};
    int result{0};
    size_t nrEq = equations.size();

    for (size_t pairs = 0; pairs < nrEq; pairs++){
        M *= equations[pairs].second;
    }

    for (size_t pairs = 0; pairs < nrEq; pairs++) {
        mValues.emplace_back(M / equations[pairs].second);
    }

    for (size_t pairs = 0; pairs < nrEq; pairs++) {
        mInverses.emplace_back(mValues[pairs] % equations[pairs].second);
    }

    for(size_t pairs = 0; pairs < nrEq; pairs++){
        result += equations[pairs].first * mValues.at(pairs) * mInverses.at(pairs);
    }
    std::cout<<result;
    result = result % M;
    std::cout<<"\n";

    return result;
}