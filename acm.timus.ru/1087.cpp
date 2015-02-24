#include "stdafx.h"
#include <iostream>
using namespace std;
void main()
{
	int n,m;
	cin>>n>>m;
	int* K = new int[m];
	bool* A = new bool[n];
	for(int i = 0;i<m;i++)
		cin>>K[i];
	for(int i = 0; i < n; i++)
		A[i]=false;
    for(int i = 0; i < n; i++)
		if(!A[i])
			for(int j = 0; j < m; j++)
				if(i+K[j]<n)
					A[i+K[j]] = true;
	if(A[n-1])
		cout<<1;
	else
		cout<<2;
}