#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
int comp(const void* l, const void* r)
{
	if(*((int*)l)>*((int*)r))
		return 1;
	if( *((int*)l)<*((int*)r) )
		return -1;
	return 0;
}
void main()
{
	int n,m;
	string s;
	cin>>n;
	int * N = new int[n];
	for(int i =0;i<n;i++)
		cin>>N[i];
	qsort((void*)N,n,sizeof(int),comp);
	cin>>s;
	cin>>n;
	for(int i =0;i<n;i++)
	{
		cin>>m;
		cout<<N[m-1]<<endl;
	}
}