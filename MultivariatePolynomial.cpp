#include "MultivariatePolynomial.h"

    // Add a term to the polynomial
void MultivariatePolynomial::addTerm(double coefficient, const std::unordered_map<char, int>& variables) {
    terms.push_back(Term(coefficient, variables));
}

// Evaluate the polynomial at a given point
double MultivariatePolynomial::evaluate(std::unordered_map<char, double> point) {
    double result = 0.0;
    for (const auto& term : terms) {
        double termResult = term.coefficient;
        for (const auto& variable : term.variables) {
            if (point.find(variable.first) == point.end()) {
                throw std::invalid_argument("Missing variable in point");
            }
            termResult *= pow(point[variable.first], variable.second);
        }
        result += termResult;
    }
    return result;
}

void MultivariatePolynomial::add(const MultivariatePolynomial& other) {
    for (const auto& term : other.terms) {
        terms.push_back(term);
    }
}

void MultivariatePolynomial::subtract(const MultivariatePolynomial& other) {
    for (const auto& term : other.terms) {
        terms.push_back(Term(-term.coefficient, term.variables));
    }
}

std::vector<MultivariatePolynomial> MultivariatePolynomial::factorize() {
    std::vector<MultivariatePolynomial> factors;
    if (terms.size() == 1) {
        factors.push_back(*this);
        return factors;
    }
    // Check if the polynomial is a perfect square
    bool isSquare = true;
    std::unordered_map<char, int> vars = terms[0].variables;
    double coefficient = terms[0].coefficient;
    for (const auto& term : terms) {
        if (term.variables != vars) {
            isSquare = false;
            break;
        }
        if (term.coefficient != coefficient) {
            isSquare = false;
            break;
        }
    }
    if (isSquare) {
        MultivariatePolynomial factor;
        factor.addTerm(sqrt(coefficient), vars);
        factors.push_back(factor);
        return factors;
    }
    //Implement more advanced polynomial factorization algorithms
    factors.push_back(*this);
    return factors;
}

MultivariatePolynomial MultivariatePolynomial::addPolynomials(const MultivariatePolynomial& p1, const MultivariatePolynomial& p2) {
    MultivariatePolynomial result = p1;
    result.add(p2);
    return result;
}

MultivariatePolynomial MultivariatePolynomial::subtractPolynomials(const MultivariatePolynomial& p1, const MultivariatePolynomial& p2) {
    MultivariatePolynomial result = p1;
    result.subtract(p2);
    return result;
}