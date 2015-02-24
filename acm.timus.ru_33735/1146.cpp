#include <cstdio>
#define N 100

int B[N+1][N+1];

void main()
{
	int n,tmp;
	scanf("%d",&n);
	
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			scanf("%d",&tmp);
			B[i][j] = tmp + B[i-1][j] + B[i][j-1] - B[i-1][j-1];
		}
	}
	int max = -1000000000;
	for(int x1 = 1; x1 <= n; x1++)
	{
		for(int y1 = 1; y1 <= n; y1++)
		{
			for(int x2 = x1; x2 <= n; x2++)
			{
				for(int y2 = y1; y2 <= n; y2++)
				{
					tmp = B[x2][y2]-B[x1-1][y2]-B[x2][y1-1]+B[x1-1][y1-1];
					if(tmp > max)
						max = tmp;
				}
			}
		}
	}
	printf("%d",max);
}