#include <cstdio>
#include <vector>
#include <algorithm>
#define N 1002
#define INF 1000000000
using namespace std;

struct Graph
{
	int P[N], M[N][N], E[N];
	bool Finished[N];

	Graph()
	{
		for(int i = 0; i < N; i++)
		{
			Finished[i] = false;
			P[i] = -1;
			E[i] = INF;
		}
		fill((int*)M, (int*)(M)+N*N,INF);
	}


	void AddEdge(int u, int v, int w)
	{
		M[u][v] = w;
		M[v][u] = w;
	}

	void Prim(int start, int n)
	{
		E[start] = 0;
		int maxweight = -1;

		while(true)
		{
			int to = -1;
			for(int i = 0; i < n; i++)
			{
				if(!Finished[i] && (to == -1 || E[i] < E[to]))
					to = i;
			}

			if(to == -1)
				break;

			Finished[to] = true;
			if(P[to] == -1 || M[to][P[to]] > maxweight)
				maxweight = M[to][P[to]];

			for(int i = 0; i < n; i++)
				if(!Finished[i] && M[to][i] < INF)
					if(M[to][i] < E[i])
					{
						E[i] = M[to][i];
						P[i] = to;
					}
		}
		printf("%d\n",maxweight);
		int count = 0;
		for(int i = 0; i < n; i++)
			if(Finished[i] && (P[i] != -1 && Finished[P[i]]))
				count++;
		printf("%d\n",count);
		for(int i = 0; i < n; i++)
			if(Finished[i] && (P[i] != -1 && Finished[P[i]]))
				printf("%d %d\n",i+1,P[i]+1);
	}
};

Graph g;

void main()
{
	//freopen("input.txt","r",stdin);

	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 0; i < m; i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		g.AddEdge(u-1,v-1,w);
	}
	g.Prim(0,n);
}