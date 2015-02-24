#include "stdafx.h"
#include <iostream>
using namespace std;
int A[8][8];
bool ok(int i, int j)
{
	return (i>=0 && i<=7 && j>=0 && j<=7);
}
bool process(int i,int j)
{
	int an = (A[i][j] == 1)?2:1;
	if(ok(i-2, j+2) && ok(i-1, j+1))
	{
		if(A[i-1][j+1] == an && A[i-2][j+2] == 0)
			return true;
	}
	if(ok(i-2, j-2) && ok(i-1, j-1))
	{
		if(A[i-1][j-1] == an && A[i-2][j-2] == 0)
			return true;
	}
	if(ok(i+2, j+2) && ok(i+1, j+1))
	{
		if(A[i+1][j+1] == an && A[i+2][j+2] == 0)
			return true;
	}
	if(ok(i+2, j-2) && ok(i+1, j-1))
	{
		if(A[i+1][j-1] == an && A[i+2][j-2] == 0)
			return true;
	}
	/////
	if(ok(i-1, j+1)&& ok(i+1,j-1))
	{
		if(A[i-1][j+1] == an && A[i+1][j-1] == 0)
			return true;
	}
	if(ok(i-1, j-1) && ok(i+1,j+1))
	{
		if(A[i-1][j-1] == an && A[i+1][j+1] == 0)
			return true;
	}
	if(ok(i+1, j+1) && ok(i-1,j-1))
	{
		if(A[i+1][j+1] == an && A[i-1][j-1] == 0)
			return true;
	}
	if(ok(i+1, j-1) && ok(i-1,j+1))
	{
		if(A[i+1][j-1] == an && A[i-1][j+1] == 0)
			return true;
	}
	return false;
}
void main()
{
	char c;
	int a,b;

	for(int i = 1; i <= 32; i++)
	{
		cin>>c>>b;
		switch(c)
		{
		case 'a':
			a = 0;
			break;
		case 'b':
			a = 1;
			break;
		case 'c':
			a = 2;
			break;
		case 'd':
			a = 3;
			break;
		case 'e':
			a = 4;
			break;
		case 'f':
			a = 5;
			break;
		case 'g':
			a = 6;
			break;
		case 'h':
			a = 7;
			break;
		}
		if( i % 2 == 1)
			A[a][b-1] = 1;
		else
			A[a][b-1] = 2;
		if(process(a,b-1))
		{
			cout<<i;
			return;
		}
	}
	cout<<"Draw";
}