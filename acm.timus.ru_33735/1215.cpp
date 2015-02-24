#include <cstdio>
#include <cmath>

#define EPS 0.00001

#define EQ(a,b) (fabs((a)-(b)) <= EPS)
#define NE(a,b) (fabs((a)-(b)) > EPS)
#define GT(a,b) (a - b >= EPS)
#define GE(a,b) (a - b >= -EPS)
#define LT(a,b) (a - b <= -EPS)
#define LE(a,b) (a - b <= EPS)
#define SQR(x) (x) * (x)

#define MIN(a,b) ( LT((a), (b)) ) ? (a) : (b)
# define M_PI_2         1.57079632679489661923

const int MAXPOL = 101;

using namespace std;

struct point
{
	double x,y;
	point(){}
	point(double _x, double _y):x(_x),y(_y){}

	double dist(point& b)
	{
		return sqrt( SQR(x - b.x) + SQR(y - b.y) );
	}
};

struct segment
{
	point a,b;
	segment(){}
	segment(point _a, point _b):a(_a),b(_b){}

	double length()
	{
		return a.dist(b);
	}
};

struct line
{
	double a,b,c;
	line(){}
	line(point _a, point _b)
	{
		a = _b.y - _a.y;
		b = _a.x - _b.x;
		c = (_b.x - _a.x)*_a.y - (_b.y - _a.y)*_a.x;
	}
	double value(point _a)
	{
		return a*_a.x + b*_a.y + c;
	}
	void normalize()
	{
		double tmp = sqrt(SQR(a) + SQR(b));
		a /= tmp;
		b /= tmp;
		c /= tmp;
	}
};

typedef point vector;

vector init_vector(point& a, point &b)
{
	return vector(b.x - a.x, b.y - a.y);
}

double vector_length(vector& v)
{
	return sqrt(SQR(v.x) + SQR(v.y));
}

double scalar_multiply(vector& v1, vector& v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

double angle(vector& v1, vector& v2)
{
	return acos(scalar_multiply(v1,v2)/vector_length(v1)/vector_length(v2));
}

struct polygon
{
	int num;
	point p[MAXPOL];
	polygon(int n) : num(n) {}
};

bool point_on_segment(segment& s, point& a)
{
	return ( EQ(a.dist(s.a) + a.dist(s.b) , s.a.dist(s.b)) );
}

/*bool segments_intersect(segment& our, segment& side)
{
	line l2(our.a, our.b);
	line l1 (side.a, side.b);
	double our_val_1 = l1.value(our.a);
	double our_val_2 = l1.value(our.b);
	double side_val_1 = l2.value(side.a);
	double side_val_2 = l2.value(side.b);
	//if ( EQ(side_val_1,0) || EQ(side_val_2,0) ) return false;
	//if( EQ(our_val_1,0) || EQ(our_val_2,0) || EQ(side_val_1,0) || EQ(side_val_2,0))
	//{
	//	return ( point_on_segment(our,side.a) || point_on_segment(our,side.b) ||
	//		point_on_segment(side,our.a) || point_on_segment(side,our.b));
	//}
	//else
	{
		return LT(our_val_1 * our_val_2, 0) && LT(side_val_1 * side_val_2, 0);
	}
}*/

/*bool vertex_on_seg(segment& s, polygon& p)
{
	for(int i = 0; i < p.num; i++)
	{
		if( point_on_segment(s,p.p[i]) )
			return true;
	}
	return false;
}
*/
bool point_in_polygon(point& a, polygon& p)
{
	line l(p.p[0], p.p[1]);
	bool sign = GT(l.value(a), 0);
	for ( int i = 1; i < p.num; i++ )
	{
		line tmp(p.p[i], p.p[(i+1)%p.num]);
		segment seg(p.p[i], p.p[(i+1)%p.num]);
		double d = tmp.value(a);
		if ( d == 0 )
		{
			if ( point_on_segment(seg,a) )
			{
				return true;
			}
		}
		else if ( GT(d, 0) != sign )
		{
			return false;
		}
	}
	return true;
}


double dist_point_segment(point &p, segment &s)
{
	vector ab = init_vector(s.a,s.b);
	vector ba = init_vector(s.b,s.a);
	vector ap = init_vector(s.a,p);
	vector bp = init_vector(s.b,p);
	if ( angle(ab, ap) > M_PI_2 || angle(ba, bp) > M_PI_2 )
	{
		return MIN( s.a.dist(p), s.b.dist(p) );
	}
	else
	{
		line l(s.a, s.b);
		l.normalize();
		return fabs(l.value(p));
	}
}

int main()
{
	point p;
	int n;
	scanf("%lf %lf %d", &p.x, &p.y, &n);
	polygon P(n);
	for(int i = 0; i < n; i++)
		scanf("%lf %lf",&P.p[i].x, &P.p[i].y);
	if(point_in_polygon(p,P))
		printf("0.000");
	else
	{
		double mindist = 1e+9;
		for(int i = 1; i < n; i++)
			if(dist_point_segment(p,segment(P.p[i-1],P.p[i])) < mindist)
				mindist = dist_point_segment(p,segment(P.p[i-1],P.p[i]));
		if(dist_point_segment(p,segment(P.p[n-1],P.p[0])) < mindist)
				mindist = dist_point_segment(p,segment(P.p[n-1],P.p[0]));
		printf("%.3lf",mindist*2);
	}
	return 0;
}