/*Kuzminov Artem 10-4*/

#include <stdlib.h>
#include <glut.h>
#include <stdio.h>


#define W 500
#define H 500
#define MagicalConstCRe  0,36
#define MagicalConstCIm  0,34

double Frame[H][W][3];

typedef struct {
	double Re, Im;
}  Complex;

Complex Mult(Complex A, Complex B)
{
	Complex Z;
	Z.Re = A.Re*A.Im - B.Re*B.Im;
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
	return A.Re*A.Re + A.Im*A.Im ;
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
	C.Re = MagicalConstCRe;
	C.Im = MagicalConstCIm;

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
			
			Poop.Re = col;
			Poop.Im = row;
			n = ComplIter(Poop);
			printf("%i", n);
			Frame[col][row][0] = (double)n;
			Frame[col][row][1] = (double)n / 2;
			Frame[col][row][2] = (double)n / 4;

		}

	}


}

void Display(void)
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

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
