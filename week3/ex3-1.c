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
	double x[N];

	int i, j, k;

	// forward elimination
	for (k = 0; k < N - 1; k++) //引く行
	{
		for (i = k + 1; i < N; i++) //引かれる行
		{
			double alpha = a[i][k] / a[k][k];
			for (j = i - 1; j < N; j++) //列
			{
				a[i][j] -= alpha * a[k][j];
			}
			b[i] -= alpha * b[k];
		}
	}

	// backward substitution
	for (i = N - 1; i >= 0; i--)
	{
		float c = 0;
		if (i != N - 1)
		{
			for (k = N - 1; k > i; k--)
				c += a[i][k] * x[k];
		}
		x[i] = (b[i] - c) / a[i][i];
	}

	// print the results
	long ct = clock();
	double sec = (double)ct / CLOCKS_PER_SEC;
	printf("%f\n", sec);
	for (i = 0; i < N; i++)
		printf("%f\n", x[i]);

	return 0;
}
