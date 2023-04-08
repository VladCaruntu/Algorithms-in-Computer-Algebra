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
    static Polynomial addPoly(const Polynomial&, const Polynomial&);
    static Polynomial subtractPoly(const Polynomial&, const Polynomial&);
    static Polynomial multiplyPoly(const Polynomial&, const Polynomial&);

    bool isProcessed = false;
};

#endif
