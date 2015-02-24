#include "stdafx.h"
#include <iostream>
#include <cstdio>
using namespace std;
int comp (const void *l,const void *r)
{
	if (*(int*)l>*(int*)r)
		return 1;
	if (*(int*)l<*(int*)r)
		return -1;
	return 0;
}
void main()
{
	int n;
	cin>>n;
	int* A = new int[n];
	for(int i = 0; i < n; i++)
		cin>>A[i];
	qsort((void*)A,n,sizeof(int),comp);
	for(int i = n-1; i >= 0; i--)
		cout<<A[i]<<endl;
}