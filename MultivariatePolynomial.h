#ifndef COD_MULTIVARIATEPOLYNOMIAL_H
#define COD_MULTIVARIATEPOLYNOMIAL_H
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>
#include <boost/rational.hpp>

struct Term {
    std::pair<boost::rational<int>, std::map<char,int>> term_;

    Term(const boost::rational<int>& coefficient, const std::vector<int>& powers){
        term_.first = coefficient;
        char c = 97; // a
        for(int power: powers){
            term_.second[c++] = power;
        }
    }

    bool operator==(const Term& rhs) const {
        if (term_.second.size() != rhs.term_.second.size()) {
            return false;
        }

        for (const auto& entry : term_.second) {
            const auto& key = entry.first;
            const auto& value = entry.second;

            if (rhs.term_.second.count(key) == 0 || rhs.term_.second.at(key) != value) {
                return false;
            }
        }
        return true;
    }

    friend std::ostream& operator<<(std::ostream& os, const Term& term) {
        os << term.term_.first;
        for(const auto& monomial: term.term_.second){
            if(monomial.second > 1) {
                os << "*" << monomial.first << "^" << monomial.second;
            }
            else if (monomial.second == 1){
                os << "*" << monomial.first;
            }
        }
        return os;
    }
};

class MultivariatePolynomial {
private:
    void processPoly();
    void sortPoly(int flag = 0);
    bool isPolyZero(const MultivariatePolynomial&);
    int sumOfPowers(const Term&);
//    std::vector<Term> terms_;

public:
    std::vector<Term> terms_;
    void addTerm(const Term& term);
    //verifici ce se intampla daca rezulatatul este 0
    static MultivariatePolynomial addPolynomials(const MultivariatePolynomial& , const MultivariatePolynomial&);
    //verifici ce se intampla daca rezulatatul este 0
    static MultivariatePolynomial subtractPolynomials(const MultivariatePolynomial& , const MultivariatePolynomial&);
    //verifici ce se intampla daca rezulatatul este 0
    static MultivariatePolynomial multiplyPolynomials(const MultivariatePolynomial&, const MultivariatePolynomial&);

    friend std::ostream& operator<<(std::ostream& os, MultivariatePolynomial& poly) {
        poly.processPoly();
        os << poly.terms_[0] << " ";

        for(size_t i = 1; i < poly.terms_.size(); ++i){
            if (poly.terms_[i].term_.first > 0){
                os << "+" << poly.terms_[i] << " ";
            }
            else{
                os << poly.terms_[i] << " ";
            }
        }
        return os;
    }
};

#endif
