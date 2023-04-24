#include <iostream>
#include <vector>
#include <boost/rational.hpp>

#include "EuclideanAlgorithm.h"
#include "ChineseRemainderAlgorithm.h"
#include "ExtendedEuclideanAlgorithm.h"
#include "Interpolation.h"
#include "FastFourierTransform.h"
#include "Polynomial.h"

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
//    p1->addTerm(std::make_pair(boost::rational<int>(2,3), 4));
//    p1->addTerm(std::make_pair(boost::rational<int>(2,4), 3));
//    p1->addTerm(std::make_pair(boost::rational<int>(-21,4), 3));
//    p1->addTerm(std::make_pair(boost::rational<int>(-5,2),0));
//    p1->addTerm(std::make_pair(boost::rational<int>(10,2),0));
//    p1->addTerm(std::make_pair(boost::rational<int>(-11, 5),5));
//    p1->addTerm(std::make_pair(boost::rational<int>(19, 4),3));
//    p1->addTerm(std::make_pair(boost::rational<int>(11, 5),5));
//    p1->addTerm(std::make_pair(boost::rational<int>(2, 3),2));
//    p1->addTerm(std::make_pair(boost::rational<int>(5,4),1));
//
//    std::unique_ptr<Polynomial> p2 = std::make_unique<Polynomial>();
//    p2->addTerm(std::make_pair(boost::rational<int>(5,4), 1));
//    p2->addTerm(std::make_pair(boost::rational<int>(2,3), 2));

//    p1->printPoly();
//    std::unique_ptr<Polynomial> p3 = std::make_unique<Polynomial>(Polynomial::addPoly(*p1, *p2, true));
//    std::unique_ptr<Polynomial> p4 = std::make_unique<Polynomial>(Polynomial::subtractPoly(*p1, *p2, true));
//    std::unique_ptr<Polynomial> p5 = std::make_unique<Polynomial>(Polynomial::multiplyPoly(*p1, *p2, true));
//    p3->printPoly();
//    p4->printPoly();
//    p5->printPoly();
    return 0;
}