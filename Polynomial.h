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
    static Polynomial addPoly(const Polynomial&, const Polynomial&, bool flag = true);
    static Polynomial subtractPoly(const Polynomial&, const Polynomial&, bool flag = true);
    static Polynomial multiplyPoly(const Polynomial&, const Polynomial&, bool flag = true);
    static std::pair<Polynomial, std::vector<Polynomial>> dividePoly(const Polynomial& , const Polynomial&, bool flag = true);

    Polynomial& operator=(const Polynomial& other) {
        if (this == &other) {
            return *this;
        }
        terms_ = other.terms_;
        return *this;
    }

    friend bool operator==(const Polynomial& p1, const Polynomial& p2)
    {
        if (p1.terms_.size() != p2.terms_.size()) {
            return false;
        }
        for (size_t i = 0; i < p1.terms_.size(); i++) {
            if (p1.terms_[i] != p2.terms_[i]) {
                return false;
            }
        }
        return true;
    }
};

#endif