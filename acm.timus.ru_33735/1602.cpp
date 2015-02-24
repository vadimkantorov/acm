#include <cstdio>
#include <cmath>

bool LT(int x, int y)
{
	return x < y;
}

bool EQ(int x, int y)
{
	return x == y;
}

double max(int x, int y)
{
	if(LT(x,y))
		return y;
	return x;
}

int main()
{
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);

	int n,k;
	double U,V;
	scanf("%d%d%lf%lf",&n,&k,&U,&V);

	int u = U*100000;
	int v = V*100000;
	
	int minTime = u*(n-1);
	int minFloor = 1;


	for(int i = n; i > 1; i--)
	{
		int ladder = (n - i)*u;
		int liftDown = v*(k-1)+15*100000;
		int liftUsage = 2*v*(i-1) + 5*100000;

		int time = liftUsage + max(ladder, liftDown);

		if(LT(time,minTime) || (EQ(time, minTime) && i > minFloor))
		{
			minTime = time;
			minFloor = i;
		}
	}

	printf("%d",minFloor);

	return 0;
}