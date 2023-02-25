#include <iostream>

#include "EuclideanAlgorithm.h"
#include "ChineseRemainderAlgorithm.h"
#include "ExtendedEuclideanAlgorithm.h"

//void separate(){
//    std::cout << "------------------------------------------------------------------------------------------------\n";
//}

int main() {
    //euclidean algorithm
//    std::cout << EuclideanAlgorithm::euclideanAlgorithmWithSubtractions(16384,32, true) << std::endl;
//    std::cout << EuclideanAlgorithm::euclideanAlgorithmWithDivisions(16384,32, true) << std::endl;
//    std::cout << EuclideanAlgorithm::euclideanAlgorithmWithRecursion(16384,32, true) << std::endl;

    //extended euclidean algorithm
    int EuclideanX, EuclideanY;
    ExtendedEuclideanAlgorithm::extendedEuclideanAlgorithm(102, 38, EuclideanX, EuclideanY, true);
    printf("x = %d, y = %d\n", EuclideanX, EuclideanY);

    return 0;
}