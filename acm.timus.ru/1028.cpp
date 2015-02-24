#include <cstdio>
#include <algorithm>
#define N 32768
using namespace std;

struct FenwickTree
{
	int M[N+5],P[N+5];

	FenwickTree()
	{
		fill_n(M,N,0);
		fill_n(P,N,0);
	}

	void Add(int t)
	{
		P[t]++;
		int l = 1, r = N;

		while(l <= r)
		{
			int mid = (l+r)/2;
			if(t == mid)
				break;
			if(t < mid)
			{
				M[mid]++;
				r = mid-1;
			}
			else if(t > mid)
				l = mid+1;
		}
	}

	int Value(int t)
	{
		int res = 0;
		int l = 1, r = N;

		while(l <= r)
		{
			int mid = (l+r)/2;
			if(t == mid)
			{
				res += M[mid];
				break;
			}
			if(t < mid)
				r = mid-1;
			else if(t > mid)
			{
				res += M[mid];
				res += P[mid];
				l = mid+1;
			}
		}
		return res;
	}
};

FenwickTree tree;

int T[N];

void main()
{
	//freopen("input.txt","r",stdin);

	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		tree.Add(a);
		int level = tree.Value(a+1);
		T[level]++;
	}
	for(int i = 1; i <= n ; i++)
		printf("%d\n",T[i]);
}