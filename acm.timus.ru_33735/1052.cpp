#include <cstdio>
#include <cmath>
#define SQR(x) ((x)*(x))
#define EPS 1e-5
#define EQ(x,y) (fabs(x-y) <= EPS)
struct Point
{
	double X, Y;

	void Scan()
	{
		scanf("%lf%lf",&X, &Y);
	}
};

struct Line
{
	double a,b,c;

	Line(Point& A, Point& B)
	{
		double x1 = A.X, x2 = B.X, y1 = A.Y, y2 = B.Y;
		a = y2-y1;
		b = x1-x2;
		c = -a*x1-b*y1;
	}

	void Normalize()
	{
		double temp = sqrt(SQR(a) + SQR(b));
		a /= temp;
		b /= temp;
		c /= temp;
	}

	double Value(Point& p)
	{
		return a*p.X + b*p.Y + c;
	}
};

Point ps[202];

void main()
{
	//freopen("input.txt", "r", stdin);

	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		ps[i].Scan();

	int max = 0;
	for(int i = 0; i < n; i++)
		for(int j = i+1; j < n; j++)
		{
			Line l(ps[i], ps[j]);
			l.Normalize();
			int count = 0;
			for(int k = 0; k < n; k++)
			{
				if(EQ(l.Value(ps[k]),0))
					count++;
			}
			if(count > max)
				max = count;
		}
	printf("%d",max);
}