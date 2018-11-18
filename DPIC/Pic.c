/*Kuzminov Artem, 10-4, 10.04.17*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dpic.h"

void DrawPixel ( int x, int y, unsigned char r, unsigned char g, unsigned char b )
{
  if (x >= 0 && x < FRAME_W && y >= 0 && y < FRAME_H)
  {
    FRAME[y][x][0] = b;
    FRAME[y][x][1] = g;
    FRAME[y][x][2] = r;
  }
}

void ImageDraw( IMG *P, int x0,  int y0 )
{
  int x, y;

  if (P->PIXELS == NULL)
    return;
  for (y = 0; y < P->H; y++)
    for (x = 0; x < P->W; x++)
      DrawPixel(x0 + x, y0 + y,  P->PIXELS[y * P->W + x][2], P->PIXELS[y * P->W + x][1], P->PIXELS[y * P->W + x][0]);
}

void ImageDrawAuto( IMG *P )
{
  static int x0 = 0, y0 = 0;
  static int lineH = 0;

  if (x0 + P->W >= FRAME_W)
  {
    y0 += lineH;
    x0 = 0;
    lineH = 0;
  }
  ImageDraw(P, x0, y0);
  if (lineH < P->H)
    lineH = P->H;
  x0 += P->W;
}


int ImageCreate ( IMG *P, int NewW, int NewH )
{
  P->H = NewH;
  P->W = NewW;
  P->PIXELS = malloc(NewW * NewH * sizeof(RGB));
  if (P->PIXELS == NULL)
    return 0;
  memset(P->PIXELS, 0, NewW * NewH * sizeof(RGB));
  return 1;
}  

int ImageLoad( IMG *P, char *FileName )
{
  FILE*F;
  int W = 0;
  int H = 0;
  
  if ((F= fopen(FileName, "rb")) == NULL)
    return 0;
  fread(&W, 2, 1, F);
  fread(&H, 2, 1, F);
  ImageCreate(P, W, H);
  if (!ImageCreate(P, W, H))
  {
    fclose(F);
    return 0;
  }
  fread(P->PIXELS, 3, W * H, F);
  fclose(F);
  return 1;
}

void ImageFree ( IMG *P )
{                
  if (P->PIXELS != NULL)
    return;
  free(P->PIXELS);
  P->W = P->H = 0;
  P->PIXELS = NULL;
}

void Negative ( IMG *Src, IMG *Dest )
{
  int x, y;

  for (y = 0; y < Src->H; y++)
    for(x = 0; x < Src->W; x++)
    {     
      Dest->PIXELS[y * Src->W + x][2] = 255 - Src->PIXELS[y * Src->W + x][2];
      Dest->PIXELS[y * Src->W + x][1] = 255 - Src->PIXELS[y * Src->W + x][1];
      Dest->PIXELS[y * Src->W + x][0] = 255 - Src->PIXELS[y * Src->W + x][0];
    }
}

void Square ( IMG *Src, IMG *Dest, int x0, int y0, int sqr )
{
  int x, y, r = 0, g = 0, b = 0, cnt; 

  for (y = y0; y < y0 + sqr; y++)
  {
    for (x = x0; x < x0 + sqr; x++)
    {
      r += Src->PIXELS[y * Src->W + x][2];
      g += Src->PIXELS[y * Src->W + x][1];
      b += Src->PIXELS[y * Src->W + x][0];
    }
  }
  r /= 25;
  g /= 25;
  b /= 25;


  for (y = y0; y < y0 + sqr; y++)
    for(x = x0; x < x0 + sqr; x++)
    {                             
      Dest->PIXELS[y * Src->W + x][2] = r;
      Dest->PIXELS[y * Src->W + x][1] = g;
      Dest->PIXELS[y * Src->W + x][0] = b;
    }
}

void Blur ( IMG *Src, IMG *Dest )
{
  int x, y, r = 0, g = 0, b = 0, sqr = 5;
  for (y = 0; y < Src->H; y++)
  {
    for (x = 0; x < Src->W; x++)
    {
      if (y + sqr < Src->H && x + sqr < Src->W)
        Square(Src, Dest, x, y, sqr);
    }

  }


}
