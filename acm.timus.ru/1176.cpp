#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

struct Graph
{
	static const int N = 1002;
	vector<short> M[N];
	
	void AddEdge(int u, int v)
	{
		M[u].push_back(v);
	}

	void DeleteEdge(int u, int v)
	{
		M[u].erase(find(M[u].begin(), M[u].end(), v));
	}

	stack<short> vers;
	stack<short> result;

	void PrintEulerTour(int v)
	{
		vers.push(v);
				
		while(!vers.empty())
		{
			v = vers.top();
			if(M[v].size() != 0)
			{
				int w = M[v][0];
				DeleteEdge(v,w);
				vers.push(w);
			}
			else
			{
				result.push(v);
				vers.pop();
			}
		}

		int prev = -1;
		while(!result.empty())
		{
			if(prev != -1)
				printf("%d %d\n",prev+1,result.top()+1);
			
			prev = result.top();
			result.pop();
		}
	}
};

Graph g;

void main()
{
	//freopen("input.txt","r",stdin);
	
	int n,A;
	scanf("%d%d",&n,&A);
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			int tmp;
			scanf("%d",&tmp);
			if(i != j && tmp == 0)
				g.AddEdge(i,j);
		}
	}
	g.PrintEulerTour(A-1);
}