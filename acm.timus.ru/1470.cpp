#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 130;
const int L = 0;
const int R = 128;

struct D3Summator
{
	int M[N][N][N];
	
	void Insert(int x, int y, int z, int k)
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
					{
						int p = L, q = R;
						while(p <= q)
						{
							int c = (p+q)/2;
							if(z <= c)
								M[mid][m][c] += k;
							if(c < z)
								p = c+1;
							else if(c > z)
								q = c-1;
							else
								break;
						}
					}
					
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

	int Sum(int x, int y, int z)
	{
		if( x == -1 || y == -1 || z == -1)
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
					{
						int p = L, q = R;
						while(p <= q)
						{
							int c = (p+q)/2;
							if(c <= z)
								sum += M[mid][m][c];
							if(c < z)
								p = c+1;
							else if(c > z)
								q = c-1;
							else
								break;
						}
					}

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

	int Sum(int x1, int y1, int z1, int x2, int y2, int z2)
	{
		return Sum(x2,y2,z2) 
			-Sum(x2,y2,z1-1)
			-(Sum(x2,y1-1,z2) - Sum(x2,y1-1,z1-1))
			-(Sum(x1-1,y2,z2) - Sum(x1-1,y2,z1-1))
			+(Sum(x1-1,y1-1,z2) - Sum(x1-1,y1-1,z1-1));
	}
};


D3Summator tree;

void main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	int n;
	scanf("%d",&n);

	while(true)
	{
		int a;
		scanf("%d",&a);
		switch(a)
		{
		case 1:
			int x,y,z,k;
			scanf("%d%d%d%d",&x,&y,&z,&k);
			tree.Insert(x,y,z,k);
			break;
		case 2:
			int x1,y1,z1,x2,y2,z2;
			scanf("%d%d%d%d%d%d",&x1,&y1,&z1,&x2,&y2,&z2);
			printf("%d\n",tree.Sum(x1,y1,z1,x2,y2,z2));
			break;
		case 3:
			return;
		}
	}
}