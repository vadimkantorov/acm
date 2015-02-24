#include <cstdio>
#include <algorithm>
using namespace std;

int TList[15020];

void main()
{
	int n,m, count = 0;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%d",&TList[i]);

	sort(TList, TList + n);

	scanf("%d",&m);
	for(int i = 0; i < m; i++)
	{
		int aux;
		scanf("%d",&aux);
		if(binary_search(TList, TList + n, aux))
			count++;
	}

	printf("%d",count);
}