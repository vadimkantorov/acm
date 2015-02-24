#include <cstdio>

int c;

int pow(int a, int b)
{
	if(b == 0)
		return 1%c;
	if(b == 1)
		return a%c;
	int tmp = pow(a,b/2);
	return ( (tmp*tmp)%c*pow(a,b%2) )%c;
}

int main()
{
	int a,b;
	scanf("%d%d%d",&a,&b,&c);
	printf("%d",pow(a,b));
	return 0;
}