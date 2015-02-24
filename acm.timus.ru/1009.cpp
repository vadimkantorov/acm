#include <stdio.h>

void main()
{
	int n,k;
	scanf("%d %d", &n, &k);
	int a = 1;
	int b = k-1;
	int c;
	for(int i = 2; i <= n; i++)
	{
		c = (a+b)*(k-1);
		a = b;
		b = c;
	}
	printf("%d",b);
}