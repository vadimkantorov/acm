#include <cstdio>
#include <cstdlib>
const int N = 102;

struct Sleeper
{
	int X,Y;
	int Number;
	int SleepersBefore;
};

int compSleepers(const void* l, const void* r)
{
	Sleeper a = *((Sleeper*)l);
	Sleeper b = *((Sleeper*)r);

	if(a.X > b.X)	return 1;
	if(a.X < b.X)	return -1;
	return 0;
}

Sleeper X[N];

void main()
{
	//freopen("input.txt","r",stdin);
	
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d %d",&X[i].X, &X[i].Y);
		X[i].Number = i + 1;
	}
	qsort(X,n,sizeof(Sleeper),compSleepers);
	X[0].SleepersBefore = 0;
	int maxbef = -1;
	for(int i = 1; i < n; i++)
	{
		for(int j = i-1; j >= 0; j--)
		{
			if(X[i].Y > X[j].Y && X[j].SleepersBefore + 1 > X[i].SleepersBefore)
			{
				X[i].SleepersBefore = X[j].SleepersBefore + 1;
				if(X[i].SleepersBefore > maxbef)
					maxbef = X[i].SleepersBefore;
			}
		}
	}
	printf("%d",n - maxbef - 1);
}