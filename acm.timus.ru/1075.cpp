#include <cstdio>
#include <cmath>

#define SQR(x) ((x)*(x))
#define EPS 1e-7
#define EQ(x,y) (fabs((y) - (x)) <= EPS)
#define LT(x,y) (((y) - (x)) > EPS)
#define GT(x,y) LT(y,x)
#define LE(x,y) (LT(x,y) || EQ(x,y))
#define GE(x,y) LE(y,x)

const double PI = 3.1415926535897932384626433832795;

double acos1(double x)
{
	if(x > 1)
		x = 1;
	if(x < -1)
		x = -1;
	return acos(x);
}

double sqrt1(double x)
{
	if(x < 0)
		x = 0;
	return sqrt(x);
}

struct Point
{
	double X,Y,Z;

	Point() {}
	Point(double X, double Y, double Z) : X(X), Y(Y), Z(Z) { }
	
	void Scan()
	{
		scanf("%lf %lf %lf",&X, &Y, &Z);
	}

	double Length()
	{
		return sqrt1(SQR(X) + SQR(Y) + SQR(Z));
	}

	double DistanceTo(Point& x)
	{
		return sqrt1(SQR(X - x.X) + SQR(Y - x.Y) + SQR(Z - x.Z));
	}

	Point operator-(Point& x)
	{
		return Point(X - x.X, Y - x.Y, Z - x.Z);
	}

	double operator%(Point& x)
	{
		double X1 = X, Y1 = Y, Z1 = Z, X2 = x.X, Y2 = x.Y, Z2 = x.Z;
		return sqrt(SQR(Y1*Z2 - Y2*Z1) + SQR(Z1*X2 - Z2*X1) + SQR(X1*Y2 - X2*Y1));
			
		//return Y1*Z2 - Y2*Z1 + Z1*X2 - Z2*X1 + X1*Y2 - X2*Y1;
	}

	double operator*(Point& x)
	{
		return X*x.X + Y*x.Y + Z*x.Z;
	}

	double operator^(Point& x)
	{
		return acos1(((*this)*x)/(Length()*x.Length()));
	}
};

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
	double h = fabs((A - C)%(B - C))/AB;
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