#include <cstdio>

struct SegmentTree
{
	static const int N = (1 << 17);
	int val[2*N], sum[2*N];
	//val - inner
	//sum - outer


	void Add(int a, int b, int c)
	{
		Add(1,1,N,a,b,c);
	}

	void Add(int pos, int L, int R, int l, int r, int e)
	{
		sum[pos] += (r-l+1)*e;

		if(L == l && R == r)
			val[pos] += e;
		else
		{
			int mid = (L+R)/2;
			if(r <= mid)
				Add(2*pos,L,mid,l,r,e);
			else if(l > mid)
				Add(2*pos+1,mid+1,R,l,r,e);
			else
			{
				Add(2*pos,L,mid,l,mid,e);
				Add(2*pos+1,mid+1,R,mid+1,r,e);
			}
		}
	}

	int Count(int n)
	{
		return Count(1,1,N,n,n);
	}
	
	int Count(int pos, int L, int R, int l, int r)
	{
		if(L == l && R == r)
			return sum[pos];
		else
		{
			int mid = (L+R)/2;
			if(r <= mid)
			{
				return val[pos] + 
					Count(2*pos,L,mid,l,r);
			}
			else if(l > mid)
			{
				return val[pos] +
					Count(2*pos+1,mid+1,R,l,r);
			}
			else
			{
				return val[pos] +
					Count(2*pos,L,mid,l,mid) +
					Count(2*pos+1,mid+1,R,mid,r);
			}
		}
	}

} tree;

void main()
{
	int n;
	scanf("%d",&n);
	
	for(int i = 0; i < n+1; i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		tree.Add(a,b,c);
	}

	for(int i = 1; i <= n; i++)
		printf("%d ",tree.Count(i));
}