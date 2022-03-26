
#include <random>
#include <iostream>
#include <cmath>
#include <iostream>

#include "../include/DrawField.h"
#include "../include/GameHandler.h"
#include "../include/Snake.h"
#include "../include/SnakeBrain.h"
#include "../include/matrix.h"

GameHandler::GameHandler(size_t width, size_t height, DrawField *drawField) : W(width), H(height)
{
    df = drawField;

    appleColor = sup_getColor(sup_rand(128, 255), sup_rand(0, 200), sup_rand(0, 200));

    //appleColor = sup_getColor(255, 0, 0);

    snake_head_color = appleColor;

    snake = new Snake();

    score = 0; ticks_behind = 0; apple_count = 0;

    dir = 3;

    ifLOSE = false;

    ticksleft = STARTTICK;

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
    SnakeBrain *buffBrain = new SnakeBrain(*(snake->getBrain()));
    delete snake;
    snake = new Snake();
    snake->setBrain(buffBrain); // Операция по пересадке мозга прошла успешно=/

    score = 0; ticks_behind = 0; apple_count = 0;

    dir = 3;

    ifLOSE = false;

    ticksleft = STARTTICK;

    random_apple();
}

double GameHandler::getScore() const
{
    if(apple_count < 10)
        return ticks_behind*ticks_behind * fast_pow(2, apple_count);
    else
        return ticks_behind*ticks_behind*1024*(apple_count-1);
}

int GameHandler::countApples() const
{
    return apple_count;
}

Snake* GameHandler::getSnake() const
{
    return snake;
}

bool GameHandler::tick(int action)
{
    --ticksleft;
    if(ticksleft < 0)
        ticksleft = 0;
    if(ifLOSE)
        return false;

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

    if(ticksleft <= 0 || check_lose(buffHead))
    {
        //reset();
        ifLOSE = true;
        res = false;
    }

    if(buffHead.x == apple.x && buffHead.y == apple.y)
    {
        ticksleft += STARTTICK;
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

    if(!ifLOSE)
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
        //if(!(sbs[i].x < 0 || sbs[i].x >= (int)W || sbs[i].y < 0 || sbs[i].y >= (int)H))
        df->putPoint(sbs[i].x, sbs[i].y, snake_color);
    }

    SnakeBlock snakeHead = snake->getHead();
    df->putPoint(snakeHead.x, snakeHead.y, snake_head_color);

    df->putPoint(apple.x, apple.y, appleColor);
}

int GameHandler::whatSnakeThink() const
{
    const SnakeBrain *brain = snake->getBrain();
    Matrix<double> v_in(brain->inNum+1, 1);

    //   3                 *       8                   +   1         +      1     =   26
    // wall,snake,apple         L,LU,U,RU,R,RD,D,LD       r_apple        const=1

    //wall
    v_in.set(find_something({-1, 0}, 1), 0, 0);
    v_in.set(find_something({-1, 1}, 1), 1, 0);
    v_in.set(find_something({0, 1}, 1), 2, 0);
    v_in.set(find_something({1, 1}, 1), 3, 0);
    v_in.set(find_something({1, 0}, 1), 4, 0);
    v_in.set(find_something({1, -1}, 1), 5, 0);
    v_in.set(find_something({0, -1}, 1), 6, 0);
    v_in.set(find_something({-1, -1}, 1), 7, 0);

    //tail (snake)
    v_in.set(find_something({-1, 0}, 2), 8, 0);
    v_in.set(find_something({-1, 1}, 2), 9, 0);
    v_in.set(find_something({0, 1}, 2), 10, 0);
    v_in.set(find_something({1, 1}, 2), 11, 0);
    v_in.set(find_something({1, 0}, 2), 12, 0);
    v_in.set(find_something({1, -1}, 2), 13, 0);
    v_in.set(find_something({0, -1}, 2), 14, 0);
    v_in.set(find_something({-1, -1}, 2), 15, 0);

    //apple (watch?v=Ct6BUPvE2sM)
    v_in.set(find_something({-1, 0}, 3), 16, 0);
    v_in.set(find_something({-1, 1}, 3), 17, 0);
    v_in.set(find_something({0, 1}, 3), 18, 0);
    v_in.set(find_something({1, 1}, 3), 19, 0);
    v_in.set(find_something({1, 0}, 3), 20, 0);
    v_in.set(find_something({1, -1}, 3), 21, 0);
    v_in.set(find_something({0, -1}, 3), 22, 0);
    v_in.set(find_something({-1, -1}, 3), 23, 0);

    // r
    //v_in.set(find_something({0, 0}, 5051), 24, 0);

    // 1
    v_in.set(1.0, 24, 0);

    //cout << v_in.toString() << endl;

    return brain->think(v_in);
}

double GameHandler::find_something(SnakeBlock v, int mode) const
{
    int k = 1;
    int x, y;
    SnakeBlock head = snake->getHead();
    if(mode == 1)
    {
        do
        {
            x = head.x + v.x*k;
            y = head.y + v.y*k;
            ++k;
        }while( !(x < 0 || x >= (int)W || y < 0 || y >= (int)H) );

        //return 1.0 / sqrt((head.x-x)*(head.x-x) + (head.y-y)*(head.y-y));
        return 1.0 / (double)k;
    }
    else if(mode == 2)
    {   
        const SnakeBlock *sbs = snake->getSnakeBlocks();
        size_t snake_size = snake->getSize();
        while(true)
        {
            x = head.x + v.x*k;
            y = head.y + v.y*k;
            ++k;
            if((x < 0 || x >= (int)W || y < 0 || y >= (int)H))
                return 0; // Расстояние бесконечность
            for(size_t i = 0; i < snake_size; ++i)
                if(x == sbs[i].x && y == sbs[i].y)
                    return 1.0 / (double)k;
                    //return 1.0 / sqrt((head.x-x)*(head.x-x) + (head.y-y)*(head.y-y));
        }
    }
    else if(mode == 3)
    {
        while(true)
        {
            x = head.x + v.x*k;
            y = head.y + v.y*k;
            ++k;
            if((x < 0 || x >= (int)W || y < 0 || y >= (int)H))
                return 0; // Расстояние бесконечность
            if(x == apple.x && y == apple.y)
                return 1.0 / (double)k;
                //return 1.0 / sqrt((head.x-x)*(head.x-x) + (head.y-y)*(head.y-y));
        }
    }
    else
        return 1.0 / sqrt((head.x-apple.x)*(head.x-apple.x) + (head.y-apple.y)*(head.y-apple.y));
}

bool GameHandler::isLose() const
{
    return ifLOSE;
}