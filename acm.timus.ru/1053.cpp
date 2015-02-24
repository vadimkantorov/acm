#include "stdafx.h"
#include <iostream>
using namespace std;
int NOD(int a,int b)
{
	int c;
	while((c=a%b) != 0)
	{
		a = b;
		b = c;
	}
	return b;
}

void main()
{
	int n,x,t;
	cin >>n;
	cin >>x;
	for(int i = 1; i < n; i++)
	{
		cin>>t;
		x = NOD(x,t);
	}
	cout<<x;
}