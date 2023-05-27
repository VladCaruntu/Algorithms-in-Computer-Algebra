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

//    if(vect.size() > 1)
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

//    std::cout<<"Din functie\n";
//    for(const auto& term: this->terms_) {
//        std::cout << term << "@@@";
//    }
//    std::cout<<"\n";
    if(isPolyZero(*this)){
        tempVector.clear();
        for(size_t index = 0; index < nrOfVars; index++){
            tempVector.push_back(0);
        }
        this->terms_.push_back(Term(boost::rational<int>(0,1), tempVector));
    }
}

MultivariatePolynomial MultivariatePolynomial::addPolynomials(const MultivariatePolynomial& p1, const MultivariatePolynomial& p2){
    std::unique_ptr<MultivariatePolynomial> p_temp = std::make_unique<MultivariatePolynomial>();
    for(const auto& el: p1.terms_){
        p_temp->terms_.push_back(el);
    }
    for(const auto& el: p2.terms_){
        p_temp->terms_.push_back(el);
    }
    p_temp->processPoly();
    return *p_temp;
}

MultivariatePolynomial MultivariatePolynomial::subtractPolynomials(const MultivariatePolynomial& p1, const MultivariatePolynomial& p2){
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
    return *p_temp;
}

MultivariatePolynomial MultivariatePolynomial::multiplyPolynomials(const MultivariatePolynomial& p1, const MultivariatePolynomial& p2){
    std::unique_ptr<MultivariatePolynomial> p_temp = std::make_unique<MultivariatePolynomial>();

    for(const auto& term1: p1.terms_){
        for(const auto& term2: p2.terms_) {
            p_temp->terms_.push_back(term1 * term2);
        }
    }

    p_temp->processPoly();

    return *p_temp;
}

int MultivariatePolynomial::getDegree() const{
    std::unique_ptr<MultivariatePolynomial> p_copy = std::make_unique<MultivariatePolynomial>(*this);
    int sum = 0;

    p_copy->processPoly();
    for(const auto& var_pow: p_copy->terms_[0].term_.second){
        sum += var_pow.second;
    }
    return sum;
}

bool MultivariatePolynomial::canDivide(const MultivariatePolynomial& p1, const MultivariatePolynomial& p2)
{
    //trebuie sa adaug la p2 niste termeni ca sa fie aceeasi marime cu p1
    size_t size1 = p1.terms_.size();
    size_t size2 = p2.terms_.size();

    std::unique_ptr<MultivariatePolynomial> p1_copy = std::make_unique<MultivariatePolynomial>(p1);
    std::unique_ptr<MultivariatePolynomial> p2_copy = std::make_unique<MultivariatePolynomial>(p2);

    if(size1 > size2){
        while(size2 < size1){
            p2_copy->terms_.push_back(Term());
            size2++;
        }
    }
    else{
        while(size1 < size2){
            p1_copy->terms_.push_back(Term());
            size1++;
        }
    }

    size_t i = 0;
    while(i < size1)
    {
        //aici sunt mapele de puteri cu tot cu variabile
        auto term1_term2 = Term::equalizeTerms(p1.terms_[i], p2.terms_[i]);
        std::map<char, int> var_pow1 = term1_term2.first.term_.second;
        std::map<char, int> var_pow2 = term1_term2.second.term_.second;

        std::vector<int> powers1 {};
        std::vector<int> powers2 {};

        for(const auto& el: var_pow1)
        {
            //primul polinom = p1
            powers1.push_back(el.second);
        }

        for(const auto& el: var_pow2)
        {
            //al doilea polinom = p2
            powers2.push_back(el.second);
        }

        //afisam
        //stergi dupa
        for(auto el: powers1)
        {
            std::cout<<el<<" ";
        }
        std::cout<<"\n";
        for(auto el: powers2)
        {
            std::cout<<el<<" ";
        }

        const size_t size = powers1.size();
        for(size_t j = 0; j < size; j++)
        {
            if(powers1[j] < powers2[j])
                return false;
        }

        i++;
    }
    return true;
}

std::pair<MultivariatePolynomial, std::vector<MultivariatePolynomial>> MultivariatePolynomial::dividePolynomials(const MultivariatePolynomial& p1, const MultivariatePolynomial& p2) {
    std::unique_ptr<MultivariatePolynomial> p1_copy = std::make_unique<MultivariatePolynomial>(p1);
    std::unique_ptr<MultivariatePolynomial> p2_copy = std::make_unique<MultivariatePolynomial>(p2);
    p1_copy->processPoly();
    p2_copy->processPoly();

    MultivariatePolynomial quotient;
    MultivariatePolynomial tempPoly;
    MultivariatePolynomial p_temp;
    std::vector<MultivariatePolynomial> reminders{};

    int firstDeg = p1.getDegree();
    const int secondDeg = p2.getDegree();

    std::cout<<canDivide(p1, p2);
    return std::make_pair(*p1_copy, reminders);

    Term tempTerm;
    if(firstDeg >= secondDeg)
    {
        int iter = 1;
        while(firstDeg >= secondDeg)
        {
            std::cout<<"Iteratia " << iter++ << ":\n";
            tempTerm = p1_copy->terms_[0] / p2_copy->terms_[0];
            std::cout<<tempTerm<<'\n';
            tempPoly.addTerm(tempTerm);
            p_temp = MultivariatePolynomial::subtractPolynomials(p1, MultivariatePolynomial::multiplyPolynomials(tempPoly, *p2_copy));
            *p1_copy = p_temp;
            std::cout<<"Poly: " << *p1_copy<<"\n";
            firstDeg = p1_copy->getDegree();
            std::cout<<firstDeg<<"-------"<<secondDeg<<'\n';
            tempPoly.terms_.clear();
            std::cout<<"tempTerm: "<<tempTerm<<"\n";
            quotient.addTerm(tempTerm);
            reminders.push_back(*p1_copy);
        }
        return std::make_pair(quotient, reminders);
    }
    else
    {
        std::cerr << "Error: The first degree must be greater or equal to the second degree!";
        return std::make_pair(*p1_copy, reminders);
    }
}