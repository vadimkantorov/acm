#include "stdafx.h"
#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;
const double PI=3.14159265358979323846;
void main()
{
	double a,r,res;
	//scanf("%f%f",&l, &r);
	cin>>a>>r;
	if(r <= a/2)
		res = PI*r*r;
	else if(2*r >= a*sqrt((double)2))
		res = a*a;
	else
	{
		double alpha = PI/2-2*acos(a/(2*r));//������� ����
		res = 2*a*sqrt((double)(r*r-a*a/4));//��������� ������� ������ �������������
		res += 2*alpha*r*r;//��������� ������� ������ ��������
	}
	printf("%.3f",res);
}
