#ifndef COD_MULTIVARIATEPOLYNOMIAL_H
#define COD_MULTIVARIATEPOLYNOMIAL_H
#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <cmath>

struct Term {
    double coefficient = 0.0;
    std::unordered_map<char, int> variables {};

    Term(double c, std::unordered_map<char, int> v) : coefficient(c), variables(std::move(v)) {}
};

class MultivariatePolynomial {
private:
    std::vector<Term> terms;

public:
    void addTerm(double, const std::unordered_map<char, int>&);
    double evaluate(std::unordered_map<char, double>);
    void add(const MultivariatePolynomial&);
    void subtract(const MultivariatePolynomial&);
    std::vector<MultivariatePolynomial> factorize();
    static MultivariatePolynomial addPolynomials(const MultivariatePolynomial& , const MultivariatePolynomial&);
    static MultivariatePolynomial subtractPolynomials(const MultivariatePolynomial& , const MultivariatePolynomial&);
};

#endif
