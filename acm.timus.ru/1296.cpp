#include <iostream>
using namespace std;

void main()
{
	int max = 0, cur = 0, n,tmp;
	
	cin >> n;
	
	for(int i = 0; i < n; i++)
	{
		cin >> tmp;
		cur += tmp;
		if(cur < 0)
			cur = 0;
		if(cur > max)
			max = cur;
	}

	cout << max;
}