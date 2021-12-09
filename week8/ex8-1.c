/* Gray-Scott ReactionDiffusion */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bmp.h"

/* 時間の設定 */

#define T_INIT 0.0
#define T_FINISH 10000.0
#define DT 1.0

/* 空間の設定 */

#define SIZE 128
#define DX (1.0 / (double)SIZE)

#define WIDTH SIZE
#define HEIGHT SIZE

/* 反応拡散系のパラメータ */

#define D_U 0.1
#define D_V 0.05

#define U_INIT 0.5
#define V_INIT 0.25
#define INIT_RADIUS 20

/* 画像ファイル出力 */

#define OUTPUT_FILE "grayscott%.3d.bmp"
#define OUTPUT_STEP 9999

/* グローバル変数の設定 */

double u[WIDTH][HEIGHT];
double u_new[WIDTH][HEIGHT];

double v[WIDTH][HEIGHT];
double v_new[WIDTH][HEIGHT];

unsigned char image[WIDTH * HEIGHT * 3];

int output_image_num = 1;

/* シミュレーション結果を画像に変換 */

void CopyFieldToImage(unsigned char *image)
{
	int x, y;
	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			unsigned char c = u[x][y] * 255;
			image[(x + y * WIDTH) * 3] = c;
			image[(x + y * WIDTH) * 3 + 1] = c;
			image[(x + y * WIDTH) * 3 + 2] = 255;
		}
	}
}

/* 画像の出力 */

void OutputImage(void)
{
	char filename[256]; /* sprintfは画面ではなく文字列に出力 */
	sprintf(filename, OUTPUT_FILE, output_image_num);
	CopyFieldToImage(image);
	WriteBMP(filename, image, WIDTH, HEIGHT);
	output_image_num++;
	printf("image output: %s\n", filename);
}

/* シミュレーションの初期化 */

double Random(double min, double max)
{
	return min + (max - min) * rand() / (double)RAND_MAX;
}

void InitField(void)
{
	int x, y;
	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			int dx = x - WIDTH / 2;
			int dy = y - HEIGHT / 2;
			if (dx * dx + dy * dy < INIT_RADIUS * INIT_RADIUS)
			{
				u[x][y] = U_INIT * Random(0.95, 1.05);
				v[x][y] = V_INIT * Random(0.95, 1.05);
			}
			else
			{
				u[x][y] = 1.0;
				v[x][y] = 0.0;
			}
		}
	}
}

/* ここからメイン */

int main(int argc, char **argv)
{
	int loop = (T_FINISH - T_INIT) / DT;
	int i, x, y;
	double t = T_INIT;
	double f, k;

	if (argc < 3)
	{
		fprintf(stderr, "usage: %s [F] [K]\n", argv[0]);
		return -1;
	}
	f = atof(argv[1]);
	k = atof(argv[2]);

	/* 乱数初期化 */
	srand(time(NULL));

	/* 濃度初期化 */
	InitField();

	/* 繰り返し */
	for (i = 0; i < loop; i++)
	{
		/* 濃度の更新 */
		for (y = 0; y < HEIGHT; y++)
		{
			for (x = 0; x < WIDTH; x++)
			{
				int xl = (x - 1 + WIDTH) % WIDTH; /* 周期境界条件 */
				int xr = (x + 1) % WIDTH;
				int yu = (y - 1 + HEIGHT) % HEIGHT;
				int yd = (y + 1) % HEIGHT;
				double diff_u = D_U * (u[xl][y] + u[xr][y] + u[x][yu] + u[x][yd] - 4 * u[x][y]);
				double diff_v = D_V * (v[xl][y] + v[xr][y] + v[x][yu] + v[x][yd] - 4 * v[x][y]);
				double reaction_uv = u[x][y] * v[x][y] * v[x][y];
				double du = diff_u - reaction_uv + f * (1 - u[x][y]);
				double dv = diff_v + reaction_uv - (f + k) * v[x][y];
				u_new[x][y] = u[x][y] + du * DT;
				v_new[x][y] = v[x][y] + dv * DT;
			}
		}
		for (y = 0; y < HEIGHT; y++)
		{
			for (x = 0; x < WIDTH; x++)
			{
				u[x][y] = u_new[x][y];
				v[x][y] = v_new[x][y];
			}
		}

		/* 定期的に画像出力 */
		if (i % OUTPUT_STEP == 0)
		{
			OutputImage();
		}

		/* 時刻を進める */
		t += DT;
	}

	return 0;
}
