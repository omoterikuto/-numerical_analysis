#include <stdio.h>

#define deltaT 1e-4

double dy1dt(double y1, double y2)
{
    y1 = 2 * y1 - y1 * y2;
    return y1;
}

double dy2dt(double y1, double y2)
{
    y2 = y1 * y2 - 3 * y2;
    return y2;
}

int main()
{
    double t;
    double old_y1 = 1, old_y2 = 1;
    double y1, y2 = 0;
    for (t = 0; t <= 20; t += deltaT)
    {
        y1 = dy1dt(old_y1, old_y2) * deltaT + old_y1;
        y2 = dy2dt(old_y1, old_y2) * deltaT + old_y2;
        printf("%6.6f %6.6f %6.6f\n", t, y1, y2);
        old_y1 = y1;
        old_y2 = y2;
    }
    return 0;
}