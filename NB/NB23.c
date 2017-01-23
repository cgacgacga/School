/*Kuzminov Artem 10-4, 2017/16/01*/

#include <stdio.h>
#include <stdlib.h>
#include "nb.h"

#define Max 50

int Menu( int cur, Pupil *DB )
{
  printf("0 - Exit\n1 - Add pupil\n2 - Delete by number\n3 - Output all pupils\n4 - Sort datebase\n5 - Flip database\n6 - Save database\n7 - load database\n");
  switch(getch())
  {
  case '0':
    return 0;
  case '1':
    AddPupil(cur, DB);
    break;
  case '2':
    break;
  case '3':                      
    break;
  case '4':
    break;
  case '5':
    break;
  case '6':
    break;
  case '7':
    break;
  }
}

int main( void )
{
  int cur = 0;
  Pupil DB[50];
  while (Menu(cur, DB))
    cur += Menu(cur, DB);
  return 0;
}
