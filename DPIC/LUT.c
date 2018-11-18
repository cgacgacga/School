/*Kuzminov Artem, 10-4, 24.04.17 */
#include <stdio.h>
#include <math.h>
#include "dpic.h"


void LUTApply ( IMG *Dst, IMG *Src, byte *LUT )
{
  int x, y, c;

  for (y = 0; y < Src->H; y++)
    for (x = 0; x < Src->W; x++) 
      for (c = 0; c < 3; c++)
        Dst->PIXELS[y * Dst->W + x][c] = LUT[Src->PIXELS[y * Src->W + x][c]];
}

void LUTSetCopy ( byte *LUT )
{
  int i;

  for (i = 0; i < 256; i++)
    LUT[i] = i;
}

void LUTSetNegative ( byte *LUT )
{
  int i;

  for (i = 0; i < 256; i++)
    LUT[i] = 255 - i;
}

int Clamp ( int x, int A, int B )
{
  if (x < A)
    return A;
  if (x > B)
    return B;
  return x;
}

void LUTSetBrightness ( byte *LUT, int Di )
{
  int i;

  for (i = 0; i < 256; i++)
    LUT[i] = Clamp(i + Di, 0, 255);
}

void LUTSetContrast ( byte *LUT, int A, int B )
{
  int i;

  for (i = 0; i < 256; i++)
    LUT[i] = Clamp(255 * (i - A) / (B - A), 0, 255);
  
}

void LUTSetGamma ( byte *LUT, double Gamma )
{
  int i;

  for (i = 0; i < 256; i++)
    LUT[i] = (byte)(255 * pow(i / 255.0, 1 / Gamma));
}


void LUTSetPoster ( byte *LUT, int Levels )
{
  int i;

  for (i = 0; i < 256; i++)
    LUT[i] = i / (255 / Levels) * (255 / Levels);
}


void LUTSetAutoContrast ( byte *LUT, IMG *P )
{ 
  int x, y, c, max = 0, min = 255;

  for (y = 0; y < P->H; y++)
    for (x = 0; x < P->W; x++)
      for (c = 0; c < 3; c++)
      {
        if (min > P->PIXELS[y * P->W + x][c])
          min = P->PIXELS[y * P->W + x][c];
        if (max < P->PIXELS[y * P->W + x][c])
          max = P->PIXELS[y * P->W + x][c];
      }
 LUTSetContrast(LUT, min, max);
}
/*Kuzminov Artem, 10-4, 24.04.17 */
#include <stdio.h>
#include <math.h>
#include "dpic.h"


void LUTApply ( IMG *Dst, IMG *Src, byte *LUT )
{
  int x, y, c;

  for (y = 0; y < Src->H; y++)
    for (x = 0; x < Src->W; x++) 
      for (c = 0; c < 3; c++)
        Dst->PIXELS[y * Dst->W + x][c] = LUT[Src->PIXELS[y * Src->W + x][c]];
}

void LUTSetCopy ( byte *LUT )
{
  int i;

  for (i = 0; i < 256; i++)
    LUT[i] = i;
}

void LUTSetNegative ( byte *LUT )
{
  int i;

  for (i = 0; i < 256; i++)
    LUT[i] = 255 - i;
}

int Clamp ( int x, int A, int B )
{
  if (x < A)
    return A;
  if (x > B)
    return B;
  return x;
}

void LUTSetBrightness ( byte *LUT, int Di )
{
  int i;

  for (i = 0; i < 256; i++)
    LUT[i] = Clamp(i + Di, 0, 255);
}

void LUTSetContrast ( byte *LUT, int A, int B )
{
  int i;

  for (i = 0; i < 256; i++)
    LUT[i] = Clamp(255 * (i - A) / (B - A), 0, 255);
  
}

void LUTSetGamma ( byte *LUT, double Gamma )
{
  int i;

  for (i = 0; i < 256; i++)
    LUT[i] = (byte)(255 * pow(i / 255.0, 1 / Gamma));
}


void LUTSetPoster ( byte *LUT, int Levels )
{
  int i;

  for (i = 0; i < 256; i++)
    LUT[i] = i / (255 / Levels) * (255 / Levels);
}


void LUTSetAutoContrast ( byte *LUT, IMG *P )
{ 
  int x, y, c, max = 0, min = 255;

  for (y = 0; y < P->H; y++)
    for (x = 0; x < P->W; x++)
      for (c = 0; c < 3; c++)
      {
        if (min > P->PIXELS[y * P->W + x][c])
          min = P->PIXELS[y * P->W + x][c];
        if (max < P->PIXELS[y * P->W + x][c])
          max = P->PIXELS[y * P->W + x][c];
      }
 LUTSetContrast(LUT, min, max);
}
