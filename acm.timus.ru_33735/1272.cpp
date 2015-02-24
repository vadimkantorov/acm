#include <cstdio>
#include <vector>
using namespace std;


struct Graph
{
	const static int NMAX = 10002;
	vector<int> M[NMAX];
	bool visited[NMAX];

	void AddEdge(int u, int v)
	{
		M[u].push_back(v);
		M[v].push_back(u);
	}

	void DFS(int start)
	{
		visited[start] = true;
		for(int i = 0; i < M[start].size(); i++)
			if(!visited[M[start][i]])
				DFS(M[start][i]);
	}

	int GetConnectedComponentsCount(int n)
	{
		for(int i = 1; i <= n; i++)
			visited[i] = false;
		int comp = 0;
		for(int i = 1; i <= n; i++)
		{
			if(!visited[i])
			{
				comp++;
				DFS(i);
			}
		}
		return comp;
	}
};

Graph g;

void main()
{
	//freopen("input.txt","r",stdin);

	int n,k;
	scanf("%d%d%d",&n,&k);
	for(int i = 0; i < k; i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		g.AddEdge(u,v);
	}
	printf("%d",g.GetConnectedComponentsCount(n) - 1);
}