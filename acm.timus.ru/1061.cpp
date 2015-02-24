#include <cstdio>
#define N 100005

int bs[N], sum[N];

void main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	
	int n,k;
	scanf("%d%d\n",&n,&k);
	for(int i = 0; i < n; i++)
	{
		bs[i] = getchar()-'0';
		if(bs[i] == '*'-'0')
			bs[i] = 1e+6;

		if((i+1)%80 == 0)
			getchar();
	}

	for(int i = 1; i <= n; i++)
		sum[i] = sum[i-1] + bs[i-1];

	int l = 0;
	for(int i = k; i <= n; i++)
	{
		if(sum[i] - sum[i-k] < 1e+6)
		{
			if(l == 0 || (sum[i] - sum[i-k] < sum[l] - sum[l-k]))
				l = i;
		}
	}
	if(l == 0)
		puts("0");
	else
		printf("%d",l-k+1);
}