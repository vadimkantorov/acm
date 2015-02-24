#include <cstdio>
#include <algorithm>
#define N 2000005
using namespace std;

int rems[N];

void main()
{
	fill_n(rems,N,-1);
	
	int k,p;
	scanf("%d%d",&k,&p);
	
	for(__int64 i = 0; i < p; i++)
		rems[(i*i)%p] = i;

	for(int i = 0; i <= k+p; i++)
	{
		if(rems[i] != -1)
		{
			if(k >= i && rems[k-i] != -1)
			{
				printf("%d %d",rems[i],rems[k-i]);
				return;
			}
			if(rems[k+p-i] != -1)
			{
				printf("%d %d",rems[i],rems[k+p-i]);
				return;
			}
		}
	}
	puts("NO SOLUTION");
}