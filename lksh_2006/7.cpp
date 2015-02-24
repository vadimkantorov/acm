#include <cstdio>
long long int P[65][65];


void FillP(int n)
{
	P[2*n][0] = 1;
	for(int x = 2*n-1; x >= 0; x--)
	{
		P[x][2*n] = P[x+1][2*n-1];
		for(int y = 2*n-1; y >= 1; y--)
			P[x][y] = P[x+1][y+1] + P[x+1][y-1];
		P[x][0] = P[x+1][1];
	}
}

/*//Recursive version of FillP. Init call - Go(0,0). Make n global variable
int Go(int x, int y)
{
	if(P[x][y] == 0)
	{
		if(x == n && y == n)
			P[x][y] = 1;
		else if(x == 2*n && y != 0)
			P[x][y] = 0;
		else if(x == 2*n && y == 0)
			P[x][y] = 1;
		else
		{
			int a = 0;
			int b = 0;
			if(x + 1 <= 2*n)
			{
				a = Go(x+1,y+1);
				if(y > 0)
					b = Go(x+1,y-1);
			}
			P[x][y] = a + b;
		}
	}
	return P[x][y];
}*/

void Print(long long int num, int n)
{
	int y = 0;
	for(int x = 0; x < 2*n; x++)
	{
		if(num <= P[x+1][y+1])
		{
			putchar('(');
			y++;
		}
		else
		{
			putchar(')');
			num -= P[x+1][y+1];
			y--;
		}
	}
}

int main()
{
	int n;
	long long int k;
	scanf("%d%I64d",&n,&k);
	FillP(n);
	if( k > P[0][0])
		puts("ERROR");
	else
		Print(k,n);
	return 0;
}