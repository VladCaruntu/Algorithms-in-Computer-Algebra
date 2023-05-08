#include "MultivariatePolynomial.h"
#include "EuclideanAlgorithm.h"

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
        bool found = false;
        for (auto& t : terms) {
            if (t.variables == term.variables) {
                t.coefficient += term.coefficient;
                found = true;
                break;
            }
        }
        if (!found) {
            terms.push_back(term);
        }
    }
}

void MultivariatePolynomial::subtract(const MultivariatePolynomial& other) {
    for (const auto& term : other.terms) {
        bool found = false;
        for (auto& t : terms) {
            if (t.variables == term.variables) {
                t.coefficient -= term.coefficient;
                found = true;
                break;
            }
        }
        if (!found) {
            terms.push_back(Term(-term.coefficient, term.variables));
        }
    }
}

//MultivariatePolynomial MultivariatePolynomial::factorize() {
//    MultivariatePolynomial result;
//    std::vector<std::pair<double, std::unordered_map<char, int>>> terms_to_factorize;
//
//    for (const auto& term : terms) {
//        double coefficient = term.coefficient;
//        std::unordered_map<char, int> variables = term.variables;
//
//        for (auto& [variable, power] : variables) {
//            if (power < 0) {
//                throw std::logic_error("Cannot factorize polynomial with negative powers.");
//            }
//            if (power == 0) {
//                coefficient *= variable;
//                power = 0;
//            }
//            else {
//                double root = std::sqrt(variable);
//                if (std::abs(std::round(root) - root) < 1e-9) {
//                    coefficient *= std::pow(root, power);
//                    variables[variable] = root;
//                    power = 0;
//                }
//            }
//        }
//
//        if (variables.empty()) {
//            terms_to_factorize.emplace_back(coefficient, std::unordered_map<char, int>{});
//        }
//        else {
//            terms_to_factorize.emplace_back(coefficient, std::move(variables));
//        }
//    }
//
//    std::vector<MultivariatePolynomial> factorized_terms;
//    for (const auto& [coefficient, variables] : terms_to_factorize) {
//        if (coefficient == 0) continue;
//        MultivariatePolynomial term;
//        term.addTerm(coefficient, variables);
//        factorized_terms.push_back(std::move(term));
//    }
//
//    if (factorized_terms.empty()) {
//        result.addTerm(0.0, {});
//        return result;
//    }
//
//    result = std::move(factorized_terms[0]);
//    for (size_t i = 1; i < factorized_terms.size(); ++i) {
//        result = multiplyPolynomials(result, factorized_terms[i].gcd(result));
//    }
//
//    return result;
//}
// Factorize a given coefficient

//MultivariatePolynomial MultivariatePolynomial::factorize() {
//    MultivariatePolynomial result;
//
//    if (terms.size() <= 1) {
//        // A polynomial with one or zero terms cannot be factorized.
//        return *this;
//    }
//
//    // Compute the gcd of all the coefficients.
//    int gcd = std::abs(terms.front().coefficient);
//    for (const auto& term : terms) {
//        gcd = EuclideanAlgorithm::euclideanAlgorithmWithDivisions(gcd, static_cast<int>(std::abs(term.coefficient)));
//    }
//
//    // If the gcd is not 1, factor it out.
//    if (gcd != 1) {
//        MultivariatePolynomial common_term;
//        common_term.addTerm(gcd, {});
//        for (auto& term : terms) {
//            term.coefficient /= gcd;
//        }
//        result.push_back(common_term);
//    }
//
//    // Collect the variables.
//    std::unordered_set<char> variables;
//    for (const auto& term : terms) {
//        for (const auto& variable_pair : term.variables) {
//            variables.insert(variable_pair.first);///verifici aici daca nu merge
//        }
//    }
//
//    // Sort the variables.
//    std::vector<char> sorted_variables(variables.begin(), variables.end());
//    std::sort(sorted_variables.begin(), sorted_variables.end());
//
//    // Factorize each variable.
//    for (const auto& variable : sorted_variables) {
//        MultivariatePolynomial factorized_polynomial;
//        for (const auto& term : terms) {
//            if (term.variables.count(variable) == 0) {
//                // This term does not contain the variable, so add it to the result unchanged.
//                factorized_polynomial.addTerm(term.coefficient, term.variables);
//            } else {
//                // This term contains the variable, so factorize it.
//                auto new_term = term;
//                new_term.variables.erase(variable);
//                factorized_polynomial.addTerm(term.coefficient, new_term.variables);
//            }
//        }
//        result.push_back(factorized_polynomial.factorize()); ///linie care trebuie modificata
//    }
//
//    return result;
//}


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

MultivariatePolynomial MultivariatePolynomial::multiplyPolynomials(const MultivariatePolynomial& p1, const MultivariatePolynomial& p2) {
    MultivariatePolynomial result;

    // Multiply each term in p1 by each term in p2
    for (const auto& term1 : p1.terms) {
        for (const auto& term2 : p2.terms) {
            // Multiply the coefficients
            double coefficient = term1.coefficient * term2.coefficient;

            // Multiply the variables
            std::unordered_map<char, int> variables = term1.variables;
            for (const auto& variable : term2.variables) {
                if (variables.find(variable.first) == variables.end()) {
                    variables[variable.first] = 0;
                }
                variables[variable.first] += variable.second;
            }

            // Add the resulting term to the result polynomial
            result.addTerm(coefficient, variables);
        }
    }
    return result;
}
