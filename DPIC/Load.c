#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "..\\dpic.h"

/* Picture load function */
BOOL PicLoad( PIC *P, CHAR *Filename )
{
  INT W = 0, H = 0, x, y;
  BYTE r, g, b;
  FILE *F;

  if ((F = fopen(Filename, "rb")) == NULL)
    return FALSE;
  fread(&W, 2, 1, F);
  fread(&H, 2, 1, F);
  if (!PicCreate(P, W, H))
  {
    fclose(F);
    return FALSE;
  }
  for (y = 0; y < H; y++)
    for (x = 0; x < W; x++)
    {
      fread(&b, 1, 1, F);
      fread(&g, 1, 1, F);
      fread(&r, 1, 1, F);
      P->Pixels[x + y * W] = RGB(r, g, b);
    }
  fclose(F);
  return TRUE;
} /* End of 'PicLoad' function */

/* END OF 'LOAD.C' FILE */
