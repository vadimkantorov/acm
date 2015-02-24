#include <cstdio>
#include <algorithm>
#include <bitset>
#include <queue>

using namespace std;

const int N = 4;

typedef bitset<N*N> BS;

int pathLength[70000];

queue<BS> S;

void bfs(BS start)
{
	fill_n(pathLength, 70000, -1);
	pathLength[(unsigned short)start.to_ulong()] = 0;
	S.push(start);

	while(!S.empty())
	{
		start = S.front();
		S.pop();

		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < N; j++)
			{
				int di[] = {0,0,1,-1, 0};
				int dj[] = {1,-1,0,0,0};

				BS newState = start;

				for(int k = 0; k < N+1; k++)
				{
					int ni = i + di[k];
					int nj = j + dj[k];

					if(0 <= ni && ni < N &&
						0 <= nj && nj < N)
					{
						newState.flip(ni*N + nj);
					}
				}

				if(pathLength[(unsigned short)newState.to_ulong()] == -1)
				{
					pathLength[(unsigned short)newState.to_ulong()] = 1 + pathLength[(unsigned short)start.to_ulong()];
					S.push(newState);
				}
			}
		}
	}
}

void main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
#endif

	BS start;

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if(getchar() == 'w')
				start.set(i*N + j);
		}
		getchar();
	}

	bfs(start);

	int mv = (1<<16)-1;
	if(pathLength[0] == -1 && pathLength[mv] == -1)
		puts("Impossible");
	else if(pathLength[0] == -1 || pathLength[mv] == -1)
		printf("%d",max(pathLength[0], pathLength[mv]));
	else
		printf("%d",min(pathLength[0], pathLength[mv]));
}