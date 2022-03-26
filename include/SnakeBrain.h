#ifndef SNAKEBRAIN_H
#define SNAKEBRAIN_H

#include <cstdlib>
#include "../include/sup.h"
#include "../include/matrix.h"

class SnakeBrain
{
    private:

    /*   двуслойный перцептрон:
    o o o o o o o o         in
     X X X X X X /     first matrix = I слой
     o o o o o o         hide layer 1
      X X X X /        second matrix = II слой
      o o o o            hide layer 2
       x x /            third matrix = III слой
        o o                  out
    */
    
    Matrix<double> M1;
    Matrix<double> M2;
    Matrix<double> M3;

    static double activationFunction(double x);

    static Matrix<double> add1ToLastRow(const Matrix<double> &v);

    public:

    static const std::size_t inNum = 24;

    static const std::size_t middleLayerNum1 = 18;

    static const std::size_t middleLayerNum2 = 12;

    static const std::size_t outNum = 4;

    /*random genom*/
    SnakeBrain();

    SnakeBrain(const Matrix<double> &genom);

    SnakeBrain(const SnakeBrain &otherBrain);

    /*
    return: 1 - left, 2 - up, 3 - right, 4 - down
    */
    int think(const Matrix<double> &v_in) const;

    Matrix<double> getGenom() const;

    static Matrix<double> offspring(const Matrix<double>& genom1, const Matrix<double>& genom2);
};

#endif // SNAKEBRAIN_H
