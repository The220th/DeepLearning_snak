#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <random>

#include "../include/DrawField.h"
#include "../include/Snake.h"

class GameHandler
{
    private:
    const std::size_t W;
    const std::size_t H;

    double score;
    size_t apple_count;
    size_t ticks_behind;

    DrawField *df;

    Snake *snake;
    //const unsigned snake_head_color = sup_getColor(255, 0, 0) ^ sup_getColor(0, 255, 0);
    const unsigned snake_head_color = sup_getColor(255, 0, 0, 128);

    /*1 - left
    2 - up
    3 - right
    4 - down*/
    int dir;
    SnakeBlock apple;
    const unsigned appleColor = sup_getColor(255, 0, 0);

    std::random_device rd;

    void random_apple();

    void drawGameField();

    bool check_snake_collision(const SnakeBlock &toCheck);

    bool check_lose(const SnakeBlock &nextHead);

    void reset();

    public:
    GameHandler(std::size_t width, std::size_t height, DrawField *drawField);
    ~GameHandler();

    double getScore();

    /*
    0 - nothing
    1 - left
    2 - up
    3 - right
    4 - down
    */
   /*return: true = ok, false = lose*/
    bool tick(int action = 0);
};

#endif // GAMEHANDLER_H
