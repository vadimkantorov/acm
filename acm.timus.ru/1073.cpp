#include <stdio.h>
#include <stdlib.h>
#define MAXVAL 1000000
int mas[250];
int count;

int matr[60002] = {0,1};

void go(int n)
{
	int min = MAXVAL;
	for(int i = 1; i <= count && mas[i] <= n; i++)
		if(matr[n-mas[i]]+1 < min)
			min = matr[n-mas[i]]+1;
	
	matr[n] = min; 
}

void main()
{
	int n;
	scanf("%d",&n);
	for(int i = 1; i*i <= n; i++,count++)
		mas[i] = i*i;
	for(int i = 2; i <= n ;i++)
		go(i);
	printf("%d",matr[n]);
}