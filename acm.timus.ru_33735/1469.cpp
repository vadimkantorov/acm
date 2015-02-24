#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <set>
using namespace std;

const int N = 50003;

struct Endpoint
{
	int X,Y;
	bool IsRight;
	int SegmentIndex;

	bool operator<(Endpoint& rhs) const
	{
		if(X != rhs.X)
			return X < rhs.X;
		if(IsRight != rhs.IsRight)
			return IsRight < rhs.IsRight;
		return Y < rhs.Y;
	}
};

struct Segment
{
	Endpoint Left,Right;
	int Index;

	Segment() { }
	Segment(Endpoint& a, Endpoint& b, int i)
	{
		a.SegmentIndex = b.SegmentIndex = i;
		a.IsRight = a.X > b.X;
		b.IsRight = !a.IsRight;
		
		if(a.IsRight)
			swap(a,b);
		
		Index = i;
		Left = a;
		Right = b;
	}

	double Y(int x) const
	{
		if(Left.X != Right.X)
		{
			double alpha = double(x - Left.X)/(Right.X - Left.X);
			return Left.Y + (Right.Y - Left.Y)*alpha;
		}
		else
			return Left.Y;
	}

	bool operator<(const Segment& rhs) const
	{
		int rx = max(Left.X, rhs.Left.X);
		return Y(rx)< rhs.Y(rx);
	}

	static bool InEx(int c, int d, int a, int b)
	{
		return max(a,b) >= min(c,d) &&
			min(a,b) <= max(c,d);
	}

	bool IntersectsWith(Segment& x)
	{
		double v1x = Right.X - Left.X;
		double v1y = Right.Y - Left.Y;
		double v2x = x.Right.X - x.Left.X;
		double v2y = x.Right.Y - x.Left.Y;
		
		double v11 = v1x*(x.Left.Y - Left.Y) - v1y*(x.Left.X - Left.X);
		double v12 = v1x*(x.Right.Y - Left.Y) - v1y*(x.Right.X - Left.X);
		double v21 = v2x*(Left.Y - x.Left.Y) - v2y*(Left.X - x.Left.X);
		double v22 = v2x*(Right.Y - x.Left.Y) - v2y*(Right.X - x.Left.X);

		if(v11 == 0 && v12 == 0 && v21 == 0 && v22 == 0)
			return InEx(Left.X, Right.X, x.Left.X, x.Right.X)
				&& InEx(Left.Y, Right.Y, x.Left.Y, x.Right.Y);
		else
			return v11*v12 <= 0 && v21*v22 <= 0;
	}
};

Endpoint Q[2*N];
Segment S[N];

set<Segment> window;
int n;

typedef set<Segment>::iterator SegIter;

void YES(int i, int j)
{
	printf("YES\n%d %d",i+1,j+1);
	exit(0);
}

SegIter Below(SegIter loc)
{
	return loc != window.begin() ? --loc : window.end();
}

SegIter Above(SegIter loc)
{
	return ++loc;
}

void main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif

	scanf("%d",&n);
	for(int i = 0; i < n; i++)
	{
		int paired = 2*n-i-1;
		scanf("%d%d%d%d", &Q[i].X, &Q[i].Y, &Q[paired].X, &Q[paired].Y);
		
		S[i] = Segment(Q[i], Q[paired], i);
	}

	n *= 2;
	sort(Q, Q+n);

	for(int i = 0; i < n; i++)
	{
		Endpoint cur = Q[i];
		if(!cur.IsRight)
		{
			pair<SegIter, bool> inserted = window.insert(S[cur.SegmentIndex]);
			SegIter loc = inserted.first;
			SegIter below = Below(loc);
			SegIter above = Above(loc);
			
			if(inserted.second)
			{
				if(above != window.end() && loc->IntersectsWith(*above))
					YES(loc->Index, above->Index);
				if(below != window.end() && loc->IntersectsWith(*below))
					YES(loc->Index, below->Index);
			}
			else
				YES(loc->Index, cur.SegmentIndex);
		}
		else
		{
			SegIter loc = window.find(S[cur.SegmentIndex]);
			SegIter below = Below(loc);
			SegIter above = Above(loc);

			if(above != window.end() && below != window.end() && above->IntersectsWith(*below))
				YES(above->Index, below->Index);
			
			window.erase(loc);
		}
	}

	puts("NO");
}