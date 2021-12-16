#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "bmp.h"

/* 時間の設定 */
#define T_INIT 0.0
#define T_FINISH 1
#define DT 1e-4

/* 空間の設定 */

#define SIZE 256
#define DX (1.0 / (double)SIZE)

#define WIDTH SIZE
#define HEIGHT SIZE

/* 画像ファイル出力 */
#define OUTPUT_FILE "wave%.3d.bmp"
#define OUTPUT_STEP 100

/* グローバル変数の設定 */

double u[WIDTH][HEIGHT];
double u_new[WIDTH][HEIGHT];
double u_old[WIDTH][HEIGHT];

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
			unsigned char c = u[x][y] * 128 + 128;
			image[(x + y * WIDTH) * 3] = c;
			image[(x + y * WIDTH) * 3 + 1] = c;
			image[(x + y * WIDTH) * 3 + 2] = 255;
		}
	}
}

/* 画像の出力 */

void OutputImage(void)
{
	char filename[256]; /* sprintfは画面でゃなく文字列に出力 */
	sprintf(filename, OUTPUT_FILE, output_image_num);
	CopyFieldToImage(image);
	WriteBMP(filename, image, WIDTH, HEIGHT);
	output_image_num++;
	printf("image output: %s\n", filename);
}

/* シミュレーションの初期化 */

void InitField(void)
{
	int x, y;
	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			if (x == WIDTH / 4 && y == HEIGHT / 2)
			{
				u[x][y] = 1.0;
				u_old[x][y] = 1.0;
			}
			else if (x == WIDTH * 3 / 4 && y == HEIGHT / 2)
			{
				u[x][y] = 1.0;
				u_old[x][y] = 1.0;
			}
			else
			{
				u[x][y] = 0.0;
				u_old[x][y] = 0.0;
			}
		}
	}
}

/* ここからメイン */

int main(void)
{
	int loop = (T_FINISH - T_INIT) / DT;
	int i, x, y;
	double t = T_INIT;

	/* 初期化 */
	InitField();

	double a = (DT * DT) / (DX * DX);

	/* 繰り返し */
	for (i = 0; i < loop; i++)
	{

		/* 変位の更新 */
		for (y = 1; y <= HEIGHT - 2; y++)
		{
			for (x = 1; x <= WIDTH - 2; x++)
			{
				int xl = x - 1; /* 周期境界条件ではない */
				int xr = x + 1;
				int yu = y - 1;
				int yd = y + 1;
				if (x == WIDTH / 4 && y == HEIGHT / 2)
					u_new[x][y] = cos(10 * M_PI * t);
				else if (x == WIDTH * 3 / 4 && y == HEIGHT / 2)
					u_new[x][y] = cos(10 * M_PI * t);
				else
					u_new[x][y] = a * (u[xr][y] + u[xl][y] + u[x][yu] + u[x][yd] - 4 * u[x][y]) + 2 * u[x][y] - u_old[x][y];
			}
		}

		/* 境界条件*/
		for (y = 0; y <= HEIGHT - 1; y++)
		{
			u_new[0][y] = 0;
			u_new[WIDTH - 1][y] = 0;
		}
		for (x = 0; x <= WIDTH - 1; x++)
		{
			u_new[x][0] = 0;
			u_new[x][HEIGHT - 1] = 0;
		}

		/* u, u_oldを更新 */
		for (x = 0; x <= WIDTH - 1; x++)
		{
			for (y = 0; y <= HEIGHT - 1; y++)
			{
				u_old[x][y] = u[x][y];
				u[x][y] = u_new[x][y];
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
