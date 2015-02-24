//ACCEPTED CODE
#include <cstdio>
#include <functional>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

double SQR(double x)
{
	return x*x;
}

struct Point
{
	int X,Y;
	unsigned short Index, Rank;

	double Dist(Point& p)
	{
		return sqrt(SQR(X-p.X) + SQR(Y-p.Y));
	}

	static bool YComp(const Point& lhs, const Point& rhs)
	{
		if(lhs.Y != rhs.Y)
			return lhs.Y < rhs.Y;
		return lhs.X < rhs.X;
	}

	static bool XComp(const Point& lhs, const Point& rhs)
	{
		if(lhs.X != rhs.X)
			return lhs.X < rhs.X;
		return lhs.Y < rhs.Y;
	}
};

struct Triangle
{
	Point ps[3];
	double Perimeter;

	Triangle(Point a, Point b, Point c)
	{
		ps[0] = a;
		ps[1] = b;
		ps[2] = c;

		Perimeter = 0.0;
		for(int i = 0; i < 3; i++)
			Perimeter += ps[i].Dist(ps[(i+1)%3]);
	}

	void Print()
	{
		printf("%lf\n%hu %hu %hu", Perimeter, ps[0].Index, ps[1].Index, ps[2].Index);
	}
};

const int N = 66000;
const int LEVEL = 14;
const int UNIT = 8;

Point XSorted[N];
Point YSorted[LEVEL][N];
Point Strip[N];
int Lengths[LEVEL][1 << LEVEL];
int stripLength;

Triangle MinimalPerimeterTriangle(int xleft, int xright, int level, int segmentInd)
{
	int n = xright-xleft+1;
	int segmentSize = (1 << (LEVEL - level - 1))*UNIT;
	int newLevel = level + 1;
	int newSegmentSize = segmentSize / 2;

	Point* xSorted = &XSorted[xleft];
	Point* ySorted = &YSorted[level][segmentInd*segmentSize];
	
	Triangle best(xSorted[0], xSorted[1], xSorted[2]);

	if(n <= UNIT)
	{  
		for(int i = 0; i < n; i++)
		{
			for(int j = i+1; j < n; j++)
			{
				for(int k = j+1; k < n; k++)
				{
					Triangle tr(xSorted[i],xSorted[j],xSorted[k]);
					if(tr.Perimeter < best.Perimeter)
						best = tr;
				}
			}
		}
	}
	else
	{
		Point lastLeft = xSorted[n/2 - 1];
		
		for(int i = 0; i < n; i++)
		{
			Point cur = ySorted[i];
			bool pushRight = cur.Rank > lastLeft.Rank;
			
			int newSegmentInd = 2*segmentInd + pushRight;
			int& len = Lengths[newLevel][newSegmentInd];
			
			YSorted[newLevel][newSegmentInd*newSegmentSize + len++] = cur;
		}

		int rl = xleft + n/2;
		Triangle lt = MinimalPerimeterTriangle(xleft, rl-1, newLevel, 2*segmentInd);
		Triangle rt = MinimalPerimeterTriangle(rl, xright, newLevel, 2*segmentInd + 1);
		best = lt.Perimeter < rt.Perimeter ? lt : rt;
		
		for(int i = 0; i < n; i++)
		{
			Point cur = ySorted[i];
			if(2*abs(cur.X - lastLeft.X) <= best.Perimeter)
				Strip[stripLength++] = cur;
		}

		for(int i = 0; i < stripLength; i++)
		{
			for(int j = 1; j <= 3 && i+j < stripLength; j++)
			{
				for(int k = 1; j+k <= 3 && i+j+k < stripLength; k++)
				{
					Triangle tr(Strip[i], Strip[i+j], Strip[i+j+k]);
					if(tr.Perimeter < best.Perimeter)
						best = tr;
				}
			}
		}
		stripLength = 0;
	}

	return best;
}

void Preprocess(int n)
{
	sort(XSorted, XSorted+n, Point::XComp);
	for(int i = 0; i < n; i++)
		XSorted[i].Rank = i;
	
	Lengths[0][0] = n;
	copy(XSorted, XSorted + n, YSorted[0]);
	sort(YSorted[0], YSorted[0] + n, Point::YComp);
}

void main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);

	int start = clock();
#endif

	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d%d", &XSorted[i].X, &XSorted[i].Y);
		XSorted[i].Index = i+1;
	}

	Preprocess(n);
	MinimalPerimeterTriangle(0, n-1, 0, 0).Print();

#ifndef ONLINE_JUDGE	
	printf("\nTime: %lf", double(clock()-start)/CLOCKS_PER_SEC);
	printf("\nMemory: %.2lf Mb",(sizeof(XSorted) + sizeof(YSorted) + sizeof(Lengths) + sizeof(Strip))/(1e+6));
#endif
}