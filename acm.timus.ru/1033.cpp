#include <cstdio>
#include <algorithm>
#define N 36
using namespace std;

int n, sum;
bool ishouse[N][N], visited[N][N], counted[N][N][4];

void DFS(int x0, int y0)
{
	int dx[] = {0,0,1,-1};
	int dy[] = {1,-1,0,0};

	visited[x0][y0] = true;
	for(int i = 0; i < 4; i++)
	{
		int x = x0 + dx[i];
		int y = y0 + dy[i];

		if(ishouse[x][y])
		{
			if(!counted[x][y][i])
			{
				sum++;
				counted[x][y][i] = true;
			}
		}
		else if(!visited[x][y])
			DFS(x,y);
	}
}

void main()
{
	//freopen("input.txt","r",stdin);
	
	scanf("%d\n",&n);

	fill((bool*)ishouse,(bool*)(ishouse) + N*N, true);
	ishouse[0][0] = ishouse[0][1] = ishouse[1][0] = ishouse[n+1][n+1] = ishouse[n][n+1] = ishouse[n+1][n] = false;
	visited[0][0] = visited[0][1] = visited[1][0] = visited[n+1][n+1] = visited[n][n+1] = visited[n+1][n] = true;
	
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
			ishouse[j][i] = (getchar() == '#');
		getchar();
	}

	DFS(1,1);
	DFS(n,n);

	printf("%d",sum*9);
}