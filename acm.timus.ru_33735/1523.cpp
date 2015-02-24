#include <cstdio>
#define ulong __int64

const int MAX = 1 << 15;
int M[15][MAX+5];

int Parent(int idx)
{
	return idx + (idx & -idx);
}

int Left(int idx)
{
	return idx - (idx & -idx);
}

int Modulo(ulong a, ulong b)
{
	ulong l = a;
	ulong r = b;
	return (l+r)%int(1e+9);
}

void Add(int x, int k)
{
	ulong added = 1;
	for(int i = 1; i <= k; i++)
	{
		int idx = x;
		ulong adding = 0;
		while(idx > 0)
		{
			adding += M[i][idx];
			idx = Left(idx);
		}
		
		idx = x;
		while(idx <= MAX)
		{
			M[i][idx] = Modulo(M[i][idx], added);
			idx = Parent(idx);
		}

		added = adding;
	}
}

int Count(int k)
{
	return M[k][MAX];
}

void main()
{
	int n,k;
	scanf("%d%d",&n,&k);

	for(int i = 0; i < n; i++)
	{
		int x;
		scanf("%d",&x);
		Add(n-x+1,k);
	}
	
	printf("%d",Count(k));
}