#include "stdafx.h"
#include <iostream>
using namespace std;
void main()
{
	int n;
	cin>>n;
	unsigned* A = new unsigned[n];

	int ni,id;
	for(int i = 0; i < n; i++)
	{
		cin>>id>>ni;
		A[i] = id*101+ni;
	}
	for(int i = 100; i >= 0; i--)
		for(int j = 0; j < n; j++)
			if(A[j]%101==i)
				cout<<(A[j]-A[j]%101)/101<<" "<<A[j]%101<<endl;
}