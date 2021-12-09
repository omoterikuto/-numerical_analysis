/* bmp.h */

#ifndef BMP_H
#define BMP_H

unsigned char *ReadBMP(char *filename, int *p_width, int *p_height);
int WriteBMP(char *filename, unsigned char *buf, int width, int height);

#endif /* BMP_H */
