#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

#define INF 1000000000

int Values[6];

const int N = 8;
int M[][4] = {{0,0,-1,1},{1,-1,0,0}};
int Map[] = {1,2,6,4};
int R[][6] = {/*NORTH*/{3,5,2,4,1,6},/*SOUTH*/{5,3,1,4,2,6},/*WEST*/{1,2,4,5,6,3},/*EAST*/{1,2,6,3,4,5}};
int Me[][6] = {{1,2,3,4,5,6},{6,4,3,1,5,2},{2,1,3,6,5,4},{4,6,3,2,5,1},
				{1,2,5,6,3,4},{4,6,5,1,3,2},{2,1,5,4,3,6},{6,4,5,2,3,1},
				{1,2,4,5,6,3},{3,5,4,1,6,2},{2,1,4,3,6,5},{5,3,4,2,6,1},
				{1,2,6,3,4,5},{5,3,6,1,4,2},{2,1,6,5,4,3},{3,5,6,2,4,1},
				{4,6,2,5,1,3},{3,5,2,4,1,6},{6,4,2,3,1,5},{5,3,2,6,1,4},
				{6,4,1,5,2,3},{3,5,1,6,2,4},{4,6,1,3,2,5},{5,3,1,4,2,6}
};

//0 - forward
//1 - backward
//2 - top
//3 - right
//4 - bottom
//5 - left

struct Coords
{
	int X,Y,Direction;
	
	Coords()
	{
		X = -1;
		Y = -1;
		Direction = -1;
	}

	bool IsCorrect()
	{
		return X >= 0 && Y >= 0 && X < 8 && Y < 8;
	}

	void FillNewCoords(Coords* NewCoords)
	{
		for(int i = 0; i < 4; i++)
		{
			NewCoords[i].X = X + M[0][i];
			NewCoords[i].Y = Y + M[1][i];
			int tmp[6];
			
			for(int j = 0; j < 6; j++)
				tmp[j] = Me[Direction][R[i][j]-1];
			for(int j = 0; j < 24; j++)
				if(memcmp(tmp,Me[j],6*sizeof(int)) == 0)
				{
					NewCoords[i].Direction = j;
					break;
				}
		}
	}
};

struct Cube
{
	Coords Coordinates;
	Coords Parent;
	int PathLength;
	bool Finished;

	bool operator<(const Cube& r) const
	{
		return (PathLength > r.PathLength);
	}
};

Cube Cubes[N][N][25];

void Dijkstra(Coords& start)
{
	for(int i = 0; i < N; i++)
		for(int j = 0; j < N; j++)
			for(int k = 0; k < 24; k++)
			{
				Cubes[i][j][k].PathLength = INF;
				Cubes[i][j][k].Finished = false;
				Cubes[i][j][k].Coordinates.X = i;
				Cubes[i][j][k].Coordinates.Y = j;
				Cubes[i][j][k].Coordinates.Direction = k;
			}
	Cubes[start.X][start.Y][start.Direction].PathLength = Values[4];
	Cubes[start.X][start.Y][start.Direction].Coordinates = start;
	priority_queue<Cube> vers;
	vers.push(Cubes[start.X][start.Y][start.Direction]);
	Coords NewCoords[4];
	while(!vers.empty())
	{
		Cube c = vers.top();
		vers.pop();
		if(!Cubes[c.Coordinates.X][c.Coordinates.Y][c.Coordinates.Direction].Finished)
		{
			c.Finished = true;
			Cubes[c.Coordinates.X][c.Coordinates.Y][c.Coordinates.Direction] = c;
			c.Coordinates.FillNewCoords(NewCoords);
			for(int i = 0; i < 4; i++)
			{
				if(NewCoords[i].IsCorrect())
				{
					Cube cb = Cubes[NewCoords[i].X][NewCoords[i].Y][NewCoords[i].Direction];
					if(!cb.Finished)
					{
						cb.Parent = c.Coordinates;
						cb.PathLength = c.PathLength + Values[Me[c.Coordinates.Direction][Map[i]-1]-1];
						vers.push(cb);
					}
				}
			}
		}
	}
}

void Print(Coords c)
{
	if(Cubes[c.X][c.Y][c.Direction].Parent.Direction != -1)
		Print(Cubes[c.X][c.Y][c.Direction].Parent);
	printf("%c%d ",'a'+c.X,c.Y+1);
}

void main()
{
	//freopen("input.txt","r",stdin);
	
	char x1,x2;
	Coords start,end;
	scanf("%c%d %c%d",&x1,&start.Y,&x2,&end.Y);
	start.X = x1 - 'a';
	start.Y--;
	end.X = x2 - 'a';
	end.Y--;
	for(int i = 0; i < 6; i++)
		scanf("%d",&Values[i]);
	swap(Values[0],Values[1]);
	start.Direction = 0;
	Dijkstra(start);
	int mindir = 0;
	for(int i = 0; i < 24; i++)
	{
		if(Cubes[end.X][end.Y][i].PathLength < Cubes[end.X][end.Y][mindir].PathLength)
			mindir = i;
	}
	printf("%d ",Cubes[end.X][end.Y][mindir].PathLength);
	Print(Cubes[end.X][end.Y][mindir].Coordinates);
}