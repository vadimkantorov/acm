#include <cstdio>
#include <queue>
#define MAX 12

bool mas[MAX][MAX];

struct ver
{
	int x,y;
};

void BFS1(int x, int y, bool visited[MAX][MAX])
{
	int matr[2][4] = {{1,0,-1,0},{0,1,0,-1}};
	char* names[4] = {"R","T","L","B"};
	std::queue<ver> vers;
	
	ver tmp = {x, y};
	vers.push(tmp);
	visited[tmp.x][tmp.y] = true;
		
	while(!vers.empty())
	{
		ver v = vers.front();
		vers.pop();
		
		for(int i = 0; i < 4; i++)
		{
			tmp.x = v.x + matr[0][i];
			tmp.y = v.y + matr[1][i];
			if(!visited[tmp.x][tmp.y])
			{
				vers.push(tmp);
				visited[tmp.x][tmp.y] = true;
				printf(names[i]);
			}
		}
		if(vers.empty())
			printf(".");
		else
			printf(",");
		printf("\n");
	}
}

int BFS2(int x, int y)
{
	std::queue<ver> vers;
	
	ver tmp = {x, y};
	vers.push(tmp);
	char str[5];
	int dx,dy,len,count;
	while(!vers.empty())
	{
		ver v = vers.front();
		mas[v.x][v.y] = true;
		count++;
		vers.pop();
		gets(str);
		len = strlen(str);
		for(int i = 0; i < len-1; i++)
		{
			switch(str[i])
			{
			case 'R':
				dx = 1;
				dy = 0;
				break;
			case 'T':
				dx = 0;
				dy = 1;
				break;
			case 'L':
				dx = -1;
				dy = 0;
				break;
			case 'B':
				dx = 0;
				dy = -1;
				break;
			}
			tmp.x = v.x + dx;
			tmp.y = v.y + dy;
			vers.push(tmp);
		}
	}
	return count;
}

int main()
{
	//freopen("input.txt", "r", stdin);
	char C[20];
	gets(C);
	int a,b;
	if(sscanf(C,"%d %d",&a,&b) == 1)
	{
		int n = a, min_x = MAX, min_y = MAX, x, y;
		
		bool visited[MAX][MAX];
		
		for(x = 0; x < MAX; x++)
			for(y = 0; y < MAX; y++)
				visited[x][y] = true;

		for(int i = 0; i < n; i++)
		{
			scanf("%d %d", &x, &y);
			if(i == 0)
			{
				min_x = x;
				min_y = y;
			}
			mas[x][y] = true;
			visited[x][y] = false;
		}
		printf("%d %d\n", min_x, min_y);
		BFS1(min_x, min_y,visited);
	}
	else
	{
		int x = a, y = b;
		
		int count = BFS2(x,y);
		printf("%d\n",count);
		for(int x = 1; x < MAX; x++)
		{
			for(int y = 1; y < MAX; y++)
			{
				if(mas[x][y])
					printf("%d %d\n",x,y);
			}
		}
	}
	return 0;
}