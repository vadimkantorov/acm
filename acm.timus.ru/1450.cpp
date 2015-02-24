#include <cstdio>
#include <vector>
#include <algorithm>
#define N 502
#define INF 1000000000
using namespace std;

struct Graph
{
	int M[N][N];
	int RealD[N];
	int D[N];

	Graph()
	{
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				M[i][j] = INF;
	}

	void AddEdge(int u, int v, int weight)
	{
		M[u][v] = weight;
	}
	
	bool visited[N];
	vector<int> ret;
	void DFS(int start)
	{
		visited[start] = true;
		for(int i = 0; i < N; i++)
		{
			if(M[start][i] != INF && !visited[i])
				DFS(i);
		}
		ret.push_back(start);
	}

	vector<int> Topological_Sort(int n)
	{
		for(int i = 0; i < N; i++)
			visited[i] = false;
		for(int i = 0; i < n; i++)
			if(!visited[i])
				DFS(i);
		reverse(ret.begin(), ret.end());
		return ret;
	}

	void Relax(int u, int v, int w)
	{
		int newd = D[u] + (-w);
		if(newd < D[v])
		{
			D[v] = newd;
			RealD[v] = RealD[u] + w;
		}
	}

	int DAG_Shortest_Paths(int source,  int end, int n)
	{
		for(int i = 0; i < N; i++)
			D[i] = RealD[i] = INF;
	
		D[source] = RealD[source] = 0;

		vector<int> order = Topological_Sort(n);
		for(int i = 0; i < order.size(); i++)
			for(int j = 0; j < n; j++)
				if(M[order[i]][j] != INF)
					Relax(order[i], j, M[order[i]][j]);
		return RealD[end];
	}
};

Graph g;

void main()
{
	freopen("input.txt","r",stdin);

	int n, m, source, end;
	scanf("%d%d",&n,&m);
	for(int i = 0; i < m; i++)
	{
		int a,b,w;
		scanf("%d%d%d",&a, &b, &w);
		g.AddEdge(a-1,b-1,w);
	}
	scanf("%d%d",&source,&end);
	int d = g.DAG_Shortest_Paths(source-1,end-1,n);
	if(d >= INF)
		puts("No solution");
	else
		printf("%d",d);
}