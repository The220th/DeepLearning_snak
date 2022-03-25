#ifndef SNAKE_H
#define SNAKE_H

#include <cstdlib>
#include "../include/sup.h"

struct SnakeBlock
{
    int x;
    int y;
};


class Snake
{
    private:
    std::size_t curSize;
    SnakeBlock *train;
    SnakeBlock head;
    const unsigned color;



    public:
    Snake(std::size_t initSize = 3, unsigned snake_color = sup_getColor(0, 255, 0));
    ~Snake();

    const SnakeBlock* getSnakeBlocks();
    std::size_t getSize();
    SnakeBlock getHead();

    unsigned getColor();

    /*
    ] dx = 1, dy = 0
    if grow = true:
        oo   ->   ooo
        o         o
    if grow == false:
        oo   ->   ooo
        o
    */
    void move(int dx, int dy, bool grow = false);
};

#endif // SNAKE_H
