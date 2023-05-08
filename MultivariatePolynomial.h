#ifndef COD_MULTIVARIATEPOLYNOMIAL_H
#define COD_MULTIVARIATEPOLYNOMIAL_H
#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
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
    MultivariatePolynomial factorize();
    static MultivariatePolynomial addPolynomials(const MultivariatePolynomial& , const MultivariatePolynomial&);
    static MultivariatePolynomial subtractPolynomials(const MultivariatePolynomial& , const MultivariatePolynomial&);
    static MultivariatePolynomial multiplyPolynomials(const MultivariatePolynomial&, const MultivariatePolynomial&);

    friend std::ostream& operator<<(std::ostream& os, const MultivariatePolynomial& poly) {
        bool first_term = true;
        for (auto it = poly.terms.begin(); it != poly.terms.end(); ++it) {
            if (!first_term && it->coefficient > 0) {
                os << " + ";
            }
            else if (!first_term && it->coefficient < 0){
                os << " ";
            }
            else{
                first_term = false;
            }
            if(it->coefficient != 1) {
                os << it->coefficient << "*";
            }

            bool first_var = true;
            for (auto var_it = it->variables.begin(); var_it != it->variables.end(); ++var_it) {
                //var_it->first  === variabila
                //var_it->second === putere
                if (!first_var) {
                    os << "*";
                } else {
                    first_var = false;
                }

                if (var_it->second > 1) {//>0
                    os << var_it->first << "^" << var_it->second;//puterea
                }
                else if (var_it->second == 1){
                    os << var_it->first;
                }
                else {
                    os << it->coefficient;
                }
            }
        }
        return os;
    }
};

#endif
