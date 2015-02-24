#include <cstdio>
#include <set>
#include <algorithm>
using namespace std;

struct GraphA
{
	struct Edge
	{
		short Weight;
		char Company;
	};

	static const int N = 102;
	static const int INF = 32000;
	Edge M[N][N];

	GraphA()
	{
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				M[i][j].Weight = INF;
	}

	void AddEdge(int u, int v, int w, int c)
	{
		Edge e = {w,c};
		M[u][v] = e;
	}
};
int D[5002];
struct GraphB
{
	static const int N = 5002;
	static const int INF = 1000000000;
	short M[N][N];

	GraphB()
	{
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				M[i][j] = GraphA::INF;
	}
	
	void AddEdge(int u, int v, int w)
	{
		M[u][v] = w;
	}

	struct Comparer
	{
		bool operator()(int a, int b)
		{
			return D[a] < D[b];
		}
	};

	void Dijkstra(int source)
	{
		multiset<int,Comparer> V;
		for(int i = 0; i < N; i++)
		{
			D[i] = (i == source)?0:INF;
			V.insert(i);
		}
		while(!V.empty())
		{
			int u = *V.begin();
			V.erase(V.begin());
			for(int v = 0; v < N; v++)
			{
				if(M[u][v] < GraphA::INF)
				{
					int newd = D[u] + M[u][v];
					if(newd < D[v])
					{
						V.erase(v);
						D[v] = newd;
						V.insert(v);
					}
				}
			}
		}
	}
};

GraphA A;
GraphB B;

int main()
{
	//freopen("input.txt","r",stdin);
	
	int n,k,m;
	scanf("%d%d%d",&n,&k,&m);
	for(int i = 0; i < m; i++)
	{
		int u,v,w,c;
		scanf("%d%d%d%d",&u,&v,&w,&c);
		A.AddEdge(u-1,v-1,w,c-1);
	}
	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(A.M[i][j].Weight != GraphA::INF)
			{
				for(int c = 0; c < k; c++)
					if(c != A.M[i][j].Company)
						B.AddEdge(k*i+A.M[i][j].Company,k*j+c,A.M[i][j].Weight);
			}
		}
	}
	int source, sink;
	scanf("%d%d",&source,&sink);
	int min = -1;
	
	for(int i = 0; i < k; i++)
	{
		B.Dijkstra((source-1)*k + i);
		for(int j = 0; j < k; j++)
		{
			int tmp = -1;
			if(D[(sink-1)*k+j] < GraphB::INF)
				tmp = D[(sink-1)*k+j];
			if( (min == -1 && tmp != -1) || ( tmp != -1 && tmp < min ))
				min = tmp;
		}
	}
/*for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(A.M[i][j].Weight != GraphA::INF)
			{
				for(int c = 0; c < k; c++)
					if(c != A.M[i][j].Company)
					{
						int from = 0;
						if(i > 0)
							from = k*(i-1)+A.M[i][j].Company + 1;
						B.AddEdge(from,k*j+c, A.M[i][j].Weight);
						//B.AddEdge(k*i+A.M[i][j].Company,k*j+c, A.M[i][j].Weight);
					}
			}
		}
	}
	int source, sink;
	scanf("%d%d",&source,&sink);
	B.Dijkstra(0);
	int min = -1;
	printf("%d",min);*/
	printf("%d",min);
	return 0;
}