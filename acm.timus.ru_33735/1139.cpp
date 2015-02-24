#include <cstdio>

int GCD(int a, int b)
{
	int c;
	while((c=a%b) != 0)
	{
		a = b;
		b = c;
	}
	return b;
}

void main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	n--; m--;
	int k = GCD(n,m);
	printf("%d",(m/k + n/k-1)*k);
}