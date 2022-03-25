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
     o o o o o o         hide layer
      X X X X /        second matrix = II слой
      o o o o               out
    */
    
    Matrix<double> M1;
    Matrix<double> M2;


    public:

    static const std::size_t middleLayerNum = 12;
    static const std::size_t inNum = 25;
    static const std::size_t outNum = 4;

    /*random genom*/
    SnakeBrain();

    SnakeBrain(const Matrix<double> &genom);

    SnakeBrain(const SnakeBrain &otherBrain);

    /*
    return: 1 - left, 2 - up, 3 - right, 4 - down
    */
    int think(const Matrix<double> &v_in) const;
};

#endif // SNAKEBRAIN_H
