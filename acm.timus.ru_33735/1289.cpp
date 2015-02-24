#include "stdafx.h"
#include <iostream>
using namespace std;
void main()
{
	int n;
	cin>>n;
	int digs = n/2;
	if(n == 2)
	{
		cout<<10;
		return;
	}
	for(int i = 0;i<digs-1;i++)
		cout<<1;
	cout<<0;
	for(int i = 0;i<digs-2;i++)
		cout<<8;
	cout<<90;
}