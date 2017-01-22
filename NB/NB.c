/*Kuzminov Artem 10-4, 2017/16/01*/

#include "NB.h"

int AddPupil(int cur, Pupil DB)
{
	if (cur == Max - 1)
		printf("Failed, your notebook is filled");
		return 0;
	{
		int i;
		printf("Please enter number");
		for (i = 0; i < 30; i++)
			readf("%c", &DB[cur].number[i]);
		printf("Please enter class");
		readf("%i", &DB[cur].class);
		printf("Please enter sex");
		readf("%i", &DB[cur].sex);
		printf("%m");
		return 1;
	}
}
