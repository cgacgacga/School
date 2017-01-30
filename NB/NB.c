/* Kuzminov Artem, 10-4, 23/01/2017 */
//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "nb.h"

void Swap(Pupil *a, Pupil *b )
{
  Pupil tmp = *a;
  *a = *b;
  *b = tmp;
}

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
		return 1;
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
		printf("Please input FormDigit\n");
		scanf("%c", &DB[cur].FormDigit);
		scanf("%c", &bin);
		return 0;
	}
}

int DeleteByNumber(int cur, Pupil *DB, char *Num)
{
	if (cur > 49 || cur == 0)
		return 1;
	else
	{
		int i;
		for (i = 0; i < cur; i++)
			if (DB[i].Number == Num)
				break;
		
		for (; i < cur; i++)
		{
			DB[i].Birthday = DB[i + 1].Birthday;
			*DB[i].Surname = *DB[i + 1].Surname;
			*DB[i].Name = *DB[i + 1].Name;
			*DB[i].Number = *DB[i + 1].Number;
			DB[i].Age = DB[i + 1].Age;
			DB[i].Form = DB[i + 1].Form;
			DB[i].Sex = DB[i + 1].Sex;
			DB[i].FormDigit = DB[i + 1].FormDigit;
		}
		return 0;
	}
}

int Output(int cur, Pupil *DB)
{
	int i,j;
	for (i = 0; i < cur; i++)
	{
		printf("Surname:");
		for (j = 0; j < 30; j++)
			printf("%c", DB[i].Surname[j]);
		printf("\n");
		printf("Name:");
		for (j = 0; j < 30; j++)
			printf("%c", DB[i].Name[j]);
		printf("\n");
		printf("Number:");
		for (j = 0; j < 22; j++)
			printf("%c", DB[i].Number[j]);
		printf("\n");
		printf("Birthday:%i/%i/%i\nAge:%i\nForm:%i\nForm digit:%c\nSex:%c\n", DB[i].Birthday.Day, DB[i].Birthday.Month, DB[i].Birthday.Year, DB[i].Age, DB[i].Form, DB[i].FormDigit, DB[i].Sex);
	}
	return 0;
}


int Cmp(Pupil *A, Pupil *B, char a){
  if (a == 'a')
  { 
    int ag1 = A->Birthday.Year * 12 * 31 + A->Birthday.Month * 31 + A->Birthday.Day,
    ag2 = B->Birthday.Year * 12 * 31 + B->Birthday.Month * 31 + B->Birthday.Day;
    if (ag1 > ag2)
      return 1;
    else return 0;
  }
  if (a == 'b')
  {
     int res = strcmp(A->Surname, B->Surname);
     if (res < 0)
       return 0;
     else
       return 1;
  }
  return 0;
}


void SortBy(int cur, Pupil *DB, char adj)
{
  int i, j;
  for (i = 0; i < cur; i++)
    for(j = 0; j < cur; j++)
      if (Cmp(&DB[j], &DB[j+1], adj))
        Swap(&DB[j], &DB[j+1]);

}
