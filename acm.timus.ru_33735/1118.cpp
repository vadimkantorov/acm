#include <cstdio>
#include <cmath>

double Triviality(int x)
{
	int res = (x != 1)?1:0;
	int S = ceil(sqrt(double(x)));
	for(int i = 2; i*i <= x; i++)
	{
		if(x%i == 0)
		{
			res += i;
			if(i != S)
				res += x/i;
		}
	}
	return double(res)/x;
}

bool IsPrime(int x)
{
	if((x == 2) || (x%2 == 0))
		return (x == 2);
	for(int i = 3; i*i <= x; i += 2)
		if(x%i == 0)
			return false;
	return (x != 1);
}

void main()
{
	int a,b;
	scanf("%d%d",&a,&b);
	if(a != 1)
	{
		double min = 1000000000;
		int mini;
		for(int i = b; i >= a; i--)
		{
			if(IsPrime(i))
			{
				printf("%d",i);
				return;
			}
			double tmp = Triviality(i);
			if(tmp < min)
			{
				min = tmp;
				mini = i;
			}
		}
		printf("%d",mini);
	}
	else
		puts("1");
}