#include "stdafx.h"
#include <iostream>
#include <cstdio>
using namespace std;
struct bomb
{
	double x,y,r;
};
void main()
{
	int n,num=0;
	cin>>n;
	bomb* A = new bomb[n];
	for(int i = 0; i < n; i++)
		cin>>A[i].x>>A[i].y>>A[i].r;
	for(double i = 0.000; i <=1;i+= 0.001)
		for(double j = 0.000; j <= 1; j+= 0.001)
			for(int k = 0; k < n; k++)
				if((A[k].x-i)*(A[k].x-i) + (A[k].y-j)*(A[k].y-j) <= A[k].r*A[k].r)
				{
					num++;
					break;
				}
	printf("%.5f%",num/10000.);
}