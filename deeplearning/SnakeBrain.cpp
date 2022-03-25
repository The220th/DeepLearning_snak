
#include <limits>

#include "../include/SnakeBrain.h"
#include "../include/sup.h"

using namespace std;

SnakeBrain::SnakeBrain() : M1(middleLayerNum, inNum+1), M2(outNum, middleLayerNum+1)
{
    for(size_t li = 0; li < M1.get_n(); ++li)
        for(size_t lj = 0; lj < M1.get_m(); ++lj)
            M1.set(sup_rand(-1.0, 1.0), li, lj);

    for(size_t li = 0; li < M2.get_n(); ++li)
        for(size_t lj = 0; lj < M2.get_m(); ++lj)
            M2.set(sup_rand(-1.0, 1.0), li, lj);

    // Последние столбцы обязательно = 1
    for(size_t li = 0; li < M1.get_n(); ++li)
        M1.set(1, li, inNum);
    for(size_t li = 0; li < M2.get_n(); ++li)
        M2.set(1, li, middleLayerNum);
}

SnakeBrain::SnakeBrain(const Matrix<double> &genom) : M1(middleLayerNum, inNum+1), M2(outNum, middleLayerNum+1)
{
    // genom is matrix n=1 , m=12*26 + 4*13

    size_t i = 0;

    for(size_t li = 0; li < M1.get_n(); ++li)
        for(size_t lj = 0; lj < M1.get_m(); ++lj)
            M1.set(genom.get(0, i++), li, lj);

    for(size_t li = 0; li < M2.get_n(); ++li)
        for(size_t lj = 0; lj < M2.get_m(); ++lj)
            M2.set(genom.get(0, i++), li, lj);
}

SnakeBrain::SnakeBrain(const SnakeBrain &otherBrain) : M1(otherBrain.M1), M2(otherBrain.M2)
{

}

int SnakeBrain::think(const Matrix<double> &v_in) const
{
    Matrix<double> v_mid(M1.multiply(v_in));

    for(size_t i = 0; i < v_mid.get_n(); ++i)
        v_mid.set(ReLU(v_mid.get(i, 0)), i, 0);

    Matrix<double> v_mid1(middleLayerNum+1, 1);
    for(size_t i = 0; i < v_mid.get_n(); ++i)
        v_mid1.set(v_mid.get(i, 0), i, 0);
    v_mid1.set(1, v_mid1.get_n()-1, 0);

    Matrix<double> v_res(M2.multiply(v_mid1));

    double max = -std::numeric_limits<double>::infinity();
    int res = -1;
    
    for(size_t i = 0; i < v_res.get_n(); ++i)
        if(max < v_res.get(i, 0))
        {
            max = v_res.get(i, 0);
            res = i;
        }

    return res+1;
}