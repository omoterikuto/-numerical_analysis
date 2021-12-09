#include <stdio.h>
#include <stdlib.h>

#define T_INIT 0.0
#define T_FINISH 1.0

double InitFunc(double x)
{
	/*** make a function pulls x and outpus an initial value at x ***/
	return x <= 1 / 2 ? 0 : 1;
}

int main(void)
{
	double deltaT;
	int n;
	scanf("%lf %d", &deltaT, &n);
	double dx = (1.0 / (double)n);
	int loop = T_FINISH / deltaT;
	int i, j;

	double t = T_INIT;

	/*** declare double-type array variable u and u_new ***/
	double u[n], new_u[n];

	/* initialize u */
	for (int i = 0; i < n; i++)
	{
		u[i] = 0;
		new_u[i] = 0;
	}

	for (int i = 0; i <= n; i++)
	{
		/*** calculate x from the node i ***/
		double x = i * deltaT;
		/*** call InitFunc function ***/
		u[i] = InitFunc(x);
	}

	/* repeat */

	for (j = 0; j < loop; j++)
	{
		double a = deltaT / (dx * dx);

		for (i = 1; i < n; i++)
		{
			/*** calculate new_u[i] from u[i+1],u[i],u[i-1] ***/
			new_u[i] = a * u[i + 1] + (1 - 2 * a) * u[i] + a * u[i - 1];
		}

		/* apply boundary condition */
		new_u[0] = 0;
		new_u[n - 1] = 1;

		/* update u */
		for (int i = 0; i < n; i++)
		{
			u[i] = new_u[i];
		}

		/* update time */
		t = j * deltaT;
		if (t >= 0.1)
		{
			break;
		}
	}

	/*** output u as a file to diaplay a graph using gnuplot ***/
	for (i = 0; i < n; i++)
	{
		printf("%6.6f %6.6f\n", i / (double)n, u[i]);
	}

	return 0;
}
