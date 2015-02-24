#include "stdafx.h"
#include <iostream>
using namespace std;
int a[100000]={-1};
void main()
{
	a[0] = 0;
	a[1] = 1;
	for(int i = 2; i < 100000; i++)
	{
		if(i%2==0)
			a[i] = a[i/2];
		else
			a[i] = a[(i-1)/2]+a[(i-1)/2+1];
	}
	
    int n, max =0;
	while(true)
	{
		cin>>n;
		if (n==0)
			break;
		for(int i=0;i<=n;i++)
		{
			if(a[i]>max)
				max = a[i];
		}
		cout<<max<<endl;
	}
}