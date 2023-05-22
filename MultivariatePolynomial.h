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

    Term(){
        term_.first = 0;//grija aici :)
    }

    bool operator==(const Term& other) const {
        if (term_.second.size() != other.term_.second.size()) {
            return false;
        }

        for (const auto& entry : term_.second) {
            const auto& key = entry.first;
            const auto& value = entry.second;

            if (other.term_.second.count(key) == 0 || other.term_.second.at(key) != value) {
                return false;
            }
        }
        return true;
    }

    friend Term operator*(const Term& t1, const Term& t2) {
        boost::rational<int> coef = t1.term_.first * t2.term_.first;

        std::vector<int> powers1{};
        std::vector<int> powers2{};

        //we put the powers of the variable in the first term in the vector powers1
        for(const auto& var_pow: t1.term_.second){
            powers1.push_back(var_pow.second);
        }

        //we put the powers of the variable in the second term in the vector powers2
        for(const auto& var_pow: t2.term_.second){
            powers2.push_back(var_pow.second);
        }

        size_t size = std::max(powers1.size(), powers2.size());
        size_t size1 = powers1.size();
        size_t size2 = powers2.size();

        if(powers1.size() > powers2.size()){
            size = powers1.size();
            while(size2 < size1){
                powers2.push_back(0);
                size2++;
            }
        }
        else{
            size = powers2.size();
            while(size1 < size2){
                powers1.push_back(0);
                size1++;
            }
        }

        std::vector<int> finalPowers{};
        for(size_t i = 0; i < size; i++){
            finalPowers.push_back(powers1.at(i) + powers2.at(i));
        }
        Term result(coef, finalPowers);

        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Term& term) {
        if(term.term_.first == 0){
            os << "0";
            return os;
        }
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
    std::vector<Term> terms_;

    void processPoly();
    void sortPoly(int flag = 0);
    bool isPolyZero(const MultivariatePolynomial&);
    int sumOfPowers(const Term&);

public:
    void addTerm(const Term& term);
    static MultivariatePolynomial addPolynomials(const MultivariatePolynomial& , const MultivariatePolynomial&);
    static MultivariatePolynomial subtractPolynomials(const MultivariatePolynomial& , const MultivariatePolynomial&);
    static MultivariatePolynomial multiplyPolynomials(const MultivariatePolynomial&, const MultivariatePolynomial&);
    static std::pair<MultivariatePolynomial, std::vector<MultivariatePolynomial>> dividePolynomials(const MultivariatePolynomial&, const MultivariatePolynomial&);

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

    MultivariatePolynomial& operator= (const MultivariatePolynomial& other){
        if (this == &other){
            return *this;
        }
        this->terms_ = other.terms_;
        return *this;
    }
};

#endif
