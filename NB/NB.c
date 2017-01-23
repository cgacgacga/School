/* Kuzminov Artem, 10-4, 23/01/2017 */

#include <stdio.h>
#include <string.h>
#include "nb.h"



void GetStr(char *name, int n)
{
  int i;
  for (i = 0; i < n; i++)
    name[i] = 0;
  for (i = 0; i< n; i++)
  {
    scanf("%c", &name[i]);
    if (name[i] == '\n')
    {
      name[i] = 0;
      break;
    }
  }
  
  
}

int AddPupil(int cur, Pupil *DB)
{
  
  if (cur == Max - 1)
    return 0;
  else
  {
    char bin = 'c';
    printf("Please input Birthday\n");
    scanf("%i %i %i", &DB[cur].Birthday.Day, &DB[cur].Birthday.Month, &DB[cur].Birthday.Year);
    scanf("%c", &bin);

    printf("Please input Surname\n");
    GetStr(DB[cur].Surname, 30);

    printf("Please input Name\n");
    GetStr(DB[cur].Name, 30);   
    
    printf("Please input Number\n");
    GetStr(DB[cur].Number, 22);  

    printf("Please input Age\n");
    scanf("%i", &DB[cur].Age);
    scanf("%c", &bin);
    printf("Please input Sex\n");
    scanf("%c", &DB[cur].Sex);
    scanf("%c", &bin);
    printf("Please input Form\n");
    scanf("%i", &DB[cur].Form);  
    scanf("%c", &bin);    
    printf("Please input FomDigit\n");
    scanf("%c", &DB[cur].FormDigit);
    scanf("%c", &bin);    
    return 1;
  }
}

int DeleteByNumber(int cur, Pupil *DB, char *Num)
{
  int i;
  for (i = 0; i < cur; i++) 
    if(DB[i].Number == Num)
    {
      i = savei;
      break;
    }
    if (i == cur - 1)
    {
      printf("Failed");
      return 0;
    }
  for (i = savei; i < cur; i++)
  {

  }
}
