#include <cstdio>
#include <vector>
using namespace std;

struct Vertex
{
	unsigned short MaxChild;
	unsigned short DfsID;
	unsigned short ID;
	int Parent;
	unsigned short AdjCount;
	unsigned short* Adj;
};

struct Graph
{
	static const int MAXN = 40002;
	Vertex M[MAXN];
	unsigned short Degrees[MAXN];
	unsigned short IDs[MAXN];
	bool visited[MAXN];
	int n;
	int dfscount;
	
	Graph(): n(0),dfscount(0){}

	void Prepare()
	{
		for(int i = 0; i < MAXN; i++)
			if(Degrees[i] != 0)
			{
				M[IDs[i]].Adj = new unsigned short[Degrees[i]];
				M[IDs[i]].AdjCount = 0;
			}
		for(int i = 0; i < n; i++)
		{
			if(M[i].Parent != -1)
			{
				M[IDs[M[i].Parent]].Adj[M[IDs[M[i].Parent]].AdjCount++] = IDs[M[i].ID];
			}
			visited[i] = false;
		}
	}

	int DFS(int start)
	{
		visited[start] = true;
		M[start].DfsID = ++dfscount;
		M[start].MaxChild = M[start].DfsID;
		for(int i = 0; i < M[start].AdjCount; i++)
		{
			if(!visited[M[start].Adj[i]])
			{
				int tmp = DFS(M[start].Adj[i]);
				if(tmp > M[start].MaxChild)
					M[start].MaxChild = tmp;
			}
		}
		return M[start].MaxChild;
	}

	int AnswerQuestion(int psidl, int psidr)
	{
		int a = IDs[psidl];
		int b = IDs[psidr];

		if(M[a].DfsID > M[b].DfsID && M[a].DfsID <= M[b].MaxChild)
			return 2;
		if(M[b].DfsID > M[a].DfsID && M[b].DfsID <= M[a].MaxChild)
			return 1;
		return 0;
	}
};

Graph g;

void main()
{
	int a,b,root;
	
	int n;
	scanf("%d",&n);
	g.n = n;
	for(int i = 0; i < n; i++)
	{
		scanf("%d%d",&a,&b);
		g.IDs[a] = i;
		g.M[i].Parent = b;
		g.M[i].ID = a;

		if(b == -1)
			root = i;
		else
			g.Degrees[b]++;
	}
	g.Prepare();
	g.DFS(root);
	int m;
	scanf("%d",&m);
	for(int i = 0; i < m; i++)
	{
		scanf("%d%d",&a,&b);
		printf("%d\n",g.AnswerQuestion(a,b));
	}
}