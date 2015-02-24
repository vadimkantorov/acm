#include <cstdio>

bool A[70000], B[70000];
const int shift = 33000;

void main()
{
	//freopen("input.txt","r",stdin);

	int n,m;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
	{
		int t;
		scanf("%d",&t);
		A[t + shift] = true;
	}
	scanf("%d",&m);
	for(int i = 0; i < m; i++)
	{
		int t;
		scanf("%d",&t);
		B[t + shift] = true;
	}

	for(int i = -32768; i <= 32767; i++)
	{
		if(10000-i <= 32767 && 
			((A[i+shift] && B[10000-i+shift]) ||
			(B[i+shift] && A[10000-i+shift])))
		{
			puts("YES");
			return;
		}
	}
	puts("NO");
}