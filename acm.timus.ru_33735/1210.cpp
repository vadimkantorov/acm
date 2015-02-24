#include <cstdio>
#include <vector>
using namespace std;

struct Edge
{
	int Vertex;
	int Weight;
};

struct Graph
{
	static const int MAXN = 902;
	static const int INF = 1000000000;
	vector<Edge> M[MAXN];
	
	int D[MAXN];
	void AddEdge(int v,Edge e)
	{
		M[v].push_back(e);
	}

	void Relax(int u, int v, int w)
	{
		int newd = D[u] + w;
		if(newd < D[v])
			D[v] = newd;
	}

	int DagShortestPaths(int n,int source, int k)
	{
		for(int i = 0; i < MAXN; i++)
			D[i] = INF;
		D[source] = 0;
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < M[i].size(); j++)
				Relax(i,M[i][j].Vertex,M[i][j].Weight);
		}
		int min = INF;
		for(int i = n-k; i < n; i++)
			if(D[i] < min)
				min = D[i];
		return min;
	}
};

Graph g;

void main()
{
	//freopen("input.txt","r",stdin);
	
	int levels;
	scanf("%d",&levels);

	int lastIDs[30], newIDs[30];
	lastIDs[0] = 0;
	int planets = 0, maxt;
	for(int i = 0; i < levels; i++)
	{
		int curPls;
		scanf("%d",&curPls);
		if(i == levels-1)
			maxt = curPls;
		for(int j = 0; j < curPls; j++)
		{
			newIDs[j] = ++planets;
			Edge e;
			while(true)
			{
				int parent;
				scanf("%d",&parent);
				if(parent == 0) break;
				
				e.Vertex = newIDs[j];
				scanf("%d",&e.Weight);
				g.AddEdge(lastIDs[parent-1],e);
			}
		}
		for(int j = 0; j < 30; j++)
			lastIDs[j] = newIDs[j];
		scanf("\n*\n");
	}
	printf("%d",g.DagShortestPaths(planets+1,0,maxt));
}