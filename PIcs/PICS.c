  /*Kuzminov Artem, 13/03/2017, 10-4*/

#include <stdio.h>
#include <glut.h>
#include "pic.h"

extern unsigned char Frame[Frame_H][Frame_W][3];


void DrawPixel ( int x, int y, int r, int b, int g)
{
      Frame[y][x][0] = b;
      Frame[y][x][1] = g;
      Frame[y][x][2] = r;
 
}
void DrawPicFile( char *FileName, int x0, int y0 )
{
  int size_x = 0, size_y = 0, x, y;
  unsigned char b, g, r;
  FILE *F;

  F = fopen(FileName, "r");
  if (F == NULL)
  {
    printf("vse ploxo\n");
  }
  else
  {
    fread(&(size_x), 2 , 1, F);
    fread(&(size_y), 2 , 1, F);

    for (y = 0; y < size_y; y++)
      for (x = 0; x < size_x; x++)
      {
        fread(&b, 1, 1, F);
        fread(&g, 1, 1, F);
        fread(&r, 1, 1, F);

        DrawPixel(x + x0, y + y0, r, g, b);
      }
  }
}
