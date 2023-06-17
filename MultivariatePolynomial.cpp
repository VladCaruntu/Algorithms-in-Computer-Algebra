#include "MultivariatePolynomial.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <chrono>
#include <iomanip>
#include "boost/rational.hpp"

void MultivariatePolynomial::lexicographicSort()
{
    std::sort(this->terms_.begin(), this->terms_.end(),
              [this](const Term& t1, const Term& t2){
                  const auto var_pow1 = t1.term_.second;
                  const auto var_pow2 = t2.term_.second;
                  auto it1 = var_pow1.begin();
                  auto it2 = var_pow2.begin();
                  while(it1 != var_pow1.end() || it2 != var_pow2.end())
                  {
                      if(it1->second != it2->second)
                          return it1->second > it2->second;
                      it1++;
                      it2++;
                  }
              });
}

void MultivariatePolynomial::degreeSort()
{
    std::sort(this->terms_.begin(), this->terms_.end(),
              [this](const Term& t1, const Term& t2) {
                  int sum1 = sumOfPowers(t1);
                  int sum2 = sumOfPowers(t2);

                  if (sum1 != sum2) {
                      return sum1 > sum2;
                  }
              }
    );
}

void MultivariatePolynomial::degreeLexicographicSort()
{
    this->degreeSort();
    size_t size = this->terms_.size();
    for(size_t i = 0; i < size - 1; i++)
    {
        if(sumOfPowers(this->terms_[i]) == sumOfPowers(this->terms_[i + 1]))
        {
            if(this->terms_[i] < this->terms_[i + 1])
            {
                std::swap(this->terms_[i], this->terms_[i + 1]);
            }
        }
    }
}

void MultivariatePolynomial::SORTING_TEST(const std::string& flag)
{
    int choice = 0;
    if(flag == "deg")
        choice = 1;
    else if (flag == "lex")
        choice = 2;
    else if(flag == "deglex")
        choice = 3;

    switch (choice)
    {
        case 1:
            //for graded sorting
            this->degreeSort();
            break;
        case 2:
            //for lexicographic sorting
            this->lexicographicSort();
            break;
        case 3:
            //for graded lexicographic sorting
            this->degreeLexicographicSort();
            break;
    }
}

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

void MultivariatePolynomial::sortPoly() {
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

//    std::cout<<"MultiplyPoly -> Begin\n";
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
//    std::cout<<"MultiplyPoly -> End\n";
    return *p_temp;
}

std::vector<int> MultivariatePolynomial::getDegree(MultivariatePolynomial& p)
{
    size_t nrOfVariables = p.terms_[0].term_.second.size();
    std::vector<int> powers {};
    powers.reserve(nrOfVariables);

    const auto term = p.terms_[0].term_.second;
    for(auto var_pow : term)
        powers.push_back(var_pow.second);

//    for(const auto& term : p.terms_)
//    {
//        for(const auto& var_pow: term.term_.second)
//        {
//            powers[i++] = std::max(powers[i], var_pow.second);
//        }
//        i = 0;
//    }
    return powers;
}

