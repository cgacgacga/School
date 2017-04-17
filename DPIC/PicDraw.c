#include "..\\dpic.h"

/* Picture draw function */
VOID PicDraw( PIC *P, INT X0, INT Y0 )
{
  INT y, x;

  for (y = 0; y < P->PicH; y++)
    for (x = 0; x < P->PicW; x++)
      if (!(x + X0 < 0 || x + X0 >= FrameW || y + Y0 < 0 || y + Y0 >= FrameH))
        Frame[x + X0 + (y + Y0) * FrameW] = P->Pixels[x + y * P->PicW];
} /* End of 'PicDraw' function */

/* END OF 'PICDRAW.C' FILE */
