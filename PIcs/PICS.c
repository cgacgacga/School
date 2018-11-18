/*Kuzminov Artem, 13/03/2017, 10-4*/

#include <stdio.h>
#include <glut.h>
#include "pic.h"


extern unsigned char Frame[Frame_H][Frame_W][3];


void DrawPixel ( int x, int y, unsigned char r, unsigned char g, unsigned char b )
{

  if (x >= 0 && x < Frame_W && y >= 0 && y < Frame_H)
  {
      Frame[y][x][0] = b;
      Frame[y][x][1] = g;
      Frame[y][x][2] = r;
  }
  
  return ;
}
void DrawPicFile( char *FileName, int x0, int y0 )
{
  int size_x = 0, size_y = 0, x, y;
  unsigned char b, g, r;
  FILE *F;

  F = fopen(FileName, "rb");
  if (F == NULL)
  {
    printf("vse ploxo\n");   
    return ;
  }
    
  fread(&size_x, 2 , 1, F);
  fread(&size_y, 2 , 1, F);

 
  for (y = 0; y < size_y; y++)
    for (x = 0; x < size_x; x++)
    {
      fread(&b, 1, 1, F);
      fread(&g, 1, 1, F);
      fread(&r, 1, 1, F);
      
      //printf("%i %i %i\n", r, g, b);
      
      DrawPixel(x + x0, y + y0, r, g, b);

      r = 0;
      b = 0;
      g = 0;
    }
  
  fclose(F);
  return ;
}
