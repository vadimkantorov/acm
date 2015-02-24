#include "stdafx.h"
#include <iostream>
#include <cstdlib>
using namespace std;
int comp(const void* l, const void* r)
{
	if(*((int*)l)>*((int*)r))
		return 1;
	if(*((int*)l)<*((int*)r))
		return -1;
	return 0;
}
void main()
{
	int n,sum=0,t;
	cin>>n;
	int* IZ = new int[n];
	for(int i=0;i<n;i++)
		cin>>IZ[i];
	qsort((void*)IZ,n,sizeof(int),*comp);
	for(int i=0;i<n/2+1;i++)
		sum+=IZ[i]/2+1;
	cout<<sum;
}