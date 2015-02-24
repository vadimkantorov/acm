#include <cstdio>

bool fail;

struct Graph
{
	int M[25003];
	bool visited[25003];
	bool discovered[25003];
	int v;
	Graph() : v(0){}

	void dfs(int start)
	{
		discovered[start] = true;
		if(M[start] != 0)
		{
			if(!visited[M[start]])
			{
				if(discovered[M[start]])
					fail = true;
				else
					dfs(M[start]);
			}
		}
		visited[start] = true;
	}
	bool yes()
	{
		fail = false;
		for(int i = 1; i <= v; i++)
		{
			visited[i] = false;
			discovered[i] = false;
		}
		for(int i = 1; i <= v; i++)
		{
			if(!visited[i])
				dfs(i);
		}
		return !fail;
	}
};

void main()
{
	//freopen("input.txt","r",stdin);
	
	int T;
	scanf("%d",&T);
	for(int i = 0; i < T; i++)
	{
		int n;
		scanf("%d",&n);
		Graph g;
		int traitors = 0;
		for(int i = 1; i <= n; i++)
		{
			scanf("%d",&g.M[i]);
			if(g.M[i] == 0)
				traitors++;
			g.v++;
		}
		if( traitors == 1 && g.yes() )
			puts("YES");
		else
			puts("NO");
	}
}