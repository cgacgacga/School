/*Kuzminvinov Artem 10-4*/

#include <stdlib.h>
#include <glut.h>
#define W 500
#define H 500
#define MagicalConstCRe  0,36
#define MagicalConstCIm  0,34


typedef struct{
 double Re, Im;
}  Complex;


double Mult (Complex A, Complex B)
{
  return (A.Re * B.Im + B.Re * A.Re );
}

Complex Addition (Complex A, Complex B)
{
  Complex Ans;
  Ans.Re = A.Re + B.Re;
  Ans.Im = A.Im + B.Im;
  return Ans;

}

void Keyboard( unsigned char Key, int X, int Y )
{
  if (Key == 27)
    exit(0);
}

void Display( void )
{
  glClearColor(0,0,0,1);
  glClear(GL_COLOR_BUFFER_BIT);

  glFinish();

  glutSwapBuffers();

  glutPostRedisplay();
}

int ComplIter (Complex Z)
{
  int n = 0;
  Complex C;
  C.Re = MagicalConstCRe;
  C.Im = MagicalConstCIm;

  whille( n++ <= 254 && Mult(Z,Z) < 4)
    Z = Addition(Mult(Z,Z), C) 
  return n;

}

void Build ( unsigned char)
{
  int row,col;
  for (col = 0; i < H;i++)
  {
    for (row = 0; j < W; j++)
    {
      Complex Poop;
      int n;
      Poop.Re = col;
      Poop.Im = row;
      n = CompIter(Poop);
      Frame[col][row][0] = n;
      Frame[col][row][1] = n/2;
      Frame[col][row][2] = n/4;

    }

  }


}

int main ( int argc, char *argv[] )
{
  glutInit( &argc, argv);
  
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(W, H);
  glutCreateWindow("");

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);

  double Frame [H][W][3];


  glutMainLoop();

  return 0;
}