bool MultivariatePolynomial::canDivide(const MultivariatePolynomial& p1, const MultivariatePolynomial& p2)
{
    std::unique_ptr<MultivariatePolynomial> p1_copy = std::make_unique<MultivariatePolynomial>(p1);
    std::unique_ptr<MultivariatePolynomial> p2_copy = std::make_unique<MultivariatePolynomial>(p2);
    //if p2 is 0
    if(p2.terms_.size() == 1 && p2.terms_[0].term_.first == 0)
        return false;

    std::vector<int> deg1 = getDegree(*p1_copy);
    std::vector<int> deg2 = getDegree(*p2_copy);
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

std::pair<MultivariatePolynomial, std::vector<MultivariatePolynomial>> MultivariatePolynomial::dividePolynomials(const MultivariatePolynomial& p1, const MultivariatePolynomial& p2, const std::string& sort, bool flag)
{
//    auto startTime = std::chrono::high_resolution_clock::now();
//    std::ios_base::sync_with_stdio(false);

    int choice = 0;
    if(sort == "deg")
        choice = 1;
    else if (sort == "lex")
        choice = 2;
    else if(sort == "deglex")
        choice = 3;

    switch (choice) {
        case 1:
            std::cout<<"Reverse Degree ordering\n";
            break;
        case 2:
            std::cout<<"Lexicographical ordering\n";
            break;
        case 3:
            std::cout<<"Reverse Degree-lexicographic ordering\n";
            break;
        default:
            std::cout<<"Unknown ordering\n";
            break;
    }

    MultivariatePolynomial p1_copy = p1;
    MultivariatePolynomial p2_copy = p2;

    size_t nrOfVars = p1.terms_[0].term_.second.size();
    p1_copy.SORTING_TEST(sort);
    p2_copy.SORTING_TEST(sort);
    std::cout<<p1_copy << "\n";
    std::cout<<p2_copy << "\n";

    MultivariatePolynomial quotient;
    MultivariatePolynomial tempPoly;
    MultivariatePolynomial p_temp;
    std::vector<MultivariatePolynomial> reminders{};

    std::vector<int> firstDeg = getDegree(p1_copy);
    const std::vector<int> secondDeg = getDegree(p2_copy);
    Term tempTerm = Term(boost::rational<int>(0, 1),{0});

    if(canDivide(p1_copy, p2_copy))
    {
        while(canDivide(p1_copy, p2_copy))
        {
            tempTerm = p1_copy.terms_[0] / p2_copy.terms_[0];
            tempPoly.addTerm(tempTerm);
            std::cout<<"tempPoly: " << tempPoly << "\n";
            std::cout<<"2\n";
            MultivariatePolynomial multiplication_result = MultivariatePolynomial::multiplyPolynomials(tempPoly, p2_copy, false);
            std::cout<<"3\n";
            multiplication_result.SORTING_TEST(sort);///
            std::cout<<"multiplication_result: " << multiplication_result << "\n";
            MultivariatePolynomial subtraction_result = MultivariatePolynomial::subtractPolynomials(p1_copy, multiplication_result, false);
            subtraction_result.SORTING_TEST(sort);
            std::cout<<"subtraction_result: " << subtraction_result << "\n";
            p1_copy = subtraction_result;
//            p1_copy.SORTING_TEST(sort);
            std::cout<<"Temp: "<<p1_copy<<"\n";
            quotient.addTerm(tempTerm);
            reminders.push_back(p1_copy);
            tempPoly.terms_.clear();
        }
//        std::cout<<"Afara din while!\n";
        quotient.SORTING_TEST(sort);
        for(auto& reminder: reminders)
            reminder.SORTING_TEST(sort);

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

//        auto endTime = std::chrono::high_resolution_clock::now();
//        double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
//        time_taken *= 1e-9;
//        if(flag) {
//            std::cout << "The execution of " << __PRETTY_FUNCTION__ << " took " << std::fixed << time_taken
//                      << std::setprecision(10) << " seconds" << std::endl;
//        }
        return std::make_pair(quotient, reminders);
    }
    else
    {
        std::cerr << "Error: The first degree must be greater or equal to the second degree!\n";
        std::unique_ptr<std::vector<MultivariatePolynomial>> tempVect = std::make_unique<std::vector<MultivariatePolynomial>>();
        tempVect->push_back(p2_copy);
//        auto endTime = std::chrono::high_resolution_clock::now();
//        double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
//        time_taken *= 1e-9;
//        if(flag) {
//            std::cout << "The execution of " << __PRETTY_FUNCTION__ << " took " << std::fixed << time_taken
//                      << std::setprecision(10) << " seconds" << std::endl;
//        }
        return std::make_pair(p1_copy, *tempVect);
    }
}
