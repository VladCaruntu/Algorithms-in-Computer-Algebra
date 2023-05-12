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

    std::unique_ptr<Polynomial> p1 = std::make_unique<Polynomial>();
    p1->addTerm(std::make_pair(boost::rational<int>(2,1),1));
    p1->addTerm(std::make_pair(boost::rational<int>(1,1),0));
    p1->addTerm(std::make_pair(boost::rational<int>(1,1),2));
//    p1->addTerm(std::make_pair(boost::rational<int>(1,1),0));
//    p1->addTerm(std::make_pair(boost::rational<int>(2,1), 2));
//    p1->addTerm(std::make_pair(boost::rational<int>(-7,1), 3));
//    p1->addTerm(std::make_pair(boost::rational<int>(3,1), 5));
//    p1->addTerm(std::make_pair(boost::rational<int>(11,1),1));
//    p1->addTerm(std::make_pair(boost::rational<int>(9,1),0));
//    p1->addTerm(std::make_pair(boost::rational<int>(1, 1),3));
//    p1->addTerm(std::make_pair(boost::rational<int>(-3, 1),2));
//    p1->addTerm(std::make_pair(boost::rational<int>(3, 1),1));
//    p1->addTerm(std::make_pair(boost::rational<int>(-1, 1),0));
    Polynomial::printPoly(*p1);

    std::unique_ptr<Polynomial> p2 = std::make_unique<Polynomial>();
    p2->addTerm(std::make_pair(boost::rational<int>(1,1),0));
    p2->addTerm(std::make_pair(boost::rational<int>(1,1),1));
//    p2.addTerm(std::make_pair(boost::rational<int>(1,1),0));
//    p2.addTerm(std::make_pair(boost::rational<int>(6,1),4));
//    p2.addTerm(std::make_pair(boost::rational<int>(7,1),3));
//    p2.addTerm(std::make_pair(boost::rational<int>(1,1),1));
//    p2.addTerm(std::make_pair(boost::rational<int>(-5,1),0));
    Polynomial::printPoly(*p2);
    auto result = Polynomial::dividePoly(*p1,*p2);
    auto quotient = result.first;
    auto reminders = result.second;

    std::cout<<"Quot: ";
    Polynomial::printPoly(quotient);
//    for(const auto& term: Polynomial::getTerms(quotient))
//    {
//        std::cout<<term.first<<"x^"<<term.second<<"\n";
//    }
    std::cout<<"\n";

    std::cout<<"Reminders: ";
    for(auto& reminder: reminders){
        Polynomial::printPoly(reminder);
    }




//    p2->addTerm(std::make_pair(boost::rational<int>(5,4), 1));
//    p2->addTerm(std::make_pair(boost::rational<int>(2,3), 2));

//    p1->printPoly();
//    std::unique_ptr<Polynomial> p3 = std::make_unique<Polynomial>(Polynomial::addPoly(*p1, *p2, true));
//    std::unique_ptr<Polynomial> p4 = std::make_unique<Polynomial>(Polynomial::subtractPoly(*p1, *p2, true));
//    std::unique_ptr<Polynomial> p5 = std::make_unique<Polynomial>(Polynomial::multiplyPoly(*p1, *p2, true));
//    p3->printPoly();
//    p4->printPoly();
//    p5->printPoly();

//    MultivariatePolynomial p1, p2, p3, p4;
    //no powers equal to 0

//    std::unordered_map<char, int> vars1 = {{'x', 2}};
//    std::unordered_map<char, int> vars2 = {{'x', 1}};
//    std::unordered_map<char, int> vars3 = {{'x', 0}};
//    p4.addTerm(1.0, vars1);
//    p4.addTerm(-2.0, vars2);
//    p4.addTerm(1.0, vars3);
//    std::cout<<p4<<"\n";
//    std::unordered_map<char, int> vars1 = {{'x', 2}, {'y', 1}};
//    std::unordered_map<char, int> vars2 = {{'x', 1}, {'y', 1}};
//    std::unordered_map<char, int> vars3 = {{'x', 1}, {'y', 2}};
//    p1.addTerm(2.0, vars1);
//    p1.addTerm(-3.0, vars2);
//    p1.addTerm(1.0, vars3);
//    std::unordered_map<char, int> vars7 = {{'x', 1}, {'y', 2}};
//    std::unordered_map<char, int> vars4 = {{'x', 2}, {'y', 1}, {'z', 5}};
//    std::unordered_map<char, int> vars5 = {{'x', 1}, {'y', 2}, {'z', 3}};
//    std::unordered_map<char, int> vars6 = {{'x', 1}, {'y', 2}, {'z', 2}};
//    std::unordered_map<char, int> vars8 = {{'x', 1}, {'y', 0}, {'z', 1}};
//    p2.addTerm(1.0, vars4);
//    p2.addTerm(2.0, vars5);
//    p2.addTerm(-1.0, vars6);
//    p2.addTerm(-1.0, vars7);
//    p2.addTerm(-7.0, vars8);
//    std::cout<<p2<<"\n";
//    MultivariatePolynomial factorized = p2.factorize();
//    std::cout<<factorized<<"\n";
//    p1.add(p2);
//    std::cout<<p1<<"\n";
//    p3 = MultivariatePolynomial::multiplyPolynomials(p1, p2);
//    std::unordered_map<char, double> point = {{'x', 1.0}, {'y', 2.0}, {'z', 3}};
//    double result1 = p3.evaluate(point);

    return 0;
}