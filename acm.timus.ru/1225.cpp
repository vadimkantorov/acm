#include <stdio.h>

void main()
{
	int n;
	scanf("%d",&n);
	unsigned long long int a = 2;
	unsigned long long int b = 2;
	unsigned long long int c;
	for(int i = 3; i <= n; i++)
	{
		c = a + b;
		a = b;
		b = c;
	}
	printf("%I64u",b);
}