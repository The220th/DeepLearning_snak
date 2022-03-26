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

/*Don`t forget call sup_randInit*/
double sup_rand(int iMin, int iMax);

/*Don`t forget call sup_randInit*/
bool sup_rand_bool();

void sup_randInit();

/*
---|------|-----|--------------|----
a[0] a[1]   a[2]    a[3]        a[4]
С большей вероятностью выберет больнший отрезок
sumOfa <- sup_calc_sum(a, n)
*/
size_t sup_chooseProbablyBest(double* a, size_t n, double sumOfa);

double sup_calc_sum(double* a, size_t n);

/*Если в a есть x, то true*/
bool sup_check_inclusion(double* a, size_t n, double x);

#endif // SUP_H
