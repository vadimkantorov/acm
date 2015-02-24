#include <cstdio>
#include <cmath>

void main()
{
	int n;
	scanf("%d",&n);
	int tmp = (abs(n)*(abs(n)+1))/2;
	if(n > 0)
		printf("%d",tmp);
	else
		printf("%d",-tmp + 1);
}