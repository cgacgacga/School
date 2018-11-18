/*Kuzminov Artem, 10-4, 10.04.17 */
#define FRAME_W 1024
#define FRAME_H 768

unsigned char FRAME[FRAME_H][FRAME_W][3];
typedef unsigned char byte;
typedef byte RGB[3];


typedef struct
{
  int W, H;
  RGB *PIXELS;
} IMG;

int ImageLoad( IMG*P, char*FileName );
void ImageDraw ( IMG *P, int x0, int y0 );
void ImageDrawAuto ( IMG *P );
int ImageCreate ( IMG *P, int NewW, int NewH );
void ImageFree ( IMG *P );
void Negative ( IMG *Src, IMG *Dst );


typedef byte LUT[256];

void LUTSetCopy ( byte *LUT );
void LUTSetNegative ( byte *LUT );
void LUTSetBrightness ( byte *LUT, int Di );
void LUTSetContrast ( byte *LUT, int A, int B );
void LUTSetGamma ( byte *LUT, double Gamma );
void LUTSetPoster ( byte *LUT, int Levels );
void LUTSetAutoContrast ( byte *LUT, IMG *P );
void LUTApply ( IMG *Dst, IMG *Src, byte *LUT ); 

void Blur ( IMG *Src, IMG *Dest );
