#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


int loading[10];

int IsPrime(int a) 
{
	if (a == 0)
		return 0;
	else
	{
		int i;
		for (i = 2; i*i <= a; i++)
			if (a % i == 0)
				return 0;
			else
				a = a;
		return 1;
	}
}

int FirstZeroIndex(int *a, int n )
{
	int i;
	for (i = 0; i < n; i++)
		if (a[i] == 0)
			return i;
	return -1;
}

void loadingMenu(int *a, int place, int n)
{
	
	int i = 0;
	int p = (int)(place * 10 / n);
	
	system("cls");
	for (i = 0; i < p; i++)
		printf("#");
	printf("\n");
}

void Swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void SuperSort(int *a, int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - 1; j++)
			if (a[j] == 0)
				Swap(&a[j], &a[j + 1]);
}

void Compress(int *a, int place, int n)
{
	int i;
	for (i = place; i < n; i++)
		if (!IsPrime(a[i]))
			a[i] = 0;
}

int FillUp(int *a, int place, int curn, int n) {
	int i;
	for (i = place; i < n; i++)
		a[i] = curn++;
	return curn;
}

int main(void)
{
	int n = 10, place = 0, curn = 2, i =0;
	int *a;

	FILE *F;
	F = fopen("output.txt", "w");
	
	scanf("%i", &n);
	a = malloc(n * 4);
	a[n - 1] = 0;
	printf("loading\n");
	while(!IsPrime(a[n - 1]))
	{
		int prev = 0;
		curn = FillUp(a, place, curn, n);

		Compress(a, place, n);

		if ((int)(place * 10 / n) > prev)
			loadingMenu(a,place,n);

		SuperSort(a, n);
		
		prev = (int)(place * 10 / n);
	
		place = FirstZeroIndex(a, n);

	}
	system("cls");
	printf("########## - Done\n");

	for (i = 0; i < n; i++)
		fprintf(F, "%5d ", a[i]);

	scanf("%d", &place);

	free(a);

	return 0;
}
