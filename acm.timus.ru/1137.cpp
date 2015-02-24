#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>
#define N 10002
using namespace std;

struct Graph
{
	vector<int> M[N];
	int I[N], O[N];

	Graph()
	{
		fill(O, O + N, 0);
		fill(I, I + N, 0);
	}

	void AddEdge(int u, int v)
	{
		if(find(M[u].begin(), M[u].end(), v) == M[u].end())
		{
			M[u].push_back(v);
			O[u]++;
			I[v]++;
		}
	}

	void DeleteEdge(int u, int v)
	{
		M[u].erase(find(M[u].begin(), M[u].end(), v));
	}

	bool IsEulerian()
	{
		for(int i = 0; i < N; i++)
			if(I[i] != O[i])
				return false;
		return true;
	}

	void PrintEulerianCycle(int start)
	{
		stack<int> vers, result;
		vers.push(start);
		while(!vers.empty())
		{
			int ver = vers.top();
			if(!M[ver].empty())
			{
				int v = M[ver][0];
				vers.push(v);
				DeleteEdge(ver,v);
			}
			else
			{
				vers.pop();
				result.push(ver);
			}
		}

		printf("%d ",result.size()-1);
		while(!result.empty())
		{
			printf("%d ",result.top());
			result.pop();
		}
	}
};

Graph g;

void main()
{
	//freopen("input.txt", "r", stdin);
	
	int n, prev, tmp, m;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
	{
		prev = -1;
		scanf("%d",&m);
		for(int i = 0; i < m+1; i++)
		{
			scanf("%d",&tmp);
			if(prev != -1)
				g.AddEdge(prev, tmp);
			prev = tmp;
		}
	}
	if(g.IsEulerian())
		g.PrintEulerianCycle(prev);
	else
		putchar('0');
}