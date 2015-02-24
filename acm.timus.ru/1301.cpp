#include <cstdio>
#include <queue>
#include <set>
using namespace std;

struct Point
{
	int X,Y;
	Point(){}
	Point(int _x, int _y):X(_x),Y(_y){}
	bool operator<(Point p) const
	{
		if(X != p.X)
			return (X < p.X);
		return (Y < p.Y);
	}
};

int M[][4] = {{0,0,1,-1},{1,-1,0,0}};
int R[][6] = {/*NORTH*/{4,1,2,3,5,6},/*SOUTH*/{2,3,4,1,5,6},/*WEST*/{6,2,5,4,1,3},/*EAST*/{5,2,6,4,3,1}};
set<Point> hwalls;
set<Point> vwalls;

struct Cube
{
	int Distance;
	int Sides[6];
	Point Position;
};
bool visited[12][12][7][7];
int BFS(int a,int b, int C, int d, int x, int y)
{
	Cube start;
	start.Position.X = a;
	start.Position.Y = b;
	start.Distance = 0;
	for(int i = 0; i < 6; i++) start.Sides[i] = i+1;
	
	queue<Cube> vers;
	vers.push(start);
	visited[start.Position.X][start.Position.Y][start.Sides[0]-1][start.Sides[5]-1] = true;
	while(!vers.empty())
	{
		Cube c = vers.front();
		vers.pop();
		for(int i = 0; i < 4; i++)
		{
			Cube tmp;
			tmp.Position = Point(c.Position.X + M[0][i], c.Position.Y + M[1][i]);
			tmp.Distance = c.Distance + 1;
			for(int j = 0; j < 6; j++)
				tmp.Sides[R[i][j]-1] = c.Sides[j];
			bool pushed = false;
			if(tmp.Position.X <= x && tmp.Position.Y <= y && tmp.Position.X > 0 && tmp.Position.Y > 0)
			{
				if(!visited[tmp.Position.X][tmp.Position.Y][tmp.Sides[0]-1][tmp.Sides[5]-1])
				{
					if(i == 0 && hwalls.find(c.Position) == hwalls.end())
					{
						vers.push(tmp);
						pushed = true;
					}
					else if(i == 1 && hwalls.find(Point(c.Position.X,c.Position.Y-1)) == hwalls.end())
					{
						vers.push(tmp);
						pushed = true;
					}
					else if(i == 2 && vwalls.find(c.Position) == vwalls.end())
					{
						vers.push(tmp);
						pushed = true;
					}
					else if(i == 3 && vwalls.find(Point(c.Position.X-1, c.Position.Y)) == vwalls.end())
					{
						vers.push(tmp);
						pushed = true;
					}
					if(pushed)
					{
						visited[tmp.Position.X][tmp.Position.Y][tmp.Sides[0]-1][tmp.Sides[5]-1] = true;
						if(tmp.Position.X == C && tmp.Position.Y == d)
						{
							if(tmp.Sides[2] == start.Sides[2]) return tmp.Distance;
						}
					}
				}
			}
		}
	}
	return -1;
}

void main()
{
	freopen("input.txt","r",stdin);
	
	int x,y,a,b,c,d;
	scanf("%d%d%d%d%d%d",&x,&y,&a,&b,&c,&d);
	char ch;
	while((ch = getchar()) != 'v');
	while(true)
	{
		Point p;
		int ret = scanf("%d%d",&p.X,&p.Y);
		if(ret < 2) break;
		vwalls.insert(p);
	}
	getchar();getchar();
	while(true)
	{
		Point p;
		int ret = scanf("%d%d",&p.X,&p.Y);
		if(ret < 2) break;
		hwalls.insert(p);
	}
	int ret = BFS(a,b,c,d,x,y);
	if(ret != -1)
		printf("%d",ret);
	else
		puts("No solution");
}