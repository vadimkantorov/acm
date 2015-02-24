#include <iostream>
#include <queue>

using namespace std;
struct Graph
{
	#define MAXV 101
	#define MAXDEGREE MAXV
	#define ERROR 1
	int nvertices;
	int nedges;
	int edges[MAXV][MAXDEGREE];
	int degree[MAXV];
	Graph(int n)
	{
		nvertices = n;
		nedges = 0;
		for(int i = 1; i < MAXV; i++)
		{
			degree[i] = 0;
		}
	}
	void insertedge(int v, int u)
	{
		//if(v < 0 || v >= nvertices || u < 0 || u >= nvertices || v == u)
		//	return ERROR;
		edges[v][degree[v]] = u;
		degree[v]++;
		nedges++;
	}
};

void compute_indegrees(Graph& g, int in[])
{
	for (int i = 1; i <= g.nvertices; i++) 
		in[i] = 0;
	
	for (int i = 1; i <= g.nvertices; i++)
		for (int j = 0; j < g.degree[i]; j++) 
			in[ g.edges[i][j] ] ++;
}


void topsort(Graph& g)
{
	int x,in[MAXV];
	compute_indegrees(g,in);
	queue<int> zeroin;
	for(int i = 1; i <= g.nvertices; i++)
		if(in[i] == 0)
			zeroin.push(i);
	while(!zeroin.empty())
	{
		x = zeroin.front();
		zeroin.pop();
		printf("%d ",x);
		for(int i = 0; i < g.degree[x]; i++)
		{
			in[g.edges[x][i]]--;
			if(in[g.edges[x][i]] == 0)
				zeroin.push(g.edges[x][i]);
		}
	}
}

void main()
{
	int n,t;
	cin >> n;
	Graph g(n);
	for(int i = 1; i <= n; i++)
	{
		while(true)
		{
			cin>>t;
			if(t == 0)
				break;
			g.insertedge(i,t);
		}
	}
	topsort(g);
}