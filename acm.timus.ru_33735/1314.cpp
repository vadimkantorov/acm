#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#define N 33000
#define INF 1000000000
using namespace std;

bool vertices[N];

struct Graph
{
	vector<int> M[N];
	bool visited[N];
	int D1[N], D2[N];

	void AddEdge(int u, int v)
	{
		M[u].push_back(v);
		M[v].push_back(u);
	}

	void BFS(int start, int* dist)
	{
		fill(dist, dist + N, INF);
		fill(visited, visited + N, false);
		dist[start] = 0;
		visited[start] = true;

		queue<int> Q;
		Q.push(start);

		while(!Q.empty())
		{
			int ver = Q.front();
			Q.pop();

			for(int i = 0; i < M[ver].size(); i++)
			{
				if(!visited[M[ver][i]])
				{
					visited[M[ver][i]] = true;
					dist[M[ver][i]] = dist[ver] + 1;
					Q.push(M[ver][i]);
				}
			}
		}
	}

	void PrintAnswer(int first, int last)
	{
		BFS(first, D1);
		BFS(last, D2);

		for(int i = 1; i < N; i++)
			if(vertices[i] && D1[i] == D1[last] + D2[i])
				printf("%d\n", i);
	}
};

Graph g;

void main()
{
	//freopen("input.txt", "r", stdin);
	
	int n, m, k, next, first, last;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
	{
		int prev = -1;
		
		scanf("%d",&k);
		for(int i = 0; i < k; i++)
		{
			scanf("%d",&next);
			if(prev != -1)
				g.AddEdge(prev,next);
			vertices[next] = true;
			prev = next;
		}
	}
	scanf("%d",&m);
	scanf("%d",&first);
	vertices[first] = true;
	last = first;
	for(int i = 1; i < m; i++)
	{
		scanf("%d",&last);
		vertices[next] = true;
	}

	g.PrintAnswer(first, last);
}