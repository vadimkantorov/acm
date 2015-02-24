#include <iostream>
using namespace std;
int A[10001];
bool isprime(int x)
{
	if(x == 1)
		return false;
	for(int i = 2; i*i <= x; i++)
		if(x % i == 0)
			return false;
	return true;
}
void fill(int n)
{
	while( n % 2 == 0)
	{
		n /= 2;
		A[2]++;
	}
	for(int i = 3; i <= n; i+=2)
	{
		if(isprime(i))
		{
			while( n % i == 0)
			{
				n /= i;
				A[i]++;
			}
		}
	}
	/*
	for(int i = 2; i <= n; i++)
	{
		if(isprime(i))
		{
			while( n % i == 0)
			{
				n /= i;
				A[i]++;
			}
		}
	}
	*/
}
void main()
{
	int tmp;
	for(int i = 0; i < 10; i++)
	{
		cin >> tmp;
		fill(tmp);
	}
	int res = 1;
	for(int i = 1; i <= 10000; i++)
	{
		res *= A[i]+1;
	}
	res %= 10;
	cout << res;
}