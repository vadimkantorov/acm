#include "stdafx.h"
#include <iostream>
#include <cstdio>
using namespace std;
void main()
{
	int n,m,k;
	cin>>n>>m;
	int can[10000]={0};
	for(int i =0;i<m;i++)
	{
		cin>>k;
		can[k-1]++;
	}
	for(int i =0;i<n;i++)
	{
		printf("%.2f",((double)can[i]/(double)m)*100);
		cout<<"%"<<endl;
	}
}