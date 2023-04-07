#ifndef COD_POLYNOMIAL_H
#define COD_POLYNOMIAL_H

#include <vector>
#include "boost/rational.hpp"

class Polynomial {
private:
    std::vector<std::pair<boost::rational<int>, int>> terms_{};
    void sortPoly();
    void processPoly();
public:
    void addTerm(const std::pair<boost::rational<int>, int>&);
    std::vector<std::pair<boost::rational<int>, int>> getTerms(const Polynomial&);
    void printPoly();
    void addPoly(const Polynomial&);
    void subtractPoly(const Polynomial&);
    Polynomial multiplyPoly(Polynomial&);

    bool isProcessed = false;
};

#endif
