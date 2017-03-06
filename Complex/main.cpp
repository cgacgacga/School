/*Kuzminvinov Artem 10-4*/

#include <stdlib.h>
#include <glut.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


#define W 720
#define H 480
#define MagicalConstCRe  0.365
#define MagicalConstCIm  0.365

unsigned char Frame[H][W][3];

typedef struct {
	double Re, Im;
}  Complex;

Complex Mult(Complex A, Complex B)
{
	Complex Z;
	Z.Re = A.Re*A.Re - B.Im*B.Im;
	Z.Im = A.Re*A.Im + B.Re*B.Im;
	return Z;
}

Complex Addition(Complex A, Complex B)
{
	Complex Ans;
	Ans.Re = A.Re + B.Re;
	Ans.Im = A.Im + B.Im;
	return Ans;

}

double Length(Complex A)
{
	return A.Re * A.Re + A.Im * A.Im;
}

void Keyboard(unsigned char Key, int X, int Y)
{
	if (Key == 27)
		exit(0);
}

int ComplIter(Complex Z)
{
	int n = 0;

	Complex C;
	C.Re = MagicalConstCRe + 0.011 * fabs(sin(clock() / (double)CLOCKS_PER_SEC));
	C.Im = MagicalConstCIm + 0.011 * fabs(sin(clock() / (double)CLOCKS_PER_SEC));

	while (n++ <= 254 && Length(Z) <= 4)
		Z = Addition(Mult(Z, Z), C);


	return n;

}


void Build(void)
{
	int row, col;
	double x0 = -2, x1 = 2, y0 = -2, y1 = 2;
	double a, b;

	for (col = 0; col < H;col++)
	{
		for (row = 0; row < W; row++)
		{
			Complex Poop;
			int n;
			a = (double)(col*(x1 - x0)) / W + x0;
			b = (double)(row*(y1 - y0) / H) + y0;
			Poop.Re = a;
			Poop.Im = b;
			n = ComplIter(Poop);
			//printf("%i ", n);
			Frame[row][col][0] = n / 4;
			Frame[row][col][1] = n / 2;
			Frame[row][col][2] = n;

		}

	}


}

void Display(void)
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glRasterPos2d(-1, 1);
	glPixelZoom(1, -1);

	Build();

	glDrawPixels(W, H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);
	glFinish();

	glutSwapBuffers();
	glutPostRedisplay();
}


int main(int argc, char *argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(W, H);
	glutCreateWindow("Mandelbrot");
	
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);

	

	glutMainLoop();

	return 0;
}
