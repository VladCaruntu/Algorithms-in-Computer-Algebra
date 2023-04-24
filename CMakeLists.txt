cmake_minimum_required(VERSION 3.23)
project(COD)
set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(
        COD
        main.cpp
        EuclideanAlgorithm.cpp
        EuclideanAlgorithm.h
        ChineseRemainderAlgorithm.cpp
        ChineseRemainderAlgorithm.h
        ExtendedEuclideanAlgorithm.cpp
        ExtendedEuclideanAlgorithm.h
        Interpolation.cpp
        Interpolation.h
        FastFourierTransform.cpp
        FastFourierTransform.h
        Polynomial.cpp
        Polynomial.h MultivariatePolynomial.cpp MultivariatePolynomial.h)
target_link_libraries(COD ${Boost_LIBRARIES})