#include <cstdio>
#include <cmath>

const double EPS = 1e-7;
const double PI = 3.1415926535897932384626433832795;
const int D = 8;

double SQR(double x)
{
	return x*x;
}

double EQ(double x, double y) {return fabs((y) - (x)) <= EPS;}
double LT(double x, double y) {return ((y) - (x)) > EPS;}
double GT(double x, double y) {return LT(y,x);}
double LE(double x, double y) {return LT(x,y) || EQ(x,y);}
double GE(double x, double y) {return LE(y,x);}



double acos1(double x)
{
	if(x > 1)
		return 0;
	if(x < -1)
		return PI;
	return acos(x);
}

double sqrt1(double x)
{
	if(x < 0)
		return 0;
	return sqrt(x);
}

struct Point
{
	double C[D];

	Point() {}
	
	void Scan()
	{
		for(int i = 0; i < D; i++)
			scanf("%lf",&C[i]);
	}

	double Length()
	{
		double sqsum = 0;
		for(int i = 0; i < D; i++)
			sqsum += SQR(C[i]);
		return sqrt1(sqsum);
	}

	double DistanceTo(Point& x)
	{
		return (x - *this).Length();
	}

	Point operator-(Point& x)
	{
		Point p = *this;
		for(int i = 0; i < D; i++)
			p.C[i] -= x.C[i];
		return p;
	}

	double operator*(Point& x)
	{
		double res = 0;
		for(int i = 0; i < D; i++)
			res += C[i]*x.C[i];
		return res;
	}

	double operator^(Point& x)
	{
		return acos1(((*this)*x)/(Length()*x.Length()));
	}
};

double TriangleArea(Point A, Point B, Point C)
{
	double a = A.DistanceTo(B);
	double b = B.DistanceTo(C);
	double c = C.DistanceTo(A);
	double p = (a + b + c)/2;
	return sqrt1(p*(p-a)*(p-b)*(p-c));
}

void main()
{
	//freopen("input.txt", "r", stdin);
	
	Point A,B,C;
	double R;

	A.Scan();
	B.Scan();
	C.Scan();
	scanf("%lf",&R);

	double AB = A.DistanceTo(B);
	double ABC = (C-B)^(A-B), CAB = (C-A)^(B-A);
	double h = 2*TriangleArea(A,B,C)/AB;
	bool tangentCase = true;
	
	if(EQ(h,0))
		tangentCase = !EQ((A-C)^(B-C),0);
	else 
	{
		if(GE(ABC,PI/2) || GE(CAB, PI/2))
			tangentCase = false;
		else
			tangentCase = LT(h,R);
	}
		
	if(tangentCase)
	{
		double AC = A.DistanceTo(C), BC = B.DistanceTo(C);
		double ATang = sqrt1(SQR(AC) - SQR(R)), BTang = sqrt1(SQR(BC) - SQR(R));
		double AAngle = acos1(R/AC), BAngle = acos1(R/BC);
		double ACB = (A - C)^(B - C);
		printf("%.2lf", ATang + BTang + (ACB - AAngle - BAngle)*R);
	}
	else
		printf("%.2lf", AB);
}