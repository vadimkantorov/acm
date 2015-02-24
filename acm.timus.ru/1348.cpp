#include <stdio.h>
#include <math.h>
#include <cstdlib>
#define SQR(x) (x)*(x)
#define M_PI_2     1.57079632679489661923
struct point
{
	double x,y;
};

struct segment
{
	point A,B;
	double disttop(point x)
	{
		if(A.x == B.x && A.y == B.y)
			return sqrt(SQR(x.x-A.x)+SQR(x.y-A.y));
		double sc1 = ((x.x-A.x)*(B.x-A.x)+(x.y-A.y)*(B.y-A.y));//AX and AB 
		double sc2 = ((x.x-B.x)*(A.x-B.x)+(x.y-B.y)*(A.y-B.y));//BX and BA
	
		sc1 /= sqrt((SQR(x.x-A.x)+SQR(x.y-A.y))*(SQR(B.x-A.x)+SQR(B.y-A.y)));
		sc2 /= sqrt((SQR(x.x-B.x)+SQR(x.y-B.y))*(SQR(B.x-A.x)+SQR(B.y-A.y)));
		


		sc1 = acos(sc1);
		sc2 = acos(sc2);
		if(sc1 > M_PI_2 || sc2 > M_PI_2)
		{
			double d1 = sqrt(SQR(x.x-A.x)+SQR(x.y-A.y));
			double d2 = sqrt(SQR(x.x-B.x)+SQR(x.y-B.y));
			return ((d1<d2)?d1:d2);
		}
		else
		{
			double a = B.y - A.y;
			double b = A.x - B.x;
			double c = -a*A.x - b*A.y;
			return fabs((a*x.x + b*x.y +c) / sqrt(SQR(a) + SQR(b)));
		}
	}
};
void main()
{
	point C;
	segment AB;

	double L;
	scanf("%lf %lf %lf %lf %lf %lf %lf",&AB.A.x, &AB.A.y, &AB.B.x, &AB.B.y, &C.x, &C.y, &L);
	double dist1 = AB.disttop(C);
	
	double d1 = sqrt(SQR(C.x-AB.A.x)+SQR(C.y-AB.A.y));
	double d2 = sqrt(SQR(C.x-AB.B.x)+SQR(C.y-AB.B.y));
	
	double dist2 = ((d1>d2)?d1:d2);
	
	if(dist1 <= L)
		dist1 = 0;
	else
		dist1 -= L;

	if(dist2 <= L)
		dist2 = 0;
	else
		dist2 -= L;
	printf("%.2lf\n%.2lf\n",dist1,dist2);
	//system("pause");*/	
}