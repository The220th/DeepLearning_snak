#ifndef SUP_H
#define SUP_H

int rightRound(double num);

double deg2rad(double a);

// x^n
double fast_pow(double x, unsigned n);

// return = #AARRGGBB
unsigned sup_getColor(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha = 255);

double ReLU(double x);

/*Don`t forget call sup_randInit*/
double sup_rand(double fMin, double fMax);

void sup_randInit();

#endif // SUP_H
