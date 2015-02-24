#include "stdafx.h"
#include <iostream>
using namespace std;
int ** raz;
int n;
void print()
{
	int j;
	for(int i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			cout<<raz[i][j]<<" ";
			cout<<endl;
	}
			
}
void main()
{
	int x,y,t=1,j;
	cin>>n;
	raz = new int*[n];
	for(int i = 0; i < n; i++)
	{
		raz[i] = new int[n];
		for(j = 0; j < n; j++)
			raz[i][j] = 0;
	}
	for(int i = n-1; i >= 0; i--)
	{
		x = i;
		y = 0;
 		for(int k = 0; k < n-i; k++, t++, x++, y++)
		{
			raz[y][x] = t;
		}
	}
	for(int i = 1; i < n; i++)
	{
		x = 0;
		y = i;
		for(int k = 0; k < n-i; k++, t++, x++, y++)
		{
			raz[y][x] = t;
		}
	}
	print();
}