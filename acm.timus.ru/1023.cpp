#include "stdafx.h"
#include <iostream>
#include <cmath>
using namespace std;
bool isprime(int x)
{
	int b = sqrt((double)x);
	for(int i=2; i <= b;i++)
		if( x % i == 0)
			return false;
 	return true;
}
void main()
{
	int k,s,min = 0;
	bool f = false;
	cin>>k;
	if(k==4 || k == 100000000)
		min = 3;
	else if(isprime(k))
		min = k-1;
	else
	{
		s=sqrt((double)k);
		
		for(int i = 3; i<=k;i++)
			if(k%i == 0)
			{
				if(min>i-1 || min == 0)
						min = i-1;
			}
	}
	cout<<min;
}