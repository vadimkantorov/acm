#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Graph
{
	static const int N = 50005, LOGN = 16;
	
	struct Edge
	{
		int Vertex;
		int Weight;
	};
	
	vector<Edge> M[N];
	int L[N], W[N], P[N][LOGN];
	
	void AddEdge(int u, int v, int w)
	{
		Edge e1 = {v,w}, e2 = {u,w};
		M[u].push_back(e1);
		M[v].push_back(e2);
	}

	void PreProcess()
	{
		for(int i = 0; i < N; i++)
			for(int j = 0; j < LOGN; j++)
				P[i][j] = -1;
		
		queue<int> Q;
		Q.push(0);
		
		while(!Q.empty())
		{
			int ver = Q.front();
			Q.pop();

			for(int i = 0; i < M[ver].size(); i++)
			{
				int v = M[ver][i].Vertex;
				int w = M[ver][i].Weight;

				if(L[v] == 0 && v != 0)
				{
					L[v] = L[ver] + 1;
					W[v] = W[ver] + w;
					P[v][0] = ver;
					for(int j = 1; 1 << j <= L[v]; j++)
						P[v][j] = P[P[v][j-1]][j-1];

					Q.push(v);
				}
			}
		}
	}

	int LCA(int p, int q)
	{
		if(L[p] < L[q])
			swap(p,q);
		
		int log = 0;
		while(1 << (log+1) <= L[p])
			log++;

		for(int j = log; j >= 0; j--)
		{
			if(L[p] - (1 << j)  >= L[q])
				p = P[p][j];
		}

		if(p == q)
			return p;

		for(int j = log; j >= 0; j--)
		{
			if(P[p][j] != -1 && P[p][j] != P[q][j])
			{
				p = P[p][j];
				q = P[q][j];
			}
		}

		return P[p][0];
	}

	int Path(int p, int q)
	{
		return W[p] + W[q] - 2*W[LCA(p,q)];
	}
};

Graph g;

void main()
{
	//freopen("input.txt","r",stdin);
	
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n-1; i++)
	{
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		g.AddEdge(u,v,w);
	}
	g.PreProcess();
	
	int m;
	scanf("%d",&m);
	for(int i = 0; i < m; i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		printf("%d\n",g.Path(u,v));
	}
}