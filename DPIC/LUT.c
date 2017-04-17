#include "..\\dpic.h"

static BYTE LUT[256];

/* LUT apply function */
VOID LUTApply( PIC *Dest, PIC *Src )
{
  INT y, x;

  for (y = 0; y < Src->PicH; y++)
    for (x = 0; x < Src->PicW; x++)
      Dest->Pixels[x + y * Src->PicW] = RGB(LUT[(BYTE)(Src->Pixels[x + y * Src->PicW] >> 16)],
                                            LUT[(BYTE)(Src->Pixels[x + y * Src->PicW] >> 8)],
                                            LUT[(BYTE)(Src->Pixels[x + y * Src->PicW])]);
} /* End of 'LUTApply' function */

/* LUT negative function */
VOID LUTNegative( VOID )
{
  INT i;

  for (i = 0; i < 256; i++)
    LUT[i] = 255 - i;
} /* End of 'LUTNegative' function */

/* END OF 'LUT.C' FILE */
