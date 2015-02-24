#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define N 103

enum State
{
	EVEN,
	ODD,
	NOTVISITED
};

struct Graph
{
	vector<int> X[N];
	int V;
	Graph(){}
	Graph(int V):V(V){}

	void AddVertex(int v, int w)
	{
		if(find(X[v].begin(),X[v].end(),w) == X[v].end())
			X[v].push_back(w);
		if(find(X[w].begin(),X[w].end(),v) == X[w].end())
			X[w].push_back(v);
	}
};
State states[N];

void bfs(Graph& g, int start)
{
	states[start] = ODD;
	queue<int> Q;
	Q.push(start);
	int v;
	while(!Q.empty())
	{
		v = Q.front();
		Q.pop();
		for(int i = 0; i < g.X[v].size(); i++)
		{
			if(states[g.X[v][i]] == NOTVISITED)
			{
				if(states[v] == EVEN)
					states[g.X[v][i]] = ODD;
				else
					states[g.X[v][i]] = EVEN;
				Q.push(g.X[v][i]);
			}
		}
	}
}


void main()
{
	//freopen("input.txt","r",stdin);
	
	for(int i = 0; i < N; i++)
		states[i] = NOTVISITED;

	Graph g;
	scanf("%d",&g.V);
	if(g.V == 1)
		puts("0");
	else
	{
		int x;
		for(int i = 1; i <= g.V; i++)
		{
			while(true)
			{
				scanf("%d",&x);
				if(x == 0)
					break; 
				g.AddVertex(i,x);
			}
		}

		for(int i = 1; i < g.V; i++)
		{
			if(states[i] == NOTVISITED)
				bfs(g,i);
		}
		vector<int> team;
		for(int i = 1; i <= g.V; i++)
			if(states[i] == ODD)
				team.push_back(i);

		printf("%d\n",team.size());
		for(int i = 0; i < team.size(); i++)
			printf("%d ",team[i]);
	}
}