/*Kuzminov Artem, 10-4, 10.04.17 */
#include <glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "dpic.h"


IMG Src;

void Display (void)
{

  glClearColor(0.3, 0.5, 0.7, 1); 
  glClear(GL_COLOR_BUFFER_BIT);
  /*ImageDraw(&Src, 0, 0);
  ImageCreate(&Dest, Src.W, Src.H);
  Negative(&Src, &Dest);
  ImageDraw(&Dest, Src.W, 0);
  ImageFree(&Dest);
  ImageDraw(&Src, 0, 0);*/ 
  glRasterPos2d(-1, 1);
  glPixelZoom(1, -1);
  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, FRAME);
  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
  
}

void Keyboard (unsigned char Key, int X, int Y)
 {
   if (Key == 27)
     exit(0);
 }



int main (int argc, char *argv[])

{
  IMG P1, P2;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(3, 3);
  glutInitWindowSize(FRAME_W, FRAME_H); 
  glutCreateWindow("DPIC");
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  if (ImageLoad(&P1, "X:\\PICS\\M.G24"))
  {
    ImageDraw (&P1, 0, 0);
    if (ImageCreate(&P2, P1.W, P1.H))
    {
      byte LUT[256];

      LUTSetCopy(LUT);
      LUTApply(&P2, &P1, LUT);
      ImageDrawAuto(&P2);
     

      LUTSetNegative(LUT);
      LUTApply(&P2, &P1, LUT);
      ImageDrawAuto(&P2);
   
      
      LUTSetBrightness(LUT, +30);
      LUTApply(&P2, &P1, LUT);
      ImageDrawAuto(&P2);

      LUTSetBrightness(LUT, -30);
      LUTApply(&P2, &P1, LUT);
      ImageDrawAuto(&P2);
       
      LUTSetContrast(LUT, 50,  205);
      LUTApply(&P2, &P1, LUT);
      ImageDrawAuto(&P2);
      
      LUTSetContrast(LUT, -50,  305);
      LUTApply(&P2, &P1, LUT);
      ImageDrawAuto(&P2);
       
      LUTSetGamma(LUT, 3);
      LUTApply(&P2, &P1, LUT);
      ImageDrawAuto(&P2);
       
      LUTSetGamma(LUT, 0.5);
      LUTApply(&P2, &P1, LUT);
      ImageDrawAuto(&P2);
        
      LUTSetAutoContrast(LUT, &P1);
      LUTApply(&P2, &P1, LUT);
      ImageDrawAuto(&P2);

      LUTSetPoster(LUT, 2);
      LUTApply(&P2, &P1, LUT);
      ImageDrawAuto(&P2);

      LUTSetPoster(LUT, 3);
      LUTApply(&P2, &P1, LUT);
      ImageDrawAuto(&P2);

      LUTSetPoster(LUT, 5);
      LUTApply(&P2, &P1, LUT);
      ImageDrawAuto(&P2);

      Negative(&P1, &P2);
      ImageDrawAuto(&P2);
      
      Blur(&P1, &P2);
      ImageDrawAuto(&P2);


      ImageFree(&P2);
    }
    ImageFree(&P1);
  } 
 /* if (!ImageLoad(&Src, "X:\\PICS\\M.G24"))
     return 0;*/
  glutMainLoop();
}
