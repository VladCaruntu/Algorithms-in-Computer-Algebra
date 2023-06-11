#ifndef COD_EUCLIDEANALGORITHM_H
#define COD_EUCLIDEANALGORITHM_H

//finds the GCD of 2 integeres
class EuclideanAlgorithm {
public:
    EuclideanAlgorithm() = delete;
    static int euclideanAlgorithmWithSubtractions(int, int, bool flag = true);
    static int euclideanAlgorithmWithDivisions(int, int, bool flag = true);
    static int euclideanAlgorithmWithRecursion(int, int, bool flag = true);
    static int euclideanAlgorithmWithRecursionRunner(int, int);
};
#endif
