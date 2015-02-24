#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

enum RelationType
{
	Child,
	Parent
};

struct Edge
{
	int Vertex;
	RelationType Type;
};

struct Graph
{
	vector<Edge> M[1002];
	bool visited[1002];

	Graph()
	{
		fill(visited, visited+1002, false);
	}

	void AddEdge(int u, int v)
	{
		Edge e1 = {v,Parent}, e2 = {u,Child};
		
		M[u].push_back(e1);
		M[v].push_back(e2);
	}

	void DFS(int start, RelationType type)
	{
		//if(!visited[start])
		{
			visited[start] = true;
			for(int i = 0; i < M[start].size(); i++)
				if(!visited[M[start][i].Vertex] && M[start][i].Type == type)
					DFS(M[start][i].Vertex, type);
		}
	}

	void PrintSuspects(int n)
	{
		bool printed = false;
		for(int i = 0; i < n; i++)
			if(!visited[i])
			{
				printf("%d ", i+1);
				printed = true;
			}
		if(!printed)
			putchar('0');
	}
};

Graph g;

void main()
{
	freopen("input.txt", "r", stdin);

	int n;
	scanf("%d",&n);
	while(true)
	{
		int u, v;
		if(scanf("%d %d",&u, &v) <= 0)
			break;
		g.AddEdge(u-1,v-1);
	}
	scanf("BLOOD\n");
	while(true)
	{
		int ver;
		if(scanf("%d",&ver) <= 0)
			break;
		g.DFS(ver-1, Parent);
		g.DFS(ver-1, Child);
	}
	g.PrintSuspects(n);
}