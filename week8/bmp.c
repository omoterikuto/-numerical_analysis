/* bmp.c */

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

#define BMP_HEADER_SIZE 54

static int GetInt(unsigned char *p)
{
  int r = 0;
  int i;

  p += 3;
  for (i = 0; i < 4; i++) {
    r <<= 8;
    r += (int) *p;
    p--;
  }

  return r;
}

unsigned char *
ReadBMP(char *filename, int *p_width, int *p_height)
{
  unsigned char h[BMP_HEADER_SIZE];
  unsigned char *buf;
  FILE *fp;
  int i;
  int width, height;
  int line_bytes;

  if ((fp = fopen(filename, "rb")) == NULL) {
    return (NULL);
  }
  fread(h, 1, BMP_HEADER_SIZE, fp);

  width = GetInt(h + 18);
  height = GetInt(h + 22);

  line_bytes = ((width * 3 + 3) / 4) * 4;

  buf = (unsigned char *) malloc(width * height * 3);

  for (i = height - 1; i >= 0; i--) {
    unsigned char dummy[3];
    fread(buf + width * 3 * i, 1, width * 3, fp);
    if (line_bytes - width * 3 > 0) {
      fread(dummy, 1, line_bytes - width * 3, fp);
    }
  }
  fclose(fp);
 
  for (i = 0; i < width * height; i++) {
    unsigned char tmp = buf[i * 3];
    buf[i * 3] = buf[i * 3 + 2];
    buf[i * 3 + 2] = tmp;
  }

  *p_width = width;
  *p_height = height;

  return buf;
}

int WriteBMP(char *filename, unsigned char *buf, int width, int height)
{
  unsigned char h[BMP_HEADER_SIZE];
  FILE *fp;
  int i;
  int line_bytes;

  line_bytes = ((width * 3 + 3) / 4) * 4;
 
  for (i = 0; i < BMP_HEADER_SIZE; i++) {
    h[i] = 0;
  }
 
  h[0] = 'B';
  h[1] = 'M';
  *(int *)(h + 2) = (int)(line_bytes * height * 3 + BMP_HEADER_SIZE);
  *(int *)(h + 10) = (int) BMP_HEADER_SIZE;
  *(int *)(h + 14) = (int) BMP_HEADER_SIZE - 14;
  *(int *)(h + 18) = (int) width;
  *(int *)(h + 22) = (int) height;
  *(short *)(h + 26) = (short) 1;
  *(short *)(h + 28) = (short) 24;

  for (i = 0; i < width * height; i++) {
    unsigned char tmp = buf[i * 3];
    buf[i * 3] = buf[i * 3 + 2];
    buf[i * 3 + 2] = tmp;
  }
 
  if ((fp = fopen(filename, "wb")) == NULL) {
    return (-1);
  }
  fwrite(h, 1, BMP_HEADER_SIZE, fp);

  for (i = height - 1; i >= 0; i--) {
    unsigned char dummy[3] = { 0, 0, 0 };
    fwrite(buf + width * 3 * i, 1, width * 3, fp);
    if (line_bytes - width * 3 > 0) {
      fwrite(dummy, 1, line_bytes - width * 3, fp);
    }
  }
  fclose(fp);

  return 0;
}



#if 0

int
main(int argc, char **argv)
{
  unsigned char *buf;
  int width, height;

  buf = ReadBMP(argv[1], &width, &height);
  WriteBMP(argv[2], buf, width, height);

  return 0;
}

#endif
