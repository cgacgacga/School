/* Load & draw progect declaration functions module.
 * Written by: Smirnov Arsenty 10-4
 * Last update 27.11.2016
 */

#ifndef __DPIC_H_
#define __DPIC_H_

#include <windows.h>

typedef struct tagPIC
{
  INT PicW, PicH;
  ULONG *Pixels;
} PIC;

extern INT FrameW, FrameH;
extern ULONG *Frame;

/* Picture load function */
BOOL PicLoad( PIC *P, CHAR *Filename );

/* Picture create function */
BOOL PicCreate( PIC *P, INT W, INT H );

/* Picture free function */
VOID PicFree( PIC *P );

/* Picture draw function */
VOID PicDraw( PIC *P, INT X0, INT Y0 );

/* LUT negative function */
VOID LUTNegative( VOID );

/* LUT apply function */
VOID LUTApply( PIC *Dest, PIC *Src );

#endif /* __DPIC_H_ */

/* END OF 'DPIC.H' FILE */

