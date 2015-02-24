#include <cstdio>
#include <cmath>

void main()
{
	int n;
	scanf("%d",&n);

	for(int p = (1+sqrt(1+8.0*n))/2.0; p >= 1; p--)
	{
		int num = 2*n+p*(1-p);
		if(num != 0 && num%(2*p) == 0)
		{
			printf("%d %d",num/(2*p),p);
			break;
		}
	}
}