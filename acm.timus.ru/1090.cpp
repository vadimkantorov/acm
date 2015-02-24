#include <cstdio>
#include <algorithm>
#include <vector>
#define N 10005
using namespace std;


struct InversionCounter
{
	int n;
	int M[N],T[N];
	
	InversionCounter(int n) : n(n) { }

	void Init()
	{
		for(int i = 0; i < n; i++)
			scanf("%d",&M[i]);
	}

	int Merge(int a, int b, int l, int r)
	{
		int i = a, j = l;
		int k = 0, res = 0;
		while(i <= b && j <= r)
		{
			if(M[i] <= M[j])
			{
				res += k-(i-a);
				T[k++] = M[i++];
			}
			else
				T[k++] = M[j++];
		}

		if(i <= b)
		{
			while(i <= b)
			{
				res += k-(i-a);
				T[k++] = M[i++];
			}
		}
		else
		{
			while(j <= r)
				T[k++] = M[j++];
		}
		copy(T,T+k,M+a);
		return res;
	}

	int GetInversionsCount(int left, int right)
	{
		if(right == left)
			return 0;
		int mid = (left+right)/2;
		int res = GetInversionsCount(left,mid) + GetInversionsCount(mid+1,right);
		res += Merge(left,mid,mid+1,right);
		return res;
	}
};

void main()
{
	//freopen("input.txt","r",stdin);
	
	int n,k, max = 0, maxi = 0;
	scanf("%d%d",&n,&k);
	InversionCounter* ic = new InversionCounter(n);
	for(int i = 0; i < k; i++)
	{
		ic->Init();
		int invc = ic->GetInversionsCount(0,n-1);
		if(invc > max)
		{
			max = invc;
			maxi = i;
		}
	}
	printf("%d",maxi+1);
}