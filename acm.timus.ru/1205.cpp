#include <cstdio>
#include <cmath>
#include <stack>
#define SQR(x) ((x)*(x))
#define NMAX 205
#define INF 1000000000
using namespace std;

struct Point
{
	double x,y;
};

Point A[NMAX];

double Dist(int i, int j, double v)
{
	return sqrt(double(SQR(A[i].x-A[j].x)+SQR(A[i].y-A[j].y)))/v;
}

struct Graph
{
	double M[NMAX][NMAX], D[NMAX];
	int P[NMAX];
	bool visited[NMAX];
	Graph()
	{
		for(int i = 0; i < NMAX; i++)
			for(int j = 0; j < NMAX;j++)
				M[i][j] = INF;
	}

	void AddEdge(int v, int w, double weight)
	{
		if(!AreConnected(v,w))
			M[v][w] = weight;
	}

	bool AreConnected(int v, int w)
	{
		return M[v][w] != INF;
	}

	int getMin(int N)
	{
		int mini=-1;
		double minval = 2*INF;
		for(int i = 0; i < N; i++)
		{
			if(!visited[i] && D[i] < minval)
			{
				minval = D[i];
				mini = i;
			}
		}
		if(mini != -1)
			visited[mini] = true;
		return mini;
	}

	void Relax(int v, int u)
	{
		double newval = D[u] + M[u][v];
		if(newval < D[v])
		{
			D[v] = newval;
			P[v] = u;
		}
	}

	void PrintPath(int v, int N)
	{
		stack<int> st;
		int curv = v;
		while(P[curv] != -1)
		{
			if(curv != N-1 && curv != N-2)
			{
				st.push(curv);
			}
			curv = P[curv];
		}

		printf("%d ",st.size());
		while(!st.empty())
		{
			curv = st.top();
			st.pop();
			printf("%d ",curv+1);
		}
	}

	void Dijskstra(int v, int N)
	{
		for(int i = 0; i < N; i++)
		{
			P[i] = -1;
			D[i] = INF;
			visited[i] = false;
		}
		D[v] = 0;
		int cur;
		while((cur = getMin(N)) != -1)
		{
			for(int j = 0; j < N; j++)
				if(AreConnected(cur,j))
					Relax(j,cur);
		}
	}
};

void main()
{
	//freopen("input.txt","r",stdin);
	
	double Vf, Vm;
	int N;
	Graph g;

	scanf("%lf%lf", &Vf, &Vm);
	scanf("%d",&N);

	for(int i = 0; i < N; i++)
		scanf("%lf%lf",&A[i].x, &A[i].y);

	
	while(true)
	{
		int v,w;
		scanf("%d%d",&v,&w);
		
		if( v == 0 && w == 0)
			break;
		
		v--; w--;
		double time = Dist(v,w,Vm);
		g.AddEdge(v,w,time);
		g.AddEdge(w,v,time);
	}
	N += 2;
	scanf("%lf%lf",&A[N-2].x, &A[N-2].y);
	scanf("%lf%lf",&A[N-1].x, &A[N-1].y);
	int s = N-2, ver = N-1;
	/*for(int i = 0; i < N-2; i++)
	{
		if(A[i].x == A[N-2].x && A[i].y == A[N-2].y)
		{
			s = i;
			N--;
		}
		if(A[i].x == A[N-1].x && A[i].y == A[N-1].y)
		{
			ver = i;
			N--;
		}
	}*/

	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			if(i != j)
			{
				double time = Dist(i,j,Vf);
				g.AddEdge(i,j,time);
				g.AddEdge(j,i,time);
			}
		}
	}
	
	
	g.Dijskstra(s,N);
	printf("%.10lf\n",g.D[ver]);
	g.PrintPath(ver,N);
}