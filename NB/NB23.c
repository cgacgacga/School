/*Kuzminov Artem 10-4, 2017/16/01*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "nb.h"

#define Max 50

void GetStr1(char *name, int n)
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

int Menu(int cur, Pupil *DB)
{
	char num[22];
	int ch = 0;
	printf("0 - Exit\n1 - Add pupil\n2 - Delete by number\n3 - Output all pupils\n4 - Sort datebase\n5 - Flip database\n6 - Save database\n7 - load database\n");
	switch (getch())
	{
	case '0':
		return 2;
	case '1':
		ch = AddPupil(cur, DB);
		if (ch == 1)
			printf("Failed to add a pupil");
		return 1;
	case '2':
		GetStr1(num, 22);
		ch = DeleteByNumber(cur, DB, num);
		if (ch == 1)
			printf("Failed to delete a pupil");
		return -1;
	case '3':
		ch = Output(cur, DB);
		if (ch == 1)
			printf("Failed to output");
		return 0;
	/*case '4':
		break;
	case '5':
		break;
	case '6':
		break;
	case '7':
		break;
	*/
	}
}

int main(void)
{
	int cur = 0,c = 1;
	Pupil DB[50];
	while (!(c == 2))
	{
		c = Menu(cur, DB);
		cur += c;
		printf("%i", cur);
	}
	return 0;
}
