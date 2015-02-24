#include <cstdio>

void main()
{
	int n,b;
	scanf("%d%d",&n,&b);

	int on = 0;

	for(int i = 1; i <= n; i++)
	{
		int q = b*i/100;
		if(on+1 <= q+2)
		{
			on++;
			putchar('1');
		}
		else
			putchar('0');
	}
}