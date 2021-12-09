#include <stdio.h>
#include <math.h>

#define N 5
#define eps 1e-10

int main()
{
    int i, j;
    int k = 0;
    double a[N][N] = {
        {10.0, 3.0, 1.0, 2.0, 1.0},
        {1.0, 19.0, 2.0, -1.0, 5.0},
        {-1.0, 1.0, 30.0, 1.0, 10.0},
        {-2.0, 0.0, 1.0, 20.0, 5.0},
        {-3.0, 5.0, 1.0, -2.0, 25.0}};
    double b[N] = {-22.0, 27.0, 89.0, -73.0, 22.0}, x[N] = {0.0, 0.0, 0.0, 0.0, 0.0}, xnew[N];
    double diff;

    while (1)
    {
        diff = 0.0;
        for (i = 0; i < N; i++)
        {
            xnew[i] = b[i];
            for (j = 0; j < N; j++)
            {
                if (j != i)
                {
                    xnew[i] -= a[i][j] * x[j];
                }
            }
            xnew[i] = xnew[i] / a[i][i];
        }

        for (i = 0; i < N; i++)
        {
            diff += (x[i] - xnew[i]) * (x[i] - xnew[i]);
            x[i] = xnew[i];
        }

        if (sqrt(diff) < eps)
        {
            break;
        }
        k++;
    }

    for (i = 0; i < N; i++)
    {
        printf("%f\n", xnew[i]);
    }

    printf("繰り返し回数: %d\n", k);

    return 0;
}