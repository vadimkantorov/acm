#include <cstdio>

int D[1002];

void main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 0; i < n; i++)
		scanf("%d",&D[i]);
	
	for(int i = m%n; i < m%n + 10; i++)
		printf("%d",D[i%n]);
}