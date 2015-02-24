#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

double SQR(double x)
{
	return x*x;
}

double a,b,c;

double f(double x)
{
	return (a*SQR(x) + b*x + c)/(1 + SQR(x));
}

void main()
{
	int a1,a2,b1,b2;
	scanf("%d%d%d%d",&a1,&b1,&a2,&b2);

	c = SQR(a1) + SQR(a2);
	a = SQR(b1) + SQR(b2);
	b = (double(a1)*b1 + double(a2)*b2)*2;

	double res = 0;
	double v2 = (a-c+sqrt(SQR(a-c)+SQR(b)))/b;

	res = max(f(0), max(f(1e+18),f(v2)));  // we are lucky.  0 > -1.IND00000

	printf("%.10lf",sqrt(res));
}