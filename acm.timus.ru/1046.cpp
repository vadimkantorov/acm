#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstdlib>
const double pi = 3.1415926535897932384626433832795;

struct Point
{
	double X,Y;

	Point()
	{
		X = Y = 0;
	}

	Point(double x, double y)
	{
		X = x;
		Y = y;
	}

	void Scan()
	{
		scanf("%lf%lf",&X,&Y);
	}

	void Print()
	{
		printf("%.2lf %.2lf\n",X,Y);
	}
};

struct Line
{
	double a,b,c;

	Line(Point& A, Point& B)
	{
		double x1 = A.X, y1 = A.Y, x2 = B.X, y2 = B.Y;
		a = y2 - y1;
		b = x1 - x2;
		c = -a*x1 -b*y1;
	}

	Point Cross(Line& l)
	{
		Point p;
		p.X = (-c*l.b + b*l.c)/(a*l.b - b*l.a);
		p.Y = (-a*l.c + c*l.a)/(a*l.b - b*l.a);
		return p;
	}
};

struct Rotation
{
	double Angle;
	Point Centre;

	Rotation()
	{
		Angle = 0;
	}

	Rotation Compose(Rotation r)
	{
		Rotation rot;
		rot.Angle = Angle + r.Angle;
		
		Point p1(rand(),rand());
		Point p2 = r.Rotate(Rotate(p1));

		Line l(p1,p2);
		Point c((p1.X + p2.X)/2.0,(p1.Y + p2.Y)/2.0);
		Line l1(c, Point(c.X + l.a, c.Y + l.b));

		p1 = Point(rand(), rand());
		p2 = r.Rotate(Rotate(p1));
		l = Line(p1,p2);
		c = Point((p1.X + p2.X)/2.0,(p1.Y + p2.Y)/2.0);
		Line l2(c, Point(c.X + l.a, c.Y + l.b));
		
		rot.Centre = l1.Cross(l2);
		
		return rot;
	}

	Point Rotate(Point& p)
	{
		double x = p.X - Centre.X, y = p.Y - Centre.Y, an = Angle;
		
		Point res;
		res.X = x*cos(an) - y*sin(an) + Centre.X;
		res.Y = x*sin(an) + y*cos(an) + Centre.Y;
		return res;
	}
};

Rotation rs[55];


void main()
{
	srand(time(0));
	
	int n;
	scanf("%d",&n);
	
	for(int i = 0; i < n; i++)
		rs[i].Centre.Scan();
	for(int i = 0; i < n; i++)
	{
		scanf("%lf",&rs[i].Angle);
		rs[i].Angle *= pi/180.0;
	}

	Rotation rot = rs[0];
	for(int i = 1; i < n; i++)
		rot = rot.Compose(rs[i]);
	
	Point cur = rot.Centre;
	for(int i = 0; i < n; i++)
	{
		cur.Print();
		cur = rs[i].Rotate(cur);
	}
}