
#include <cstdlib>

#include "../include/Snake.h"

using namespace std;

Snake::Snake(std::size_t initSize, unsigned snake_color) : color(snake_color)
{
    curSize = initSize;
    train = new SnakeBlock[curSize];

    for(size_t i = 0; i < curSize; ++i)
        train[i] = {(int)(initSize-1-i), (int)(initSize-1)};
    head = train[0];
}

Snake::~Snake()
{
    delete train;
}

const SnakeBlock* Snake::getSnakeBlocks()
{
    return train;
}

size_t Snake::getSize()
{
    return curSize;
}

SnakeBlock Snake::getHead()
{
    return head;
}

unsigned Snake::getColor()
{
    return this->color;
}

void Snake::move(int dx, int dy, bool grow)
{
    if(grow == true)
    {
        ++curSize;
        SnakeBlock *oldtrain = train;
        SnakeBlock *newtrain = new SnakeBlock[curSize];
        for(size_t i = 1; i < curSize; ++i)
            newtrain[i] = oldtrain[i-1];
        newtrain[0] = {head.x+dx, head.y+dy};
        
        delete oldtrain;
        train = newtrain;
        head = train[0];
    }
    else
    {
        SnakeBlock prev = train[0];
        SnakeBlock buff;
        for(size_t i = 1; i < curSize; ++i)
        {
            buff = prev;
            prev = train[i];
            train[i] = buff;
        }

        train[0] = {train[0].x+dx, train[0].y+dy};
        head = train[0];
    }
}