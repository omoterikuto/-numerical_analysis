#include <stdio.h>
#include <stdlib.h>

#define deltaT 1e-4

double dvdt(double v, double w, double input)
{
    return 10 * ((-1) * v * v * v / 3 + v - w + input);
}

double dwdt(double v, double w)
{
    return v - 0.8 * w + 0.7;
}

int main(int argc, char *argv[])
{
    double input = atof(argv[1]);
    double t;
    double old_v = 0, old_w = 0;
    double v, w = 0;
    for (t = 0; t <= 100; t += deltaT)
    {
        v = dvdt(old_v, old_w, input) * deltaT + old_v;
        w = dwdt(old_v, old_w) * deltaT + old_w;
        printf("%6.6f %6.6f %6.6f\n", t, v, w);
        old_v = v;
        old_w = w;
    }
    return 0;
}