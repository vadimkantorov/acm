#include <cstdio>
#include <cmath>
#include <algorithm>
#define INF 1000000000
using namespace std;

int Ls[3],Cs[3];
int n;

struct Station
{
	int Distance;
	int PathLength;
};

Station Stations[10002];

void main()
{
	//freopen("input.txt","r",stdin);
	
	for(int i = 0; i < 3; i++) scanf("%d",&Ls[i]);
	for(int i = 0; i < 3; i++) scanf("%d",&Cs[i]);
	int source, sink;
	scanf("%d%d%d",&n,&source,&sink);
	
	Stations[0].PathLength = INF;
	for(int i = 1; i < n; i++)
	{
		scanf("%d",&Stations[i].Distance);
		Stations[i].PathLength = INF;
	}

	if(sink < source)
		swap(sink, source);
	source--;
	sink--;
	Stations[source].PathLength = 0;
	
	
	for(int v = source; v <= sink; v++)
	{
		for(int w = v+1; w <= sink; w++)
		{
			int cost = -1;
			for(int i = 0; i < 3; i++)
			{
				if(abs(Stations[v].Distance-Stations[w].Distance) <= Ls[i])
				{
					cost = Cs[i];
					break;
				}
			}
			if(cost != -1)
			{
				int newcost = Stations[v].PathLength + cost;
				if(newcost < Stations[w].PathLength)
					Stations[w].PathLength = newcost;
			}
		}
	}

	printf("%d",Stations[sink].PathLength);
}