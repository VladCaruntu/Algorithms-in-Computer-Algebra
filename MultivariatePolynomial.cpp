#include "MultivariatePolynomial.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <chrono>
#include <iomanip>
#include "boost/rational.hpp"

void MultivariatePolynomial::addTerm(const Term &term) {
    this->terms_.push_back(term);
}

int MultivariatePolynomial::sumOfPowers(const Term& term){
    int sum = 0;
    for(const auto& monomial: term.term_.second){
        sum += monomial.second;
    }
    return sum;
}

void MultivariatePolynomial::sortPoly(int flag) {
    switch (flag) {
        case 0:
            std::sort(this->terms_.begin(), this->terms_.end(),
                      [this](const Term &t1, const Term &t2){
                return sumOfPowers(t1) > sumOfPowers(t2);
            });
            break;

        case 1:
            break;

        case 2:
            break;
    }
}

bool MultivariatePolynomial::isPolyZero(const MultivariatePolynomial &poly) {
    return poly.terms_.empty();
}

void MultivariatePolynomial::processPoly(){
    this->sortPoly();

    std::unique_ptr<MultivariatePolynomial> p_temp = std::make_unique<MultivariatePolynomial>();
    std::vector<Term> vect;
    int maxDNE = 0;

    for(const auto& term: this->terms_){
        for(const auto& monomial: term.term_.second){
            maxDNE = std::max(maxDNE, monomial.second);
        }
    }

    boost::rational<int> tempCoeff = 0;
    int nrOfVars = this->terms_[0].term_.second.size();
    std::vector<int> tempVector (nrOfVars, maxDNE);
    this->terms_.push_back(Term(boost::rational<int>(1,1), tempVector));

    size_t i = 0;
    while(i < this->terms_.size()){
        //aici compar monoamele
        if(this->terms_[i].term_ == this->terms_[i + 1].term_){
            tempCoeff += this->terms_[i].term_.first;
        }
        else {
            tempCoeff += this->terms_[i].term_.first;
            //el aici are toata mapa...mie imi trebuie doar puterile variabilelor...
            std::vector<int> tempPowers{};
            for(const auto& varPow: this->terms_[i].term_.second){
                tempPowers.push_back(varPow.second);
            }
            Term tempTerm = Term(tempCoeff, tempPowers);
            vect.push_back(tempTerm);
            tempCoeff = 0;
        }
        ++i;
    }

    vect.pop_back();

    for(const auto& el: vect){
        if(el.term_.first != 0){
            p_temp->terms_.push_back(el);
        }
    }

    this->terms_.clear();
    for(const auto& el: p_temp->terms_){
        this->terms_.push_back(el);
    }

    if(isPolyZero(*this)){
        tempVector.clear();
        for(size_t index = 0; index < nrOfVars; index++){
            tempVector.push_back(0);
        }
        this->terms_.push_back(Term(boost::rational<int>(0,1), tempVector));
    }
}

