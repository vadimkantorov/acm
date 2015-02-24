#include <cstdio>

void main()
{
	int a,b;
	scanf("%d%d",&a,&b);
	int days = b-a+1;
	printf("%d",(days + (a%2 == 1))/2);
}