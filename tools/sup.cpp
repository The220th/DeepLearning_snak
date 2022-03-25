
#include <cmath>
#include <QColor>

#include <cstdlib>
#include <ctime>

#include "../include/sup.h"

using namespace std;

int rightRound(double num)
{
    return (int)(num<0?num-0.5:num+0.5);
}

double deg2rad(double a)
{
    /*
    180 - pi
    a   - x
    */
   return (M_PI*a) / 180.0;
}

double fast_pow(double x, unsigned n)
{
    double res = 1.0;
    double base = x;
    unsigned b = n;

    while(b != 0)
    {
        if(b % 2 == 1)
            res *= base;
        base *= base;
        //b = b >> 1; // b /= 2;
        b /= 2;
    }
    return res;
}

unsigned sup_getColor(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha)
{
    QColor buff(r, g, b, alpha);
    return buff.rgb(); // #AARRGGBB
}

double ReLU(double x)
{
    return x>0?x:0;
}

double sup_rand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void sup_randInit()
{
    srand(time(NULL));
}