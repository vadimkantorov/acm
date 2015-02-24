#pragma comment(linker, "/STACK:16777216")
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#define N 50002
using namespace std;

struct Edge
{
	int Vertex;
	int Weight;
	int From;
};

Edge input[N];
int n;

struct Graph
{
	vector<Edge> M[N];
	bool visited[N];
	int P[N], F[N];

	Graph()
	{
		for(int i = 0; i < n; i++)
		{
			visited[i] = false;
			P[i] = -1;
			F[i] = 0;
		}
	}

	void AddEdge(int u, int v, int w)
	{
		Edge e1 = {u,w}, e2 = {v,w};
		
		M[u].push_back(e2);
		M[v].push_back(e1);
	}
	
	void DFS(int start)
	{
		visited[start] = true;
		for(int i = 0; i < M[start].size(); i++)
			if(!visited[M[start][i].Vertex])
			{
				P[M[start][i].Vertex] = start;
				DFS(M[start][i].Vertex);
			}
		int tmp = 0;
		for(int i = 0; i < M[start].size(); i++)
		{
			int u = M[start][i].Vertex;
			if(P[start] != u)
				tmp += F[u];
		}
		F[start] = tmp+M[start].size();
		if(P[start] != -1)
			F[start]--;
	}

	double GetSum()
	{
		DFS(0);
		double sum = 0;
		for(int i = 0; i < n-1; i++)
		{
			int u = input[i].From, v = input[i].Vertex, w = input[i].Weight;
			if(P[u] == v)
				swap(u,v);
			int uvers = n-F[v]-1;
			sum += 2.0*uvers*(F[v]+1)*w/n/(n-1);
		}
		return sum;
	}
};

Graph g;

void main()
{
	//freopen("input.txt", "r", stdin);
	
	scanf("%d",&n);
	for(int i = 0; i < n-1; i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		g.AddEdge(u-1,v-1,w);
		input[i].From = u-1;
		input[i].Vertex = v-1;
		input[i].Weight = w;
	}

	printf("%.15lf",g.GetSum());
}