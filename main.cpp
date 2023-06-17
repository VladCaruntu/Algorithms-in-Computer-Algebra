#include <iostream>
#include <vector>
#include <boost/rational.hpp>

#include "EuclideanAlgorithm.h"
#include "ChineseRemainderAlgorithm.h"
#include "ExtendedEuclideanAlgorithm.h"
#include "Interpolation.h"
#include "FastFourierTransform.h"
#include "Polynomial.h"
#include "MultivariatePolynomial.h"

int main() {
    //euclidean algorithm
//    std::cout << EuclideanAlgorithm::euclideanAlgorithmWithSubtractions(16384,32, true) << std::endl;
//    std::cout << EuclideanAlgorithm::euclideanAlgorithmWithDivisions(16384,32, true) << std::endl;
//    std::cout << EuclideanAlgorithm::euclideanAlgorithmWithRecursion(16384,32, true) << std::endl;

    //extended euclidean algorithm
//    int EuclideanX, EuclideanY;
//    ExtendedEuclideanAlgorithm::extendedEuclideanAlgorithm(35, 15, EuclideanX, EuclideanY, true);
//    printf("x = %d, y = %d\n", EuclideanX, EuclideanY);

    //chinese remainder algorithm
//    std::vector <std::pair<int, int>> vector;
//    vector.emplace_back(std::make_pair(2,3));
//    vector.emplace_back(std::make_pair(3,5));
//    vector.emplace_back(std::make_pair(2,7));
//    std::cout << ChineseRemainderAlgorithm::chineseRemainderAlgorithm(vector, true);
    // interpolation
//    std::vector<double> x = {0, 1, 2, 3, 4};
//    std::vector<double> y = {1, 4, 7, 10, 18};
//    std::cout << Interpolation::linearInterpolation(x, y, 0.5, true);

//FFT
//    std::vector<int> a = {2,5,6};//2x^2+5x+6
//    std::vector<int> b = {3,3,8};//3x^2+3x+8
//    std::vector<int> c = FastFourierTransform::multiply(a, b);
//    for (int i = 0; i < c.size(); ++i) {
//        std::cout << c[i] << " ";
//    }

//    Polynomial p1;
//    p1.addTerm(std::make_pair(boost::rational<int>(3,1),5));
//    p1.addTerm(std::make_pair(boost::rational<int>(6,1), 2));
//    p1.addTerm(std::make_pair(boost::rational<int>(8,1),4));
//    p1.addTerm(std::make_pair(boost::rational<int>(-2,1), 0));
//
//    Polynomial p2;
//    p2.addTerm(std::make_pair(boost::rational<int>(-2,1),1));
//    p2.addTerm(std::make_pair(boost::rational<int>(1,1),0));
//    p2.addTerm(std::make_pair(boost::rational<int>(1,1),3));
//
//    std::cout<<"P1: ";
//    Polynomial::printPoly(p1);
//    std::cout<<"P2: ";
//    Polynomial::printPoly(p2);
//
//    Polynomial add = Polynomial::addPoly(p1, p2);
//    Polynomial sub = Polynomial::subtractPoly(p1, p2);
//    Polynomial mul = Polynomial::multiplyPoly(p1, p2);
//
//    Polynomial::printPoly(add);
//    Polynomial::printPoly(sub);
//    Polynomial::printPoly(mul);
//
//    auto result1 = Polynomial::dividePoly(p1,p2);
//    auto quotient = result1.first;
//    auto reminders = result1.second;
//
//    std::cout<<"Quot: ";
//    Polynomial::printPoly(quotient);
//
//    std::cout<<"Reminder: ";
//    Polynomial::printPoly(reminders[reminders.size() - 1]);

    MultivariatePolynomial mvp1;
    MultivariatePolynomial mvp2;

    //ADD 0 FOR ALL THE TERMS THAT DON'T EXIST
    Term t1 = Term(boost::rational<int>(1,1), {2,3,2});
    Term t2 = Term(boost::rational<int>(1,1), {3,1,2});
    Term t3 = Term(boost::rational<int>(1,1), {1,2,2});

    Term t4 = Term(boost::rational<int>(1,1), {0,2,1});
    Term t5 = Term(boost::rational<int>(1,1), {1,1,1});
    Term t6 = Term(boost::rational<int>(1,1), {2,0,0});

    Term t7 = Term(boost::rational<int>(1,1), {2,3,0});
    Term t8 = Term(boost::rational<int>(1,1), {5,1,2});
    Term t9 = Term(boost::rational<int>(1,1), {0,3,0});
    Term t10 = Term(boost::rational<int>(1,1), {0,3,5});
    Term t11 = Term(boost::rational<int>(1,1), {5,2,10});
    Term t12 = Term(boost::rational<int>(1,1), {6,0,0});
    Term t13 = Term(boost::rational<int>(1,1), {0,0,99});
    Term t14 = Term(boost::rational<int>(1,1), {2,2,2});
    Term t15 = Term(boost::rational<int>(1,1), {3,3,0});
    Term t16 = Term(boost::rational<int>(1,1), {3,0,0});
    Term t17 = Term(boost::rational<int>(-3,1), {2,0,0});

    mvp1.addTerm(t1);
    mvp1.addTerm(t2);
    mvp1.addTerm(t3);

    mvp2.addTerm(t4);
    mvp2.addTerm(t5);
    mvp2.addTerm(t6);

    std::string order = "deglex";
//    mvp1.SORTING_TEST(order);
//    auto v = MultivariatePolynomial::getDegree(mvp1);
//    for(auto a: v)
//        std::cout << a<<" ";
    auto result = MultivariatePolynomial::dividePolynomials(mvp1, mvp2, order);
    std::cout<<"QUOTIENT: "<<result.first<<"\n";
    std::cout<<"REMINDER: "<<result.second[result.second.size() - 1]<<"\n";

    return 0;
}