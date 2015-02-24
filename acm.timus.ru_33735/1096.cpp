#include <cstdio>
#include <utility>
#include <queue>
#include <stack>
#define N 1005
using namespace std;

pair<int,int> input[N];

struct Graph
{
	bool M[N][N], visited[N];
	int L[N], P[N];

	void AddEdge(int u, int v)
	{
		M[u][v] = true;
	}

	void BFS(int start, int route)
	{
		for(int i = 0; i < N; i++)
		{
			visited[i] = false;
			L[i] = 0;
			P[i] = -1;
		}
		visited[start] = true;

		queue<int> vers;
		vers.push(start);

		while(!vers.empty())
		{
			int v = vers.front();
			vers.pop();

			for(int i = 0; i < N; i++)
			{
				if(M[v][i] && !visited[i])
				{
					visited[i] = true;
					P[i] = v;
					L[i] = L[v] + 1;
					vers.push(i);
				}
			}
		}
	}
};

Graph g;

void main()
{
	//freopen("input.txt", "r", stdin);
	
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
	{
		int num, oppnum;
		scanf("%d%d",&num, &oppnum);
		input[i] = pair<int,int>(num, oppnum);
	}
	int route,a,b;
	scanf("%d%d%d",&route,&a,&b);
	input[n] = pair<int,int>(a,b);
	for(int i = 0; i <= n; i++)
	{
		for(int j = 0; j <= n; j++)
		{
			if(i != j)
			{
				if(input[i].first == input[j].first || input[i].second == input[j].first)
					g.AddEdge(i,j);
			}
		}
	}
	g.BFS(n, route);
	int last = -1;
	for(int i = 0; i < n; i++)
		if(input[i].first == route || input[i].second == route)
			if(g.P[i] != -1 && (last == -1 || g.L[i] < g.L[last]))
				last = i;
	
	if(last == -1)
	{
		puts("IMPOSSIBLE");
		return;
	}

	stack<int> ret;
	ret.push(last);
	while(g.P[last] != n)
	{
		ret.push(g.P[last]);
		last = g.P[last];
	}
	printf("%d\n",ret.size());
	while(!ret.empty())
	{
		printf("%d\n",ret.top()+1);
		ret.pop();
	}
}