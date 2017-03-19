/* main.c */
#define _CRT_SECURE_NO_WARNINGS

#include <glut.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Frame size */
INT FrameW = 480, FrameH = 360;

/* Frame array */
ULONG *Frame;

DOUBLE
  Time,
  GlobalTime,
  DeltaTime,
  GlobalDeltaTime,
  FPS;

BOOL
IsPause = 0;

/* Timer local data */
static UINT64
StartTime,    /* Start program time */
OldTime,      /* Time from program start to previous frame */
OldTimeFPS,   /* Old time FPS measurement */
PauseTime,    /* Time during pause period */
TimePerSec,   /* Timer resolution */
FrameCounter; /* Frames counter */

typedef struct tagColor3B
{
  BYTE R, G, B;
} Color3B;

typedef struct tagPIC
{
  INT PicW, PicH;
  ULONG *Img;
} PIC;

PIC Picture;

/* Initialization time function */
VOID Init( VOID )
{
  LARGE_INTEGER t;

  /* Timer initialization */
  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  PauseTime = 0;
} /* End of 'Init' function */

/* Frames per second support function */
VOID FPSSupport( VOID )
{
  LARGE_INTEGER t;

  /*** Handle timer ***/
  QueryPerformanceCounter(&t);
  /* Global time */
  GlobalTime = (DOUBLE)(t.QuadPart - StartTime) / TimePerSec;
  GlobalDeltaTime = (DOUBLE)(t.QuadPart - OldTime) / TimePerSec;

  if (IsPause)
  {
    DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    DeltaTime = GlobalDeltaTime;
    Time = (DOUBLE)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }

  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    FPS = FrameCounter * TimePerSec / (DOUBLE)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;
} /* End of 'FPSSupport' function */

/* Load image (*.G24) function. */
BOOL PicLoad( CHAR *Filename )
{
  FILE *F;
  INT x, y;
  Color3B C;

  if ((F = fopen(Filename, "rb")) == NULL)
    return FALSE;
  fread(&Picture.PicW, 2, 1, F);
  fread(&Picture.PicH, 2, 1, F);
  if ((Picture.Img = malloc(sizeof(ULONG) * Picture.PicH * Picture.PicW)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  for (y = 0; y < Picture.PicH; y++)
    for (x = 0; x < Picture.PicW; x++)
    {
      fread(&C, 3, 1, F);
      Picture.Img[x + y * Picture.PicW] = RGB(C.B, C.G, C.R);
    }
  fclose(F);
  return TRUE;
} /* End of 'PicLoad' function */

/* Put pixel to frame function */
VOID PutPixel( INT X, INT Y, ULONG Color )
{
  if (X < 0 || X > FrameW || Y < 0 || Y > FrameH)
    return;
  Frame[Y * FrameW + X] = Color;
} /* End of 'PutPixel' function */

/* Display function */
static VOID Display( VOID )
{
  DOUBLE t = Time / 1000.0;
  CHAR Buf[100];
  DOUBLE RandX = rand() % (FrameW - Picture.PicW), RandY = rand() % (FrameH - Picture.PicH);
  INT x, y;

  glClearColor(0.3, 0.5, 0.7, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glRasterPos2d(-1, 1);
  glPixelZoom(1, -1);

  FPSSupport();

  sprintf(Buf, "FPS: %.5f", FPS);
  glutSetWindowTitle(Buf);

  if (PicLoad("X:\\PICS\\M.G24"))
    for (y = 0; y < Picture.PicH; y++)
      for (x = 0; x < Picture.PicW; x++)
        PutPixel(x + RandX, y + RandY, Picture.Img[x + y * Picture.PicW]);
  glDrawPixels(FrameW, FrameH, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Frame);
  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
} /* End of 'Display' function*/

/* Keyboard function */
static VOID Keyboard( BYTE Key, INT X, INT Y )
{
  if (Key == 27)
  {
    free(Frame);
    PostQuitMessage(30);
  }
  if (Key == VK_SPACE)
    IsPause = !IsPause;
} /* End of 'Keyboard' function */

/* Reshape function */
static VOID Reshape( INT NewW, INT NewH )
{
  free(Frame);
  Frame = malloc(sizeof(ULONG) * NewW * NewH);
  FrameW = NewW;
  FrameH = NewH;
  glViewport(0, 0, NewW, NewH);
} /* End of 'Reshape' function */

/* The main program function */
INT main( INT argc, CHAR *argv[] )
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(FrameW, FrameH);
  glutCreateWindow("");
  Init();

  Frame = malloc(FrameW * FrameH * sizeof(ULONG));

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutReshapeFunc(Reshape);

  glutMainLoop();

  return 0;
} /* End of 'main' function */

/* END OF 'MAIN.C' FILE */
