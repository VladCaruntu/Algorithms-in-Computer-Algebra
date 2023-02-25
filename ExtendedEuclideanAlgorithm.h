#ifndef COD_EXTENDEDEUCLIDEANALGORITHM_H
#define COD_EXTENDEDEUCLIDEANALGORITHM_H
#include <iostream>

class ExtendedEuclideanAlgorithm {
public:
    static int extendedEuclideanAlgorithm(int, int, int&, int&, bool flag = false);
private:
    static int extendedEuclideanAlgorithmRunner(int, int, int&, int&, bool flag = false);
};

#endif
