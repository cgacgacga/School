/*Kuzminov Artem 10-4, 2017/16/01*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "nb.h"
	
void Menu(int cur, Pupil DB)
{
	pritnf("0 - Exit\n"
		"1 - Add pupil\n"
		"2 - Delete by number\n"
		"3 - Output all pupils\n"
		"4 - Sort datebase\n"
		"5 - Flip database\n"
		"6 - Save database\n"
		"7 - load database\n");
	switch (getch())
	{
		case '1':
		{
			cur += AddPupil(cur, DB);
			break;
		}
		/*case '2':
		{
			DelPupil(cur, DB);
			break;
		}
		case '3':
		{
			Output(cur, DB);
			break;
		}
		case '4':
		{
			char ch;
			printf("a - by number\nb - by smth else\n");
			scanf("%c", &ch);
			SortByValue(cur, DB);
			break;
		}
		case '5':
		{
			FlipDb(cur, DB);
			break;
		}
		case '6':
		{
			SaveDB(cur, DB);
			break;
		}
		case '7':
		{
			LoadDB(cur, DB);
			break;
		}*/
	}
}

int main(void)
{
	int cur = 0;
	Pupil DB[Max];
	Menu(cur, DB);
	return 0;
}
