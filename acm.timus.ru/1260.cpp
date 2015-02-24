#include <cstdio>

unsigned long long int f(int n)
{
	switch(n)
	{
	case 1:
	case 2:
		return 1;
	case 3:
		return 2;
	case 4:
		return 4;
	default:
		int x = 1,y = 1,z = 1,t = 0,p = 1;
		int X,Y,Z,T,P;
		for(int i = 5; i <= n; i++)
		{
			X = x + y;
			Y = p;
			Z = t + p;
			T = z;
			P = x;
			
			x = X;
			y = Y;
			z = Z;
			t = T;
			p = P;
		}
		return x + y + z + t + p;
	}
}

void main()
{
	int n;
	scanf("%d",&n);
	printf("%I64u",f(n));
}