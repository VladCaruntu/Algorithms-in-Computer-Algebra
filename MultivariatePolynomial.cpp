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
    if(this->terms_.size() > 1) {
        this->processPoly();
    }
}

int MultivariatePolynomial::sumOfPowers(const Term& term){
    int sum = 0;
    for(const auto& monomial: term.term_.second){
        sum += monomial.second;
    }
    return sum;
}

bool compareTermAlphabeticallyWithExistingVariables(const Term& t1, const Term& t2)
{
    const std::map<char, int>& term1Powers = t1.term_.second;
    const std::map<char, int>& term2Powers = t2.term_.second;

    // Iterate over the existing variables in each term and compare alphabetically
    for (const auto& term : term1Powers)
    {
        const auto& var1 = term.first;
        const auto& power1 = term.second;

        if (term2Powers.count(var1) == 0)
        {
            // Variable in t1 does not exist in t2, so t1 comes first
            return true;
        } else
        {
            // Compare the powers of the common variable alphabetically
            int power2 = term2Powers.at(var1);
            if (power1 != power2)
            {
                return power1 > power2;
            }
        }
    }

    // All variables in t1 exist in t2 or there are no variables in t1
    // Compare remaining variables in t2 that don't exist in t1
    for (const auto& [var2, _] : term2Powers)
    {
        if (term1Powers.count(var2) == 0)
        {
            // Variable in t2 does not exist in t1, so t2 comes first
            return false;
        }
    }
    // All variables are equal, shorter term comes first
    return term1Powers.size() < term2Powers.size();
}

