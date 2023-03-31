#include "Polynomial.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "boost/rational.hpp"

void Polynomial::addTerm(const std::pair<boost::rational<int>, int>& term) {
    this->terms_.push_back(term);
}

std::vector<std::pair<boost::rational<int>, int>> Polynomial::getTerms(const Polynomial& poly){
    return this->terms_;
}

void Polynomial::sortPoly() {
    std::sort(this->terms_.begin(), this->terms_.end(),
              [](std::pair<boost::rational<int>, int> t1, std::pair<boost::rational<int>, int>t2) {
                  return t1.second > t2.second;}
    );
}

void Polynomial::processPoly() {
    this->sortPoly();

    std::unique_ptr<Polynomial> p_temp = std::make_unique<Polynomial>();
    std::vector<std::pair<boost::rational<int>, int>> vect;
    size_t i{ 0 };
    int maxDNE = 0;
    for(const auto& el : this->terms_)
        maxDNE = std::max(maxDNE, el.second);

    boost::rational<int> tempCoeff{ 0 };
    this->addTerm(std::make_pair(1, maxDNE + 1));

    while (i < this->terms_.size()) {
        if (this->terms_[i].second == this->terms_[i + 1].second) {
            tempCoeff += this->terms_[i].first;
        }
        else {
            tempCoeff += this->terms_[i].first;
            std::pair<boost::rational<int>, int> tempPair = std::make_pair(tempCoeff, this->terms_[i].second);
            vect.push_back(tempPair);
            tempCoeff = 0;
        }
        ++i;
    }

    vect.pop_back();

    for (const std::pair<boost::rational<int>, int> el : vect) {
        p_temp->addTerm(el);
    }

    this->terms_.clear();
    for(auto& el : p_temp->terms_){
        this->addTerm(el);
    }
}

void Polynomial::addPoly(const Polynomial& p) {
    std::unique_ptr<Polynomial> p_temp = std::make_unique<Polynomial>();

    for(const auto& el: this->terms_){
        p_temp->addTerm(el);
    }
    for(const auto& el: p.terms_){
        p_temp->addTerm(el);
    }

    p_temp->processPoly();

    this->terms_.clear();
    for(const auto& el : p_temp->terms_){
        if(el.first != 0)
            this->addTerm(el);
    }
}

void Polynomial::subtractPoly(const Polynomial& p){
    std::unique_ptr<Polynomial> p_temp = std::make_unique<Polynomial>();

    for(const auto& el: this->terms_){
        p_temp->addTerm(el);
    }
    for(const auto& el : p.terms_){
        boost::rational<int> temp_coeff = el.first * (-1);
        p_temp->addTerm(std::make_pair(temp_coeff, el.second));
    }

    p_temp->processPoly();

    this->terms_.clear();
    for(const auto& el : p_temp->terms_){
        if(el.first != 0)
            this->addTerm(el);
    }
}

Polynomial Polynomial::multiplyPoly(Polynomial& p){
    std::unique_ptr<Polynomial> p_temp = std::make_unique<Polynomial>();

    int power1, power2;
    boost::rational<int> coef1, coef2, tempCoef;
    int tempPower;
    std::pair<boost::rational<int>, int> tempPair;

    for(size_t i{0}; i < this->terms_.size(); i++){
        coef1 = this->terms_[i].first;
        power1 = this->terms_[i].second;
        for(size_t j{0}; j < p.terms_.size(); j++){
            coef2 = p.terms_[j].first;
            power2 = p.terms_[j].second;
            tempCoef = coef1 * coef2;
            tempPower = power1 + power2;
            tempPair = std::make_pair(tempCoef, tempPower);
            p_temp->addTerm(tempPair);
        }
    }
    this->terms_.clear();
    for(const auto& el : p_temp->terms_){
        this->addTerm(el);
    }
    this->processPoly();
    return *this;
}

void Polynomial::printPoly() {
//    if(!this->isSorted){
//        this->sortPoly();
//        this->isSorted = true;
//    }
    this->processPoly();

    boost::rational<int> coef{};
    int power{};

    for (size_t i{0}; i < this->terms_.size(); i++) {
        coef = this->terms_[i].first;
        power = this->terms_[i].second;

        if (power > 1) {
            if (coef > 1 && i != 0) {
                std::cout << "+" << coef << "x" << "^" << power;
            }
            else if(coef > 1){
                std::cout << coef << "x" << "^" << power;
            }
            else if (coef < 1) {
                std::cout << coef << "x" << "^" << power;
            }
            else if (coef == 1){
                std::cout << "x" << "^" << power;
            }
            else {
                std::cout << "+" << "x" << "^" << power;
            }
        } else if (power == 1) {
            if (coef > 1 && i != 0) {
                std::cout << "+" << coef << "x";
            }
            else if(coef > 1){
                std::cout << coef << "x";
            }
            else if (coef < 1) {
                std::cout << "+" << coef << "x";
            }
            else {
                std::cout << "x" << "^" << power;
            }
        } else {
            if (coef > 0 && i != 0) {
                std::cout << "+" << coef;
            }
            else if(coef > 1){
                std::cout << coef;
            }
            else {
                std::cout << coef;
            }
        }
    }
    std::cout << "=0";
}