#include <cstdio>
#include <cmath>

int getmod(int x, int n, int m)
{
	int tmp = x%m;
	int mod = 1;
	for(int i = 0; i < n; i++)
		mod = (tmp*mod)%m;
	return mod;
}

void main()
{
	int n,m,y;
	scanf("%d%d%d",&n, &m, &y);
	bool found = false;
	
	for(int x = 0; x <= m-1; x++)
	{
		if(getmod(x,n,m) == y)
		{
			printf("%d ",x);
			found = true;
		}
	}
	
	if(!found) puts("-1");
}