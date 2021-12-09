#include <stdio.h>
int main(void)
{
    int i;
    double sum = 0.0;
    for (i = 0; i < 10000000; i++)
        sum += 0.1;
    printf("%lf\n", sum);
    return (0);
}