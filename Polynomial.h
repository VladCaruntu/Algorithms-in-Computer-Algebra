#ifndef COD_POLYNOMIAL_H
#define COD_POLYNOMIAL_H

#include <vector>
#include "boost/rational.hpp"

class Polynomial {
private:
    std::vector<std::pair<boost::rational<int>, int>> terms_{};
    void sortPoly();
    void processPoly();
    bool isPolyZero(const Polynomial&);
public:
    void addTerm(const std::pair<boost::rational<int>, int>&);
    static std::vector<std::pair<boost::rational<int>, int>> getTerms(const Polynomial&);
    static void printPoly(Polynomial&);
    static Polynomial addPoly(const Polynomial&, const Polynomial&, bool flag = false);
    static Polynomial subtractPoly(const Polynomial&, const Polynomial&, bool flag = false);
    static Polynomial multiplyPoly(const Polynomial&, const Polynomial&, bool flag = false);
    static std::pair<Polynomial, std::vector<Polynomial>> dividePoly(Polynomial, Polynomial&, bool flag = false);
//    static Polynomial GCD(const Polynomial&, const Polynomial&);
    Polynomial& operator=(const Polynomial& other) {
        if (this == &other) {
            return *this;
        }
        terms_ = other.terms_;
        return *this;
    }

//    bool isProcessed = false;
};

#endif
