#include <cstdio>
#include <vector>
using namespace std;
struct Jedi
{
	int a,b,c;
	bool visited;
	char name[32];
	vector<int> adj;
};

struct Graph
{
	Jedi vers[502];
	int v;

	Graph():v(0) {}
	void AddJedi(Jedi j)
	{
		vers[v++] = j;
	}
	void FillRelations()
	{
		for(int i = 0; i < v; i++)
			for(int j = i+1; j < v; j++)
			{
				if(vers[i].a > vers[j].a && vers[i].b > vers[j].b)
				{
					vers[i].adj.push_back(j);
					continue;
				}

				if(vers[i].a > vers[j].a && vers[i].c > vers[j].c)
				{
					vers[i].adj.push_back(j);
					continue;
				}

				if(vers[i].b > vers[j].b && vers[i].c > vers[j].c)
				{
					vers[i].adj.push_back(j);
					continue;
				}

				vers[j].adj.push_back(i);
			}
	}

	void dfs(int start)
	{
		vers[start].visited = true;
		for(int i = 0; i < vers[start].adj.size(); i++)
			if(!vers[vers[start].adj[i]].visited)
				dfs(vers[start].adj[i]);
	}

	bool CanReach(int u)
	{
		for(int i = 0; i < v; i++)
			vers[i].visited = false;
		dfs(u);
		for(int i = 0; i < v; i++)
			if(!vers[i].visited)
				return false;
		return true;
	}
};

void main()
{
	//freopen("input.txt","r",stdin);
	
	int n;
	scanf("%d",&n);
	Graph g;
	Jedi tmp;
	for(int i = 0; i < n; i++)
	{
		scanf("%s %d %d %d",tmp.name, &tmp.a, &tmp.b, &tmp.c);
		g.AddJedi(tmp);
	}
	g.FillRelations();

	for(int i = 0; i < g.v; i++)
		if(g.CanReach(i))
			puts(g.vers[i].name);
}