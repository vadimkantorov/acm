#include "stdafx.h"
#include <iostream>
using namespace std;

void main()
{
	int n;
	cin>>n;
	int**raz = new int*[n];
	for(int i = 0; i < n; i++)
	{
		raz[i] = new int[n];
		for(int j = 0; j < n; j++)
			cin>>raz[i][j];
	}
	
	for(int i = 0; i < n; i++)
	{
		for(int k = i,x = 0; k >= 0 && x <= i ; x++, k--)
		{
			int b = raz[k][x];
			cout<<b<<" ";
		}
	}
	for(int i = 1; i<n; i++)
	{
		int x = i,y = n-1;
		for(int k = n-i; k > 0; k--)
		{
			int b = raz[y][x];
			cout<<b<<" ";
			y--;
			x++;
		}
	}
}