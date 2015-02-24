#include <iostream>
using namespace std;

void main()
{
	int n,k = 0;
	char c;
	cin >> n;
	cin.get();
	while(true)
	{
		c = cin.get();
		if(c == '!')
		{
			k++;
		}
		else
			break;
	}
	int res = n;
	for(int i = 1; n - (i+1)*k > 0; i++)
	{
		res*= n-i*k;
	}
	if(n > k)
	{
		if(n % k == 0)
		{
			res *= k;
		}
		else
		{
			res *= n%k;
		}
	}
	cout << res;
}