void MultivariatePolynomial::sortPoly(int flag) {
    switch (flag) {
        case 0:
            std::sort(this->terms_.begin(), this->terms_.end(),
                      [this](const Term& t1, const Term& t2) {
                          int sum1 = sumOfPowers(t1);
                          int sum2 = sumOfPowers(t2);

                          if (sum1 != sum2) {
                              return sum1 > sum2;
                          }
                          return compareTermAlphabeticallyWithExistingVariables(t1, t2);
                      }
            );
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
    size_t nrOfVars = this->terms_[0].term_.second.size();
    std::vector<int> tempVector (nrOfVars, maxDNE + 1);
    this->terms_.push_back(Term(boost::rational<int>(1,1), tempVector));
    size_t i = 0;
    while(i < this->terms_.size()){
        if(this->terms_[i] == this->terms_[i + 1]){
            tempCoeff += this->terms_[i].term_.first;
        }
        else {
            tempCoeff += this->terms_[i].term_.first;
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

MultivariatePolynomial MultivariatePolynomial::addPolynomials(const MultivariatePolynomial& p1, const MultivariatePolynomial& p2, bool flag){
    auto startTime = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

    std::unique_ptr<MultivariatePolynomial> p_temp = std::make_unique<MultivariatePolynomial>();
    for(const auto& el: p1.terms_){
        p_temp->terms_.push_back(el);
    }
    for(const auto& el: p2.terms_){
        p_temp->terms_.push_back(el);
    }
    p_temp->processPoly();

    auto endTime = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
    time_taken *= 1e-9;
    if(flag) {
        std::cout << "The execution of " << __PRETTY_FUNCTION__ << " took " << std::fixed << time_taken
                  << std::setprecision(10) << " seconds" << std::endl;
    }
    return *p_temp;
}

MultivariatePolynomial MultivariatePolynomial::subtractPolynomials(const MultivariatePolynomial& p1, const MultivariatePolynomial& p2, bool flag){
    auto startTime = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

    std::unique_ptr<MultivariatePolynomial> p_temp = std::make_unique<MultivariatePolynomial>();
    std::unique_ptr<MultivariatePolynomial> p2_copy = std::make_unique<MultivariatePolynomial>(p2);
    for(const auto& el: p1.terms_){
        p_temp->terms_.push_back(el);
    }

    for(auto& el: p2_copy->terms_){
        el.term_.first *= -1;
        p_temp->terms_.push_back(el);
    }

    p_temp->processPoly();

    auto endTime = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
    time_taken *= 1e-9;
    if(flag) {
        std::cout << "The execution of " << __PRETTY_FUNCTION__ << " took " << std::fixed << time_taken
                  << std::setprecision(10) << " seconds" << std::endl;
    }
    return *p_temp;
}

MultivariatePolynomial MultivariatePolynomial::multiplyPolynomials(const MultivariatePolynomial& p1, const MultivariatePolynomial& p2, bool flag){
    auto startTime = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

    std::unique_ptr<MultivariatePolynomial> p_temp = std::make_unique<MultivariatePolynomial>();

    for(const auto& term1: p1.terms_){
        for(const auto& term2: p2.terms_) {
            p_temp->terms_.push_back(term1 * term2);
        }
    }

    p_temp->processPoly();

    auto endTime = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
    time_taken *= 1e-9;
    if(flag) {
        std::cout << "The execution of " << __PRETTY_FUNCTION__ << " took " << std::fixed << time_taken
                  << std::setprecision(10) << " seconds" << std::endl;
    }
    return *p_temp;
}

std::vector<int> MultivariatePolynomial::getDegree(MultivariatePolynomial& p, bool flag)
{
    for(size_t i = 0; i < p.terms_.size() - 1; i++)
    {
        for(size_t j = 0; j < p.terms_.size(); j++)
        {
            Term::equalizeTerms(p.terms_[i], p.terms_[j]);
        }
    }
    size_t nrOfVariables = p.terms_[0].term_.second.size();

    std::vector<int> powers;
    //initialization
    if(flag) // for max
    {
        powers = std::vector<int>(nrOfVariables, -1);
    }
    else
    {
        powers = std::vector<int>(nrOfVariables, INFINITY);
    }

    size_t i = 0;
    for(const auto& term: p.terms_)
    {
        for(const auto& monomial: term.term_.second)
        {
            if(flag)
            {
                powers[i++] = std::max(powers[i], monomial.second);
            }
            else{
                powers[i++] = std::min(powers[i], monomial.second);
            }
        }
        i = 0;
    }
    return powers;
}

bool MultivariatePolynomial::canDivide(const MultivariatePolynomial& p1, const MultivariatePolynomial& p2)
{
    std::unique_ptr<MultivariatePolynomial> p1_copy = std::make_unique<MultivariatePolynomial>(p1);
    std::unique_ptr<MultivariatePolynomial> p2_copy = std::make_unique<MultivariatePolynomial>(p2);
    //if p2 is 0
    if(p2.terms_.size() == 1 && p2.terms_[0].term_.first == 0)
        return false;

    size_t maxVariablesP2 = 0, maxVariablesP1 = 0;
    //Each variable in the dividend should also appear in the divisor, and vice versa
    for(const auto & term : p1.terms_)
    {
        maxVariablesP1 = std::max(maxVariablesP1, term.term_.second.size());
    }
    for(const auto & term : p2.terms_)
    {
        maxVariablesP2 = std::max(maxVariablesP2, term.term_.second.size());
    }
    if(maxVariablesP1 != maxVariablesP2)
    {
        return false;
    }

    std::vector<int> deg1 = getDegree(*p1_copy,false);
    std::vector<int> deg2 = getDegree(*p2_copy, true);
    size_t size = deg1.size();

    for(size_t i = 0; i < size; i++)
    {
        if(deg1[i] < deg2[i])
        {
            return false;
        }
    }
    return true;
}

std::pair<MultivariatePolynomial, std::vector<MultivariatePolynomial>> MultivariatePolynomial::dividePolynomials(const MultivariatePolynomial& p1, const MultivariatePolynomial& p2, bool flag)
{
    auto startTime = std::chrono::high_resolution_clock::now();
    std::ios_base::sync_with_stdio(false);

    MultivariatePolynomial p1_copy = p1;
    MultivariatePolynomial p2_copy = p2;
    int nrOfVars = p1.terms_[0].term_.second.size();

    MultivariatePolynomial quotient;
    MultivariatePolynomial tempPoly;
    MultivariatePolynomial p_temp;
    std::vector<MultivariatePolynomial> reminders{};

    std::vector<int> firstDeg = getDegree(p1_copy);
    const std::vector<int> secondDeg = getDegree(p2_copy);

    Term tempTerm = Term(boost::rational<int>(0, 1),{0});
    if(canDivide(p1, p2))
    {
        while(canDivide(p1_copy, p2_copy))
        {
            tempTerm = p1_copy.terms_[0] / p2_copy.terms_[0];
            tempPoly.addTerm(tempTerm);
            MultivariatePolynomial multiplication_result = MultivariatePolynomial::multiplyPolynomials(tempPoly, p2_copy, false);
            MultivariatePolynomial subtraction_result = MultivariatePolynomial::subtractPolynomials(p1_copy, multiplication_result, false);
            p1_copy = subtraction_result;
            quotient.addTerm(tempTerm);
            reminders.push_back(p1_copy);
            tempPoly.terms_.clear();
        }

        std::unique_ptr<MultivariatePolynomial> poly = std::make_unique<MultivariatePolynomial>();
        std::vector<int> tempVector {};
        for(size_t index = 0; index < nrOfVars; index++){
            tempVector.push_back(0);
        }
        poly->terms_.push_back(Term(boost::rational<int>(0,1), tempVector));

        if(reminders[reminders.size() - 1] == *poly)
        {
            if(!canDivide(reminders[reminders.size() - 2], p2))
                std::cout<<"The GCD of the 2 polynomials is: " << reminders[reminders.size() - 2] << "\n";
            else
                std::cout<<"The GCD of the 2 polynomials is: " << p2_copy << "\n";
        }
        else
        {
            std::cout<<"The GCD of the 2 polynomials is: 1\n";
        }

        auto endTime = std::chrono::high_resolution_clock::now();
        double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
        time_taken *= 1e-9;
        if(flag) {
            std::cout << "The execution of " << __PRETTY_FUNCTION__ << " took " << std::fixed << time_taken
                      << std::setprecision(10) << " seconds" << std::endl;
        }
        return std::make_pair(quotient, reminders);
    }
    else
    {
        std::cerr << "Error: The first degree must be greater or equal to the second degree!\n";
        return std::make_pair(p1_copy, reminders);
    }
}