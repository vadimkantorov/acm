#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
#define N 152

int dX[] = {5,	4,4, 4,		3,3,3, 3, 3,	2,2,2,2,2,2,2,		1,1,1,1,1,1,1,1,1,		0,0,0,0,0,0,0,0,0,0,

			-5,	-4,-4, -4,		-3,-3,-3, -3, -3,	-2,-2,-2,-2,-2,-2,-2,		-1,-1,-1,-1,-1,-1,-1,-1,-1,		
};
int dY[] = {0,	0,1,-1,		0,1,2,-1,-2,	0,1,2,3,-1,-2,-3,	0,1,2,3,4,-1,-2,-3,-4,	1,2,3,4,5,-1,-2,-3,-4,-5,

			0,	0,1,-1,		0,1,2,-1,-2,	0,1,2,3,-1,-2,-3,	0,1,2,3,4,-1,-2,-3,-4,};

struct X
{
	int Length;
	int Sum;

	X(int Length, int Sum) : Length(Length), Sum(Sum) { }

	bool operator<(const X& x) const
	{
		return Length < x.Length;
	}
};


int M[N][N];
vector<X> A[N][N];


void main()
{
	//freopen("input.txt", "r", stdin);
	
	int h,w;
	scanf("%d%d",&h,&w);
	for(int i = 0; i < h; i++)
		for(int j = 0; j < w; j++)
			scanf("%d",&M[i][j]);

	for(int i = 0; i < h; i++)
		for(int j = 0; j < w; j++)
		{
			if(M[i][j] != 0)
			{
				for(int k = 0; k < 60; k++)
				{
					int x = j + dX[k];
					int y = i + dY[k];
					if(x >= 0 && x <= w-1 && y >= 0 && y <= h-1)
						A[y][x].push_back(X(abs(dX[k]) + abs(dY[k]),M[i][j]));
				}
			}
		}
	int tmp;
	for(int i = 0; i < h; i++)
	{
		for(int j = 0; j < w; j++)
			if(M[i][j] == 0)
			{
				if(!A[i][j].empty())
				{
					sort(A[i][j].begin(), A[i][j].end());
					int sum = 0;
					for(int k = 0; k < A[i][j].size(); k++)
					{
						if(A[i][j][k].Length == A[i][j][0].Length)
							sum |= A[i][j][k].Sum;
						else
							break;
					}

					printf("%d ",sum);
				}
				else
					printf("0 ");
			}
			else
				printf("-1 ");
		puts("");
	}
}