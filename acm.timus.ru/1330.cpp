#include <stdio.h>
int sums[10002];
void main()
{
	int n;
	scanf("%d",&n);

	int tmp;
	for(int i = 1; i <= n; i++)
	{
		scanf("%d",&tmp);
		sums[i] = sums[i-1]+tmp;
	}
	
	int q;
	scanf("%d",&q);

	int k,l;
	for(int i = 0; i < q; i++)
	{
		scanf("%d %d",&k,&l);
		printf("%d\n",sums[l]-sums[k-1]);
	}
	
}
