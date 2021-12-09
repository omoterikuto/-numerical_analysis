#include <stdio.h>
#include <time.h>

#define N 3

int main(void)
{
	double a[N][N] = {
		{2, -2, 1},
		{2, -1, 5},
		{-1, 3, 3}};
	double b[N] = {-11, 18, 41};
	double x[N], y[N];
	double u[N][N], l[N][N];

	int i, j, k;

	// LU decomposition
	for (j = 0; j < N; j++)
	{
		for (i = 0; i <= j; i++)
		{
			u[i][j] = a[i][j];
			for (k = 0; k <= i - 1; k++)
			{
				u[i][j] -= (l[i][k] * u[k][j]);
			}
		}

		for (i = j + 1; i < N; i++)
		{
			l[i][j] = a[i][j];
			for (k = 0; k <= j - 1; k++)
			{
				l[i][j] -= (l[i][k] * u[k][j]);
			}
			l[i][j] = (l[i][j] / u[j][j]);
		}
	}
	for (i = 0; i < N; i++)
	{
		l[i][i] = 1;
	}

	// substitution
	for (i = 0; i < N; i++)
	{
		y[i] = b[i];
		for (j = 0; j <= i - 1; j++)
		{
			y[i] -= (l[i][j] * y[j]);
		}
	}

	for (i = N - 1; i >= 0; i--)
	{
		x[i] = y[i];
		for (j = N - 1; j > i; j--)
		{
			x[i] -= (u[i][j] * x[j]);
		}
		x[i] /= u[i][i];
	}

	// 実行時間
	long ct = clock();
	double sec = (double)ct / CLOCKS_PER_SEC;
	printf("%f\n", sec);

	// print x vector
	for (i = 0; i < N; i++)
	{
		printf("%f\n", x[i]);
	}

	return 0;
}
