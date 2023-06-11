#ifndef COD_CHINESEREMAINDERALGORITHM_H
#define COD_CHINESEREMAINDERALGORITHM_H
#include <vector>

class ChineseRemainderAlgorithm {
public:
    //nrEq = nr of equations
    //equations = the vector of pairs of moduli and result (a % b == c). the pair is b and c. we need to find a.
    static int chineseRemainderAlgorithm(std::vector<std::pair<int, int>>&, bool flag = true);
};

#endif
