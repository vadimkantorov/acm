#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;
const double PI = 3.14159265359;
struct point
{
public:
	double x,y;
};
double Dist(point p1, point p2)
{
	return sqrt( (double)((p2.x-p1.x)*(p2.x-p1.x) +(p2.y-p1.y)*(p2.y-p1.y)) );
}
void main()
{
	int n;
	double r, d =0;
	point p;
	cin>>n>>r;
	point* ps = new point[n];
	for(int i = 0; i<n;i++)
		cin>>ps[i].x>>ps[i].y;
	for(int i = 1; i<n;i++)
		d += Dist(ps[i-1],ps[i]);
	d+=Dist(ps[n-1],ps[0])+2*r*PI;
	printf("%.2f",d);
}