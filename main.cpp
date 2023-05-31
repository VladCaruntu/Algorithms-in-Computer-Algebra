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

//    std::unique_ptr<Polynomial> p1 = std::make_unique<Polynomial>();
//    p1->addTerm(std::make_pair(boost::rational<int>(32,1),1));
//    p1->addTerm(std::make_pair(boost::rational<int>(1,1),5));
//    p1->addTerm(std::make_pair(boost::rational<int>(-32,1),3));
//
//    p1->addTerm(std::make_pair(boost::rational<int>(2,1),1));
//    p1->addTerm(std::make_pair(boost::rational<int>(1,1), 0));
//    p1->addTerm(std::make_pair(boost::rational<int>(1,1), 2));
//    p1->addTerm(std::make_pair(boost::rational<int>(-7,1), 3));
//    p1->addTerm(std::make_pair(boost::rational<int>(3,1), 5));
//    p1->addTerm(std::make_pair(boost::rational<int>(11,1),1));
//    p1->addTerm(std::make_pair(boost::rational<int>(9,1),0));
//    p1->addTerm(std::make_pair(boost::rational<int>(1,1),3));
//    p1->addTerm(std::make_pair(boost::rational<int>(-3,1),2));
//    p1->addTerm(std::make_pair(boost::rational<int>(3,1),1));
//    p1->addTerm(std::make_pair(boost::rational<int>(-1,1),0));
//    Polynomial::printPoly(*p1);

//    std::unique_ptr<Polynomial> p2 = std::make_unique<Polynomial>();
//    p2->addTerm(std::make_pair(boost::rational<int>(1,1),2));
//    p2->addTerm(std::make_pair(boost::rational<int>(5,1),1));
//    p2->addTerm(std::make_pair(boost::rational<int>(7,1),3));
//    p2->addTerm(std::make_pair(boost::rational<int>(1,1),1));
//    p2->addTerm(std::make_pair(boost::rational<int>(1,1),0));

//    Polynomial::printPoly(*p1);
//    Polynomial::printPoly(*p2);
//    Polynomial ppp = Polynomial::subtractPoly(*p1, *p2);
//    Polynomial::printPoly(ppp);

//    Polynomial::printPoly(*p2);
//    auto result = Polynomial::dividePoly(*p1,*p2);
//    auto quotient = result.first;
//    auto reminders = result.second;
//
//    std::cout<<"Quot: ";
//    Polynomial::printPoly(quotient);
//    for(const auto& term: Polynomial::getTerms(quotient))
//    {
//        std::cout<<term.first<<"x^"<<term.second<<"\n";
//    }
//    std::cout<<"\n";
//
//    std::cout<<"Reminders: ";
//    for(auto& reminder: reminders){
//        Polynomial::printPoly(reminder);
//    }

    MultivariatePolynomial mvp1;
    MultivariatePolynomial mvp2;

    Term t1 = Term(boost::rational<int>(1,1), {2,3});// 2 3
    Term t2 = Term(boost::rational<int>(1,1), {3,4});// 3 4
    Term t3 = Term(boost::rational<int>(1,1), {3,2});// 3 2
    Term t4 = Term(boost::rational<int>(1,1), {2,1});// 2 1
    Term t5 = Term(boost::rational<int>(1,1), {1});// 1
    Term t6 = Term(boost::rational<int>(1,1), {0,1});// 0 1
    Term t7 = Term(boost::rational<int>(-1,1), {2,3});// 2 3

    mvp1.addTerm(t4);
    mvp1.addTerm(t3);
    mvp1.addTerm(t2);

//    mvp1.processPoly();
    mvp2.addTerm(t4);

    auto plus = MultivariatePolynomial::addPolynomials(mvp1,mvp2);
    auto minus = MultivariatePolynomial::subtractPolynomials(mvp1,mvp2);
    auto mult = MultivariatePolynomial::multiplyPolynomials(mvp1,mvp2);

    std::cout<<"plus: " << plus <<"\n" << "minus: " << minus << "\nmult: " << mult << std::endl;

    auto result = MultivariatePolynomial::dividePolynomials(mvp1, mvp2);
    std::cout<<"QUOT: "<<result.first<<"\n";
    std::cout<<"REMS:\n";
    for(auto & term: result.second)
    {
        std::cout<<term <<"\n";
    }

    return 0;
}