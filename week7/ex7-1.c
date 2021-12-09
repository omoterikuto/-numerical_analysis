#include <stdio.h>
#include <stdlib.h>

#define T_INIT 0.0
#define T_FINISH 1.0
#define DT 1e-4

#define N 20				 /* Number of space division */
#define DX (1.0 / (double)N) /* Space resolution */

double InitFunc(double x)
{
	/*** make a function pulls x and outpus an initial value at x ***/
	return x <= 1 / 2 ? 0 : 1;
}

int main(void)
{
	int loop = T_FINISH / DT;
	int i, j;

	double t = T_INIT;

	/*** declare double-type array variable u and u_new ***/
	double u[N], new_u[N];

	/* initialize u */
	for (int i = 0; i < N; i++)
	{
		u[i] = 0;
		new_u[i] = 0;
	}

	for (int i = 0; i <= N; i++)
	{
		/*** calculate x from the node i ***/
		double x = i * DT;
		/*** call InitFunc function ***/
		u[i] = InitFunc(x);
	}

	/* repeat */

	for (j = 0; j < loop; j++)
	{
		double a = DT / (DX * DX);

		for (i = 1; i < N; i++)
		{
			/*** calculate new_u[i] from u[i+1],u[i],u[i-1] ***/
			new_u[i] = a * u[i + 1] + (1 - 2 * a) * u[i] + a * u[i - 1];
		}

		/* apply boundary condition */
		new_u[0] = 0;
		new_u[N - 1] = 1;

		/* update u */
		for (int i = 0; i < N; i++)
		{
			u[i] = new_u[i];
		}

		/* update time */
		t = j * DT;
		if (t >= 0.1)
		{
			break;
		}
	}

	/*** output u as a file to diaplay a graph using gnuplot ***/
	for (i = 0; i < N; i++)
	{
		printf("%6.6f %6.6f\n", i / (double)N, u[i]);
	}

	return 0;
}
