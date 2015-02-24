#include <stdio.h>
#define MIN -10000000

int A[25005];

void main()
{
	int m;
	scanf("%d",&m);

	int n = 0;
	while(true)
	{
		scanf("%d",&A[n]);
		if(A[n] == -1)
			break;
		else
			n++;
	}
	
	int l = 0;
	int r = l + m;
	int max;
	while(r <= n)
	{
		max = MIN;
		for(int i = l; i < r; i++)
		{
			if(A[i] > max)
				max = A[i];
		}
		printf("%d\n",max);
		l++;
		r++;
	}
}