/* Picture load & draw project.
 * Written by: Smirnov Arsenty 10-4
 * Last update: 27.11.2016
 */

#include <stdlib.h>

#include "D:/Lib/glut/glut.h"
#include "dpic.h"

INT FrameH = 540, FrameW = 960;  /* Frame size */

ULONG *Frame;                    /* Main frame array */

PIC Picture;                          /*  */

/* Initialization function */
static BOOL Init( VOID )
{
  PIC P1;

  if ((Frame = malloc(sizeof(ULONG) * FrameW * FrameH)) == NULL)
    return FALSE;

  if (!PicLoad(&Picture, "D:\\PYATACK.G24"))
  {
    free(Frame);
    return FALSE;
  }
  PicDraw(&Picture, 0, 0);
  PicCreate(&P1, Picture.PicW, Picture.PicH);
  LUTNegative();
  LUTApply(&P1, &Picture);
  PicDraw(&P1, P1.PicW, 0);

  return TRUE;
} /* End of 'Init' function */

/* Display initialize function */
static VOID Display( VOID )
{
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.3, 0.5, 0.7, 1);

  glRasterPos2d(-1, 1);
  glPixelZoom(5, -5);

  glDrawPixels(FrameW, FrameH, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Frame);

  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
} /* End of 'Display' function */

/* Keyboard initialize function */
static VOID Keyboard( BYTE Key, INT X, INT Y )
{
  if (Key == 27)
    PostQuitMessage(30);
} /* End of 'Keyboard' function */

/* The main program function */
INT main( INT argc, char *argv[] )
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB / GLUT_DOUBLE);
  glutInitWindowSize(960, 540);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("CGSG forever!!!");

  if (!Init())
    return 569;

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  glutMainLoop();
  return 0;
} /* end of 'main' function */

/* END OF 'T28DPIC.C' FILE */
