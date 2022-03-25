
#include <random>
#include <iostream>

#include "../include/DrawField.h"
#include "../include/GameHandler.h"
#include "../include/Snake.h"

GameHandler::GameHandler(size_t width, size_t height, DrawField *drawField) : W(width), H(height)
{
    df = drawField;

    snake = new Snake();

    score = 0; ticks_behind = 0; apple_count = 0;

    dir = 3;

    random_apple();
}


GameHandler::~GameHandler()
{
    delete snake;
}

void GameHandler::random_apple()
{
    do
    {
        apple = {(int)(rd() % W), (int)(rd() % H)};
    }while(check_snake_collision(apple) == true);
    //cout << apple.x << " " << apple.y << endl;
}

bool GameHandler::check_snake_collision(const SnakeBlock &toCheck)
{
    bool res = false;

    const SnakeBlock *sbs = snake->getSnakeBlocks();
    size_t snake_size = snake->getSize();

    for(size_t i = 0; i < snake_size; ++i)
        if(sbs[i].x == toCheck.x && sbs[i].y == toCheck.y)
        {
            res = true;
            break;
        }
    return res;
}

bool GameHandler::check_lose(const SnakeBlock &nextHead)
{
    if(nextHead.x < 0 || nextHead.x >= (int)W || nextHead.y < 0 || nextHead.y >= (int)H)
        return true;

    const SnakeBlock *sbs = snake->getSnakeBlocks();
    size_t snake_size = snake->getSize();

    for(size_t i = 0; i < snake_size; ++i)
        if(sbs[i].x == nextHead.x && sbs[i].y == nextHead.y)
        {
            return true;
        }
    return false;
}

void GameHandler::reset()
{
    delete snake;
    snake = new Snake();

    score = 0; ticks_behind = 0; apple_count = 0;

    dir = 3;

    random_apple();
}

double GameHandler::getScore()
{
    return ticks_behind*ticks_behind * fast_pow(2,    (apple_count>10?10:apple_count)   ) * 2*apple_count;
}

bool GameHandler::tick(int action)
{
    bool res = true;

    int snake_dir;

    snake_dir = dir;
    if(action == 1 || action == 2 || action == 3 || action == 4)
        snake_dir = action;
    
    SnakeBlock buffHead = snake->getHead();
    int dx, dy;
    
    if(snake_dir == 1)
    {
        dx = -1; dy = 0;
    }
    else if(snake_dir == 2)
    {
        dx = 0; dy = 1;
    }
    else if(snake_dir == 3)
    {
        dx = 1; dy = 0;
    }
    else if(snake_dir == 4)
    {
        dx = 0; dy = -1;
    }
    else
    {
        dx = 0; dy = 0;
    }

    buffHead = {buffHead.x + dx, buffHead.y + dy};

    if(check_lose(buffHead))
    {
        reset();
        res = false;
    }

    if(buffHead.x == apple.x && buffHead.y == apple.y)
    {
        ++apple_count;
        snake->move(dx, dy, true);
        random_apple();
    }
    else
    {
        snake->move(dx, dy);
    }
    dir = snake_dir;

    score = getScore(); //?!

    drawGameField();

    ++ticks_behind;

    return res;
}

void GameHandler::drawGameField()
{
    const SnakeBlock *sbs = snake->getSnakeBlocks();
    size_t snake_size = snake->getSize();
    unsigned snake_color = snake->getColor();

    for(size_t i = 0; i < snake_size; ++i)
    {
        df->putPoint(sbs[i].x, sbs[i].y, snake_color);
    }

    SnakeBlock snakeHead = snake->getHead();
    df->putPoint(snakeHead.x, snakeHead.y, snake_head_color);

    df->putPoint(apple.x, apple.y, appleColor);
}