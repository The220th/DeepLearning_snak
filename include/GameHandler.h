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

    int ticksleft;
    const size_t STARTTICK =(size_t)(50*2.5+0.5);

    bool ifLOSE;

    DrawField *df;

    Snake *snake;
    //const unsigned snake_head_color = sup_getColor(255, 0, 0) ^ sup_getColor(0, 255, 0);
    unsigned snake_head_color/* = sup_getColor(255, 0, 0, 128)*/;

    /*1 - left
    2 - up
    3 - right
    4 - down*/
    int dir;
    SnakeBlock apple;
    unsigned appleColor/* = sup_getColor(255, 0, 0)*/;

    std::random_device rd;

    void random_apple();

    void drawGameField();

    bool check_snake_collision(const SnakeBlock &toCheck);

    bool check_lose(const SnakeBlock &nextHead);

    /*
        Найти:
        mode == 1: стену
        mode == 2: хвост (тело змеи)
        mode == 3: яблоко
        Относительно головы по направлению вектора v

        иначе(если mode != 1 && mode != 2 && mode != 3): расстояние от головы до яблока
    */
    double find_something(SnakeBlock v, int mode) const;



    public:
    GameHandler(std::size_t width, std::size_t height, DrawField *drawField);
    ~GameHandler();

    double getScore() const;

    int countApples() const;

    /*Мозг змейки не меняется*/
    void reset();

    Snake* getSnake() const;

    /*
    0 - nothing
    1 - left
    2 - up
    3 - right
    4 - down
    */
   /*return: true = ok, false = lose*/
    bool tick(int action = 0);

    int whatSnakeThink() const;

    bool isLose() const;
};

#endif // GAMEHANDLER_H
