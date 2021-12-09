#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
    double deltaT = atof(argv[1]);
    double y = 0.0;
    double ans_y = 0.0;

    for (double t = 0; t <= 3; t += deltaT)
    {
        y = y + (2 * t * exp(-t) - y) * deltaT;
        ans_y = t * t * exp(-t);
        printf("%6.6f, %6.6f\n", t, ans_y - y);
    }

    return 0;
}