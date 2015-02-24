#include <queue>
#include <cstdio>
#define INF 1000000000000000000
using namespace std;

int M[2][3] = {{-1,0,1},{0,1,0}};

struct Official
{
	int Fee;

	unsigned __int64 PathLength;
	bool Finished;

	int RoomNumber;
	int FloorNumber;

	int ParentRoomNumber;
	int ParentFloorNumber;

	bool operator<(const Official& r) const
	{
		return (PathLength > r.PathLength);
	}
};

int m,n;
Official Officials[102][502];

void Dijkstra()
{
	priority_queue<Official> vers;
	for(int i = 0; i < n; i++)
	{
		Officials[0][i].PathLength = Officials[0][i].Fee;
		vers.push(Officials[0][i]);
	}
	while(!vers.empty())
	{
		Official off = vers.top();
		vers.pop();
		if(!Officials[off.FloorNumber][off.RoomNumber].Finished)
		{
			off.Finished = true;
			Officials[off.FloorNumber][off.RoomNumber] = off;
			
			for(int i = 0; i < 3; i++)
			{
				int floor = off.FloorNumber + M[1][i];
				int room = off.RoomNumber + M[0][i];
				
				if(floor >= 0 && floor < m && 
					room >= 0 && room < n)
				{
					Official aux = Officials[floor][room];
					if(!aux.Finished)
					{
						aux.PathLength = off.PathLength + aux.Fee;
						aux.ParentFloorNumber = off.FloorNumber;
						aux.ParentRoomNumber = off.RoomNumber;
						vers.push(aux);
					}
				}
			}
		}
	}
}

void Print(int floor, int room)
{
	Official off = Officials[floor][room];
	if(off.ParentFloorNumber != -1)
		Print(off.ParentFloorNumber, off.ParentRoomNumber);
	printf("%d\n",off.RoomNumber + 1);
}

void main()
{
	//freopen("input.txt","r",stdin);
	
	scanf("%d%d",&m,&n);
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
		{
			scanf("%d",&Officials[i][j].Fee);
			Officials[i][j].FloorNumber = i;
			Officials[i][j].RoomNumber = j;
			Officials[i][j].PathLength = INF;
			Officials[i][j].Finished = false;
			Officials[i][j].ParentRoomNumber = Officials[i][j].ParentFloorNumber = -1;
		}
	Dijkstra();

	int mini = 0;
	for(int i = 0; i < n; i++)
		if(Officials[m-1][i].PathLength < Officials[m-1][mini].PathLength)
			mini = i;
	Print(m-1,mini);
}