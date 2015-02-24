#include <cstdio>
#include <cmath>

int A[22], inds[22];
int ds = 1000000000;
int n;

void bf(int i)
{
	if(i == n-1)
	{
		int sum1 = 0, sum2 = 0;
		for(int i = 0; i < 20; i++)
		{
			if(inds[i])
				sum1 += A[i];
			else
				sum2 += A[i];
		}
		if(abs(sum1-sum2) < ds)
			ds = abs(sum1-sum2);
	}
	else for(inds[i] = 0; inds[i] < 2; inds[i]++)
		bf(i+1);
}

void main()
{
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%d",&A[i]);
	bf(0);
	printf("%d",ds);
}