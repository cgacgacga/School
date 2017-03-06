/* main.c */
#define _CRT_SECURE_NO_WARNINGS

#include <glut.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/* Frame size */
INT FrameW = 256, FrameH = 256;

/* Frame array */
ULONG *Frame;

#define H 20
#define W 30

BOOL Field1[H][W]; /* 0 - dead
                    * 1 - alive
                    */
BOOL Field2[H][W];

DOUBLE
  Time,
  GlobalTime,
  DeltaTime,
  GlobalDeltaTime;

DOUBLE
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

/* Init life field function */
VOID FieldInit( VOID )
{
  INT x, y;

  memset(Field1, 0, sizeof(BOOL) * H * W);
  for (y = 0; y < H; y++)
    for (x = 0; x < W; x++)
      Field1[y][x] = rand() & 1;
} /* End of 'FieldInit' function */

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

/* Game step function */
VOID GameStep( VOID )
{
  INT ys, xs;

  for (ys = 0; ys < H; ys++)
    for (xs = 0; xs < W; xs++)
    {
      INT cnt_alive = 0;

      if (Field1[(ys + H) % H][(xs + 1 + W) % W])
        cnt_alive++;
      if (Field1[((ys + 1 + H) % H)][(xs + W) % W])
        cnt_alive++;
      if (Field1[(ys + 1 + H) % H][(xs + 1 + W) % W])
        cnt_alive++;
      if (Field1[(ys - 1 + H) % H][(xs + 1 + W) % W])
        cnt_alive++;


      if (Field1[(ys + H) % H][(xs - 1 + W) % W])
        cnt_alive++;
      if (Field1[(ys - 1 + H) % H][(xs + W) % W])
        cnt_alive++;
      if (Field1[((ys - 1 + H) % H)][((xs - 1 + W) % W)])
        cnt_alive++;
      if (Field1[((ys + 1 + H) % H)][((xs - 1 + W) % W)])
        cnt_alive++;

      if (Field1[(ys + H) % H][(xs + W) % W])
      {
        if (cnt_alive > 3 || cnt_alive < 2)
          Field2[(ys + H) % H][(xs + W) % W] = FALSE;
        else
          Field2[(ys + H) % H][(xs + W) % W] = TRUE;
      }
      else
      {
        if (cnt_alive == 3)
          Field2[(ys + H) % H][(xs + W) % W] = TRUE;
        else
          Field2[(ys + H) % H][(xs + W) % W] = FALSE;
      }
    }
  for (ys = 0; ys < H; ys++)
    for (xs = 0; xs < W; xs++)
    {
      BOOL tmp = Field1[ys][xs];

      Field1[ys][xs] = Field2[ys][xs], Field2[ys][xs] = tmp;
    }
  memset(Field2, 0, sizeof(BOOL) * W * H);
} /* End of 'GameStep' function */

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
  INT ys, xs;
  DOUBLE t = clock() / 1000.0, xz = (DOUBLE)FrameW / W, yz = (DOUBLE)FrameH / H;
  CHAR Buf[100];

  glClearColor(0.3, 0.5, 0.7, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glRasterPos2d(-1, 1);
  glPixelZoom(1, -1);

  FPSSupport();

  sprintf(Buf, "FPS: %.5f", FPS);
  glutSetWindowTitle(Buf);

  if (!IsPause)
    GameStep();

  for (ys = 0; ys < FrameH; ys++)
    for (xs = 0; xs < FrameW; xs++)
      if (Field1[(INT)(ys / yz)][(INT)(xs / xz)])
            PutPixel(xs, ys, 0xFFFFFF);
      else
        PutPixel(xs, ys, 0x0000);

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
  FieldInit();
  glViewport(0, 0, NewW, NewH);
} /* End of 'Reshape' function */

/* The main program function */
INT main( INT argc, CHAR *argv[] )
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(FrameW, FrameH);
  glutCreateWindow("My Window");
  Init();

  Frame = malloc(FrameW * FrameH * sizeof(ULONG));

  FieldInit();

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutReshapeFunc(Reshape);

  glutMainLoop();

  return 30;
} /* End of 'main' function */

/* END OF 'MAIN.C' FILE */
