
#include <limits>
#include <iostream>

#include "../include/SnakeBrain.h"
#include "../include/sup.h"

using namespace std;

SnakeBrain::SnakeBrain() : M1(middleLayerNum1, inNum+1), M2(middleLayerNum2, middleLayerNum1+1), M3(outNum, middleLayerNum2+1)
{
    for(size_t li = 0; li < M1.get_n(); ++li)
        for(size_t lj = 0; lj < M1.get_m(); ++lj)
            M1.set(sup_rand(-1.0, 1.0), li, lj);

    for(size_t li = 0; li < M2.get_n(); ++li)
        for(size_t lj = 0; lj < M2.get_m(); ++lj)
            M2.set(sup_rand(-1.0, 1.0), li, lj);

    for(size_t li = 0; li < M3.get_n(); ++li)
        for(size_t lj = 0; lj < M3.get_m(); ++lj)
            M3.set(sup_rand(-1.0, 1.0), li, lj);
    //for(size_t li = 0; li < M1.get_n(); ++li)
    //    M1.set(1, li, inNum);
    //for(size_t li = 0; li < M2.get_n(); ++li)
    //    M2.set(1, li, middleLayerNum);
}

SnakeBrain::SnakeBrain(const Matrix<double> &genom) : M1(middleLayerNum1, inNum+1), M2(middleLayerNum2, middleLayerNum1+1), M3(outNum, middleLayerNum2+1)
{
    // genom is matrix n=1 , m=12*26 + 4*13

    size_t i = 0;

    for(size_t li = 0; li < M1.get_n(); ++li)
        for(size_t lj = 0; lj < M1.get_m(); ++lj)
            M1.set(genom.get(0, i++), li, lj);

    for(size_t li = 0; li < M2.get_n(); ++li)
        for(size_t lj = 0; lj < M2.get_m(); ++lj)
            M2.set(genom.get(0, i++), li, lj);

    for(size_t li = 0; li < M3.get_n(); ++li)
        for(size_t lj = 0; lj < M3.get_m(); ++lj)
            M3.set(genom.get(0, i++), li, lj);
}

SnakeBrain::SnakeBrain(const SnakeBrain &otherBrain) : M1(otherBrain.M1), M2(otherBrain.M2), M3(otherBrain.M3)
{

}

double SnakeBrain::activationFunction(double x)
{
    return LeakyReLU(x);
}

Matrix<double> SnakeBrain::add1ToLastRow(const Matrix<double> &v)
{
    Matrix<double> res(v.get_n()+1, 1);
    for(size_t i = 0; i < v.get_n(); ++i)
        res.set(v.get(i, 0), i, 0);
    res.set(1, res.get_n()-1, 0);

    return res;
}

int SnakeBrain::think(const Matrix<double> &v_in) const
{
    Matrix<double> v_mid1(M1.multiply(v_in));

    for(size_t i = 0; i < v_mid1.get_n(); ++i)
        v_mid1.set(activationFunction(v_mid1.get(i, 0)), i, 0);

    Matrix<double> v_mid1_1(add1ToLastRow(v_mid1));

    Matrix<double> v_mid2(M2.multiply(v_mid1_1));

    for(size_t i = 0; i < v_mid2.get_n(); ++i)
        v_mid2.set(activationFunction(v_mid2.get(i, 0)), i, 0);

    Matrix<double> v_mid2_1(add1ToLastRow(v_mid2));

    Matrix<double> v_res(M3.multiply(v_mid2_1));

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

Matrix<double> SnakeBrain::getGenom() const
{
    // genom is matrix n=1 , m=12*26 + 4*13
    size_t m = middleLayerNum1 * (inNum+1) + middleLayerNum2 * (middleLayerNum1+1) + outNum * (middleLayerNum2+1);
    Matrix<double> res(1, m);

    size_t j = 0;

    for(size_t li = 0; li < M1.get_n(); ++li)
        for(size_t lj = 0; lj < M1.get_m(); ++lj)
            res.set(M1.get(li, lj), 0, j++);

    for(size_t li = 0; li < M2.get_n(); ++li)
        for(size_t lj = 0; lj < M2.get_m(); ++lj)
            res.set(M2.get(li, lj), 0, j++);

    for(size_t li = 0; li < M3.get_n(); ++li)
        for(size_t lj = 0; lj < M3.get_m(); ++lj)
            res.set(M3.get(li, lj), 0, j++);

    return res;
}

Matrix<double> SnakeBrain::offspring(const Matrix<double>& genom1, const Matrix<double>& genom2)
{
    // genom is matrix n=1 , m=12*26 + 4*13
    size_t m = middleLayerNum1 * (inNum+1) + middleLayerNum2 * (middleLayerNum1+1) + outNum * (middleLayerNum2+1);
    Matrix<double> res(1, m);

    for(size_t j = 0; j < m; ++j)
    {
        if(sup_rand_bool())
            res.set(genom1.get(0, j), 0, j);
        else
            res.set(genom2.get(0, j), 0, j);

        if(sup_rand(0, 100) < 2) // mutation
        {
           // double toSet = (genom1.get(0, j)+genom2.get(0, j)) / 2.0;
            double toSet = res.get(0, j) + sup_randGaussian()/5;
            //toSet += (sup_rand_bool()?1:-1)*0.15*toSet;
            //std::cout << res.get(0, j) << " " << sup_randGaussian() << std::endl;
            res.set(toSet, 0, j);
        }
    }

    return res;
}