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
        if(!powers.empty()) {
            for (int power: powers) {
                term_.second[c++] = power;
            }
        }
        else
        {
            std::cerr<<"Invalid power vector";
        }
    }

    Term() = delete;

    static void equalizeTerms(Term& t1, Term& t2)
    {
        if(t1.term_.second.size() == t2.term_.second.size())//if already equal -> function call overkill
            return;

        std::unique_ptr<Term> t1_copy = std::make_unique<Term>(t1);
        std::unique_ptr<Term> t2_copy = std::make_unique<Term>(t2);

        std::vector<int> powers1{};
        std::vector<int> powers2{};

        for(const auto& var_pow: t1.term_.second){
            powers1.push_back(var_pow.second);
        }

        for(const auto& var_pow: t2.term_.second){
            powers2.push_back(var_pow.second);
        }
        size_t size1 = t1.term_.second.size();
        size_t size2 = t2.term_.second.size();

        if(size1 > size2){
            while(size2 < size1){
                powers2.push_back(0);
                size2++;
            }
        }
        else{
            while(size1 < size2){
                powers1.push_back(0);
                size1++;
            }
        }

        t1 = Term(t1.term_.first, powers1);
        t2 = Term(t2.term_.first, powers2);
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
        std::unique_ptr<Term> term1 = std::make_unique<Term> (t1);
        std::unique_ptr<Term> term2 = std::make_unique<Term> (t2);
        equalizeTerms(*term1, *term2);

        boost::rational<int> coef = t1.term_.first * t2.term_.first;
        size_t size = term1->term_.second.size();
        std::vector<int> finalPowers{};

        std::vector<int> powers1{};
        std::vector<int> powers2{};

        for(const auto& var_pow: term1->term_.second){
            powers1.push_back(var_pow.second);
        }
        for(const auto& var_pow: term2->term_.second){
            powers2.push_back(var_pow.second);
        }

        for(size_t i = 0; i < size; i++){
            finalPowers.push_back(powers1.at(i) + powers2.at(i));
        }

        Term result(coef, finalPowers);
        return result;
    }

    friend Term operator/(const Term& t1, const Term& t2)
    {
        std::unique_ptr<Term> term1 = std::make_unique<Term> (t1);
        std::unique_ptr<Term> term2 = std::make_unique<Term> (t2);
        equalizeTerms(*term1, *term2);

        boost::rational<int> coef = t1.term_.first / t2.term_.first;
        size_t size = term1->term_.second.size();
        std::vector<int> finalPowers{};

        std::vector<int> powers1{};
        std::vector<int> powers2{};

        for(const auto& var_pow: term1->term_.second){
            powers1.push_back(var_pow.second);

        }

        for(const auto& var_pow: term2->term_.second){
            powers2.push_back(var_pow.second);
        }

        for(size_t i = 0; i < size; i++){
            if(powers1[i] < powers2[i]){
                finalPowers.push_back(0);
            }
            else if(powers2[i] == 0 && powers1[i] > 0){
                finalPowers.push_back(powers1[i]);
            }
            else {
                finalPowers.push_back(powers1[i] - powers2[i]);
            }
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
            else
            {
                if(monomial.second != 0)
                {
                    os << monomial.first;
                    return os;
                }
            }
        }
        return os;
    }
};

class MultivariatePolynomial {
private:
    std::vector<Term> terms_;

//    void processPoly();
//    void sortPoly(int flag = 0);
    bool isPolyZero(const MultivariatePolynomial&);
    //sa stergi static de la canDivide
//    static bool canDivide(const MultivariatePolynomial&, const MultivariatePolynomial&);
    int sumOfPowers(const Term&);
//    std::vector<int> getDegree(const MultivariatePolynomial&) const;

public:
    void sortPoly(int flag = 0);
    std::vector<Term> getTerms() const { return this->terms_;}
    void processPoly();
    static std::vector<int> getDegree(MultivariatePolynomial&, bool flag = false);//if flag == 0 => min degree, if flag == 1 => max degree
    static bool canDivide(const MultivariatePolynomial&, const MultivariatePolynomial&);
    void addTerm(const Term& term);
    static MultivariatePolynomial addPolynomials(const MultivariatePolynomial& , const MultivariatePolynomial&, bool flag = true);
    static MultivariatePolynomial subtractPolynomials(const MultivariatePolynomial& , const MultivariatePolynomial&, bool flag = true);
    static MultivariatePolynomial multiplyPolynomials(const MultivariatePolynomial&, const MultivariatePolynomial&, bool flag = true);
    static std::pair<MultivariatePolynomial, std::vector<MultivariatePolynomial>> dividePolynomials(const MultivariatePolynomial&, const MultivariatePolynomial&, bool flag = true);

    friend std::ostream& operator<<(std::ostream& os, MultivariatePolynomial& poly) {
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

    friend bool operator==(const MultivariatePolynomial& lhs, const MultivariatePolynomial& rhs) {
        const std::vector<Term>& lhsTerms = lhs.terms_;
        const std::vector<Term>& rhsTerms = rhs.terms_;

        if (lhsTerms.size() != rhsTerms.size()) {
            return false;
        }

        for (size_t i = 0; i < lhsTerms.size(); i++) {
            if (!(lhsTerms[i] == rhsTerms[i])) {
                return false;
            }
        }

        return true;
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
