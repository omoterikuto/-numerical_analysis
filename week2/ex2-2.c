#include <stdio.h>
#include <math.h>
#define eps 1e-7
int main(void)
{
    double a, b, c;
    a = 1.0;
    b = -1.0;
    while (fabs(a - b) / 2 >= eps)
    {
        c = (a + b) / 2;
        if (exp(-c) - c * c > 0)
        {
            b = c;
        }
        else if (exp(-c) - c * c < 0)
        {
            a = c;
        }
        else
        {
            printf("%0.12lf", c);
            return 0;
        }
    }
    printf("%0.12lf", c);
    return 0;
}