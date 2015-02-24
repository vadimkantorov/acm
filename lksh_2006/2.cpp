#include <cstdio>

int X[102];

int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
		scanf("%d",&X[i]);

	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			for(int k = 0; k < n; k++)
				if(X[i]*X[j] == X[k])
				{
					printf("%d %d %d",X[i],X[j],X[k]);
					return 0;
				}
	puts("0 0 0");
	return 0;
}