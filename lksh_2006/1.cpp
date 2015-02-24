#include <cstdio>

int DivisorsSum(int x)
{
	int sum = 0;
	for(int i = 1; i*i <= x; i++)
	{
		if(x%i == 0)
		{
			sum += i;
			if(i != x/i)
				sum += x/i;
		}
	}
	return sum;
}

int main()
{
	int n, maxd = 0,maxi;
	scanf("%d",&n);
	
	for(int i = 1; i <= n; i++)
	{
		int tmp = DivisorsSum(i);
		if(tmp > maxd)
		{
			maxd = tmp;
			maxi = i;
		}
	}

	printf("%d",maxi);
	return 0;
}