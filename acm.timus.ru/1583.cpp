#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

const int N = 105;
const double PI = 3.1415926535897932384626433832795;

int n;
double X[N], Y[N], Z[N], R[N];
vector<int> res;

bool LtV(double a, double b)
{
	double EPS = 1e-10;
	return a + EPS < b;
}

bool EqX(double a, double b)
{
	double EPS = 1e-10;
	return abs(a-b) < EPS;
}

bool LtX(double a, double b)
{
	double EPS = 1e-10;
	return a + EPS < b;
}

double Cube(double x)
{
	return x*x*x;
}

double Sqr(double x)
{
	return x*x;
}

double cm2mm(double cm)
{
	return cm*(1e+4);
}

double mm2cm(double mm)
{
	return mm/(1e+4);
}

double Volume(double x)
{
	double res = 10*10*x;
	
	for(int i = 0; i < n; i++)
	{
		if(LtX(X[i] + R[i], x))//LT R
			res -= 4.0*PI*Cube(R[i])/3;
		else if(LtX(X[i] - R[i], x) && LtX(x,X[i] + R[i]))//LT R
		{
			double h = x - X[i];
			res -= PI*(R[i]*Sqr(R[i]+h) - Cube(R[i] + h)/3.0);
		}
	}
	
	return res;
}

int Cut(double beg)
{
	beg = mm2cm(beg);
	double l = beg, r = 100;
	double vol = Volume(r) - Volume(l);
	
	if(LtV(vol, 500))
		return -1;

	while(LtX(l,r))// LT R
	{
		double mid = (l + r) / 2;
		vol = Volume(mid) - Volume(beg);
		if(LtV(vol,500))
			l = mid;
		else
			r = mid;
	}

	return floor(cm2mm(l)+.5);
}

void main()
{
	scanf("%d",&n);

	for(int i = 0; i < n; i++)
		scanf("%lf%lf%lf%lf",&Y[i],&X[i],&Z[i],&R[i]);

	int x = 0;
	while( (x = Cut(x)) > 0 )
	{
		if(!EqX(x,cm2mm(100)))
			res.push_back(x);
	}

	printf("%d\n",res.size());
	for(int i = 0; i < res.size(); i++)
		printf("%d\n",res[i]);
}