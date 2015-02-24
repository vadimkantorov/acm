#include <cstdio>
#include <algorithm>
#define N 10002
using namespace std;

int M[N];

void main()
{
	int n,s, Max = 1;
	scanf("%d%d",&n,&s);
	
	M[s] = 1;
	for(int i = s; i <= n; i++)
	{
		if(M[i] != 0)
		{
			for(int j = 1; j <= 100; j++)
				if(i*j % 100 == 0)
				{
					int k = i+i*j/100;
					if(k > i && k <= n)
					{
						M[k] = max(M[k],M[i]+1);
						Max = max(M[k],Max);
					}
				}
		}
	}
	printf("%d",Max);
}