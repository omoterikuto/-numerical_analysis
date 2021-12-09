#include <stdio.h>
#include <math.h>

int main()
{
    double deltaT = 1e-4;
    double y = 0.0;

    for (double t = 0; t <= 3 + deltaT; t += deltaT)
    {
        y = y + (2 * t * exp(-t) - y) * deltaT;
        printf("%6.6f, %6.6f\n", t, y);
    }

    return 0;
}