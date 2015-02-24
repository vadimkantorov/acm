#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 105;
const int K = 55;

int M[N], Gr[N][N], Res[K], MidGr[K][N], L[K];
int n, iter;

int Grundy(int left, int right)
{
	if(Gr[left][right] != -1)
	{
		return Gr[left][right];
	}

	bool g[N];
	fill_n(g,N,false);

	for(int i = left; i <= right; i++)
	{
		int f = -1, l = -1;
		int res = 0;
		for(int j = left; j <= right; j++)
		{
			if(M[j] > M[i])
			{
				if(l == -1)
					f = l = j;
				else
					l++;
			}
			else
			{
				if(l != -1)
				{
					res ^= Grundy(f,l);
					f = l = -1;
				}
			}
		}
		if(l != -1)
		{
			res ^= Grundy(f,l);
			f = l = -1;
		}
		g[res] = true;
		if(left == 0 && right == n-1)
			MidGr[iter][i] = res;
	}
	
	Gr[left][right] = find(g,g+N,false) - g;
	return Gr[left][right];
}

void PrepareGrundy()
{
	for(int i = 0; i < n; i++)
	{
		Gr[i][i] = 1;
		for(int j = i+1; j < n; j++)
			Gr[i][j] = Gr[j][i] = -1;
	}
}


void main()
{
	//freopen("input.txt","r",stdin);

	int k;
	scanf("%d",&k);

	int res = 0;
	for(iter = 0; iter < k; iter++)
	{
		scanf("%d",&n);
		L[iter] = n;

		for(int j = 0; j < n; j++)
			scanf("%d",&M[j]);
		
		PrepareGrundy();
		Res[iter] = Grundy(0,n-1);
		res ^= Res[iter];
	}
	if(res > 0)
	{
		puts("G");

		for(int i = 0; i < k; i++)
		{
			int curres = (res^Res[i]);
			for(int j = 0; j < L[i]; j++)
			{
				if((curres ^ MidGr[i][j]) == 0)
				{
					printf("%d %d",i+1, j+1);
					return;
				}
			}
		}
	}
	else
	{
		puts("S");
	}
}