#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void main()
{
	vector<int> mn;
	int n,l;
	cin>>n;
	if(n==0)
	{
		cout<<10;
		return;
	}
	if(n==1)
	{
		cout<<1;
		return;
	}
	for(int i = 9;i>1;i--)
		while(n%i==0)
		{
			n/=i;
			mn.push_back(i);
		}
	if(n != 1)
	{
		cout<<-1;
		return;
	}
	sort(mn.begin(), mn.end());
	l = mn.size();
	for(int i = 0; i<l;i++)
		cout<<mn[i];
}