#include <iostream>
#include <vector>

#include "EuclideanAlgorithm.h"
#include "ChineseRemainderAlgorithm.h"
#include "ExtendedEuclideanAlgorithm.h"
#include "Interpolation.h"
#include "FastFourierTransform.h"

int main() {
    //euclidean algorithm
//    std::cout << EuclideanAlgorithm::euclideanAlgorithmWithSubtractions(16384,32, true) << std::endl;
//    std::cout << EuclideanAlgorithm::euclideanAlgorithmWithDivisions(16384,32, true) << std::endl;
//    std::cout << EuclideanAlgorithm::euclideanAlgorithmWithRecursion(16384,32, true) << std::endl;

    //extended euclidean algorithm
//    int EuclideanX, EuclideanY;
//    ExtendedEuclideanAlgorithm::extendedEuclideanAlgorithm(102, 38, EuclideanX, EuclideanY, true);
//    printf("x = %d, y = %d\n", EuclideanX, EuclideanY);

    //chinese remainder algorithm
//    std::vector < std::pair < int, int > > vector;
//    vector.emplace_back(std::make_pair(1,2));
//    vector.emplace_back(std::make_pair(2,3));
//    vector.emplace_back(std::make_pair(3,5));
//    vector.emplace_back(std::make_pair(4,11));
//    vector.emplace_back(std::make_pair(2,11));
//    std::cout << ChineseRemainderAlgorithm::chineseRemainderAlgorithm(vector);

//    std::cout << Interpolation::linearInterpolation({1.1555, 200}, {1.17608, 212}, 220, true);

    std::vector<double> v{2,5,3,1};
    std::vector<double> result1 = FastFourierTransform::FFT(v);
    for(double d: result1){
        std::cout << d << " ";
    }
    std::cout<<"\n";
    std::vector<double> result2 = FastFourierTransform::IFFT(result1);
    for(double d: result2){
        std::cout << d << " ";
    }
    return 0;
}