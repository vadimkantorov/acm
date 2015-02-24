#include <cstdio>
#include <cstdlib>

#define EPS (1e-14)
#define SQR(x) ((x)*(x))

int dc(double a,double b)
{
	if(b+EPS <= a)
		return 1;
	if(a+EPS <= b)
		return -1;
	return 0;
}

#define MIN(x,y) ( dc((x),(y)) < 0 ?x:y)
struct point
{
	double x,y;
	
	point(){}
	point(double _x, double _y):x(_x),y(_y){}
	point(point& beg, point& end)
	{
		x = end.x - beg.x;
		y = end.y - beg.y;
	}

	bool operator==(point& p)
	{
		return (dc(x,p.x) == 0 && dc(y,p.y) == 0);
	}
	
	point operator- (point& p)
	{
		return point(x-p.x,y-p.y);
	}

	point operator+ (point& p)
	{
		return point(x+p.x,y+p.y);
	}

	double operator* (point& p)
	{
		return x*p.x + y*p.y;
	}

	point operator* (double d)
	{
		return point(x*d,y*d);
	}

	double operator^ (point& p)
	{
		return x*p.y - y*p.x;
	}

	void scan()
	{
		scanf("%lf %lf",&x,&y);
	}
};

struct segment
{
	point a,b;
	segment(){}
	segment(point _a, point _b) : a(_a), b(_b){}
	double dist(point x)
	{
		point ab(a,b),ba(b,a),ax(a,x),bx(b,x);
		if(dc(ab*ax,0) > 0 && dc(ba*bx,0) > 0)
			return SQR(ab^ax)/(SQR(a.x-b.x)+SQR(a.y-b.y));
		else
			return MIN(SQR(x.x-a.x) + SQR(x.y-a.y),SQR(x.x-b.x) + SQR(x.y-b.y));
	}
};



struct square
{	
	point a,b,c,d;
	
	double distance;
	int num;
	
	void scan()
	{
		a.scan();
		c.scan();

		if(dc(a.x,c.x) > 0)
		{
			point tmp = a;
			a = c;
			c = tmp;
		}

		point center = point(a,c)*0.5;
		b = a + center + point(-center.y,center.x);
		d = a + center + point(center.y,-center.x);
	}
	
	bool operator< (square& s)
	{
		if( dc(distance,s.distance) < 0)
			return true;
		if(num < s.num)
			return true;
		return false;
	}

	void dist(point x)
	{
		if(a == c)
			distance = SQR(a.x-x.x)+SQR(a.y-x.y);
		else if(pointin(x))
			distance = 0;
		else
		{
			distance = 1000000000;
			segment ab(a,b),bc(b,c),cd(c,d),da(d,a);
			double ds[4] = {ab.dist(x), bc.dist(x), cd.dist(x), da.dist(x) };
			for(int i = 0; i < 4; i++)
				if(dc(ds[i],distance) < 0)
					distance = ds[i];
		}
		
	}
	bool pointin(point x)
	{
		point ab(a,b),bc(b,c),cd(c,d),da(d,a);
		point ax(a,x),bx(b,x),cx(c,x),dx(d,x);
		double vp1 = ab^ax,vp2 = bc^bx,vp3 = cd^cx,vp4 = da^dx;

		if(dc(vp1,0) >= 0 && dc(vp2,0) >= 0 && dc(vp3,0) >= 0 && dc(vp4,0) >= 0)
			return true;
		if(dc(vp1,0) <= 0 && dc(vp2,0) <= 0 && dc(vp3,0) <= 0 && dc(vp4,0) <= 0)
			return true;
		return false;
	}
};

/*int comparesquares(const void* l, const void* r)
{
	square a= *((square*)l);
	square b= *((square*)r);

	//int res = dc(a.distance,b.distance);
	//if(res != 0)
	//	return res;
	//if(a.num > b.num)
	//	return 1;
	//if(a.num < b.num)
	//	return -1;
	if(a < b)
		return -1;
	if(b < a)
		return 1;

	return 0;
}*/

square sq[105];

void main()
{
	//freopen("input.txt","r",stdin);
	
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
	{
		sq[i].scan();
		sq[i].num = i+1;
	}
	point a;

	a.scan();
	for(int i = 0; i < n; i++)
		sq[i].dist(a);
	square tmp;
	for(int i = 0; i < n; i++)
	{
		for(int j = i+1; j < n; j++)
		{
			if(sq[j] < sq[i])
			//if(comparesquares(&sq[j],&sq[i]) == -1)
			{
				tmp = sq[i];
				sq[i] = sq[j];
				sq[j] = tmp;
			}
		}
	}
	//qsort(sq,n,sizeof(square),comparesquares); //BUG HERE QSORT works incorrectly
	for(int i = 0; i < n; i++)
		printf("%d ",sq[i].num);
}