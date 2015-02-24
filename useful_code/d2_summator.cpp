#include <cstdio>
#include <algorithm>
#define N 2000
using namespace std;

int L = 1, R = 1 << 4;

struct D1Summator
{
	static const int MAX = 1 << 7 + 6;
	int L[MAX],P[MAX];

	D1Summator()
	{
		fill_n(L,MAX,0);
		fill_n(P,MAX,0);
	}

	void Insert(int d, int k)
	{
		P[d] += k;
		
		int l = 1, r = 1 << 7;
		while(l <= r)
		{
			int mid = (l+r)/2;
			if(d == mid)
				break;
			if(d < mid)
			{
				r = mid-1;
				L[mid] += k;
			}
			else if(d > mid)
				l = mid + 1;
		}
	}

	int Sum(int d)
	{
		if(d == 0)
			return 0;
		int l = 1, r = 1 << 7, res = 0;
		while(l <= r)
		{
			int mid = (l+r)/2;
			if(d == mid)
			{
				res += P[mid];
				break;
			}
			if(d < mid)
				r = mid-1;
			else if(d > mid)
			{
				l = mid + 1;
				res += P[mid];
			}
		}
		return res;
	}

	int Sum(int i, int j)
	{
		return Sum(j)-Sum(i-1);
	}
};


struct D2Summator
{
	int M[N][N];
	
	void Insert(int x, int y, int k)
	{
		int a = L, b = R;
		while( a <= b )
		{
			int mid = (a+b)/2;

			if(x <= mid)
			{
				int l = L, r = R;
				while(l <= r)
				{
					int m = (l+r)/2;
					
					if(y <= m)
						M[mid][m] += k;
					
					if(m < y)
						l = m+1;
					else if(m > y)
						r = m-1;
					else
						break;
				}
			}

			if(mid < x)
				a = mid+1;
			else if(mid > x)
				b = mid-1;
			else
				return;
		}
	}

	int Sum(int x, int y)
	{
		if( x == 0 || y == 0)
			return 0;

		int sum = 0;
		int a = L, b = R;
		while(a <= b)
		{
			int mid = (a+b)/2;
			if(mid <= x)
			{
				int l = L, r = R;
				while(l <= r)
				{
					int m = (l+r)/2;
					if(m <= y)
						sum += M[mid][m];

					if(m < y)
						l = m+1;
					else if(m > y)
						r = m-1;
					else
						break;
				}
			}
			
			if(mid < x)
				a = mid+1;
			else if(mid > x)
				b = mid-1;
			else
				break;
		}
		return sum;
	}

	int Sum(int x1, int y1, int x2, int y2)
	{
		return Sum(x2,y2)-Sum(x1-1,y2)-Sum(x2,y1-1)+Sum(x1-1,y1-1);
	}
};

D2Summator tree;
D1Summator tree2;

void main()
{
	freopen("input.txt","r",stdin);
	
	int n,m;
	scanf("%d%d\n",&n,&m);
	
	for(int i = 0; i < m; i++)
	{
		if(getchar() == 'I')
		{
			int x,y,k;
			scanf("%d%d%d\n",&x,&y,&k);
			tree.Insert(x,y,k);
		}
		else
		{
			int x1,y1,x2,y2;
			scanf("%d%d%d%d\n",&x1,&y1,&x2,&y2);
			printf("%d",tree.Sum(x1,y1,x2,y2));
		}
	}
}