#include "Polynomial.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <chrono>
#include <iomanip>
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
    this->terms_.push_back(std::make_pair(1, maxDNE + 1));

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
        if(el.first != 0)
            p_temp->terms_.push_back(el);
    }

    this->terms_.clear();
    for(auto& el : p_temp->terms_){
        this->terms_.push_back(el);
    }
}

Polynomial Polynomial::addPoly(const Polynomial& p1, const Polynomial& p2, bool flag) {
    auto startTime = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

    std::unique_ptr<Polynomial> p_temp = std::make_unique<Polynomial>();
    for(const auto& el : p1.terms_){
        p_temp->terms_.push_back(el);
    }

    for(const auto& el : p2.terms_){
        p_temp->terms_.push_back(el);
    }

    p_temp->processPoly();
    p_temp->isProcessed = true;

    auto endTime = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

    time_taken *= 1e-9;
    if(flag) {
        std::cout << "The execution of " << __FUNCTION__ << " took " << std::fixed << time_taken
                  << std::setprecision(10) << " seconds" << std::endl;
    }

    return *p_temp;
}

Polynomial Polynomial::subtractPoly(const Polynomial& p1, const Polynomial& p2, bool flag){
    auto startTime = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

    std::unique_ptr<Polynomial> p_temp = std::make_unique<Polynomial>();

    for(const auto& el: p1.terms_){
        p_temp->terms_.push_back(el);
    }

    for(const auto& el : p2.terms_){
        boost::rational<int> temp_coeff = el.first * (-1);
        p_temp->terms_.push_back(std::make_pair(temp_coeff, el.second));
    }

    p_temp->processPoly();
    p_temp->isProcessed = true;

    auto endTime = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

    time_taken *= 1e-9;
    if(flag) {
        std::cout << "The execution of " << __FUNCTION__ << " took " << std::fixed << time_taken
                  << std::setprecision(10) << " seconds" << std::endl;
    }

    return *p_temp;
}

Polynomial Polynomial::multiplyPoly(const Polynomial& p1, const Polynomial& p2, bool flag){
    auto startTime = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

    std::unique_ptr<Polynomial> p_temp = std::make_unique<Polynomial>();

    int power1, power2;
    boost::rational<int> coef1, coef2, tempCoef;
    int tempPower;
    std::pair<boost::rational<int>, int> tempPair;

    for(size_t i{0}; i < p1.terms_.size(); i++){
        coef1 = p1.terms_[i].first;
        power1 = p1.terms_[i].second;
        for(size_t j{0}; j < p2.terms_.size(); j++){
            coef2 = p2.terms_[j].first;
            power2 = p2.terms_[j].second;
            tempCoef = coef1 * coef2;
            tempPower = power1 + power2;
            tempPair = std::make_pair(tempCoef, tempPower);
            p_temp->terms_.push_back(tempPair);
        }
    }
    p_temp->processPoly();
    p_temp->isProcessed = true;

    auto endTime = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();

    time_taken *= 1e-9;
    if(flag) {
        std::cout << "The execution of " << __FUNCTION__ << " took " << std::fixed << time_taken
                  << std::setprecision(10) << " seconds" << std::endl;
    }

    return *p_temp;
}


std::pair<Polynomial, Polynomial> Polynomial::dividePoly(Polynomial& p1, const Polynomial& p2, bool flag)
{
    Polynomial quotient;
    Polynomial tempPoly;
    std::vector<Polynomial> reminders {};

    int firstDeg = p1.terms_[0].second;
    const int secondDeg = p2.terms_[0].second;

    if(firstDeg >= secondDeg)
    {
        while(firstDeg >= secondDeg)
        {
            std::pair<boost::rational<int>, int> tempTerm;
            tempTerm = std::make_pair(p1.terms_[0].first / p2.terms_[0].first, p2.terms_[0].second - p1.terms_[0].second);

            tempPoly.addTerm(tempTerm);
            p1 = Polynomial::subtractPoly(p1, Polynomial::multiplyPoly(tempPoly, p2));
            quotient.addTerm(tempTerm);
            reminders.push_back(p1);
        }
        return std::make_pair(quotient, reminders.at(reminders.size() - 1));
    }
    else
    {
        std::cerr << "Error: The first degree must be greater or equal to the second degree!";
        return std::make_pair(p1, p2);
    }
}

void Polynomial::printPoly() {
    if(!this->isProcessed) {
        this->processPoly();
        this->isProcessed = true;
    }

    boost::rational<int> coef{this->terms_[0].first};
    int power{this->terms_[0].second};

    // for the first term
    if(power == 1) {
        std::cout << coef << "x";
    }
    else {
        std::cout << coef << "x^" << power;
    }

    //for the rest of the terms
    for (size_t i{1}; i < this->terms_.size(); i++) {
        coef = this->terms_[i].first;
        power = this->terms_[i].second;

        if (power == 1) {
            if (coef < 0) {
                std::cout << coef << "x";
            }
            else {
                std::cout << "+" << coef << "x";
            }
        }
        else if (power > 1){
            if (coef < 0) {
                std::cout << coef << "x^" << power;
            }
            else {
                std::cout << "+" << coef << "x^" << power;
            }
        }
        else {
            if (coef < 0) {
                std::cout << coef;
            }
            else {
                std::cout << "+" << coef;
            }
        }
    }
    std::cout << "=0\n";
}