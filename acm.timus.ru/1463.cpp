#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <utility>
#define N 50002
using namespace std;

int n,k;

struct Edge
{
	int Vertex, Weight;
};

struct Graph
{
	vector<Edge> M[N];
	int W[N], visited[N], maxJoy[N], P[N], maxFuckingJoy[N];
	pair<int,int> fuckingFork[N];

	void AddEdge(int u, int v, int c)
	{
		Edge e1 = {v, c};
		Edge e2 = {u, c};
		M[u].push_back(e1);
		M[v].push_back(e2);
	}

	void DFS(queue<int>& Q, int start, int kind)
	{
		visited[start] = kind;
		for(int i = 0; i < M[start].size(); i++)
			if(visited[M[start][i].Vertex] == 0)
			{
				P[M[start][i].Vertex] = start;
				DFS(Q, M[start][i].Vertex, kind);
			}
		Q.push(start);
	}

	void Process()
	{
		for(int i = 0; i < n; i++)
		{
			maxJoy[i] = W[i];
			maxFuckingJoy[i] = W[i];
			visited[i] = 0;
			fuckingFork[i].first = -1;
			fuckingFork[i].second = -1;
		}

		int kind = 1;
		for(int i = 0; i < n; i++)
		{
			if(visited[i] == 0)
			{
				queue<int> Q;
				DFS(Q,i,kind++);
				DP(Q);
			}
		}
	}

	void DP(queue<int>& Q)
	{
		while(!Q.empty())
		{
			int cur = Q.front();
			Q.pop();
			int firstFuckingIndex = -1, secondFuckingIndex = -1;
			for(int i = 0; i < M[cur].size(); i++)
			{
				if(P[cur] != M[cur][i].Vertex)
				{
					int curPathWeight = maxJoy[M[cur][i].Vertex] + M[cur][i].Weight;

					if(firstFuckingIndex == -1 || 
						(curPathWeight > maxJoy[M[cur][firstFuckingIndex].Vertex] + M[cur][firstFuckingIndex].Weight))
					{
						secondFuckingIndex = firstFuckingIndex;
						firstFuckingIndex = i;
					}
					else if(secondFuckingIndex == -1 ||
						(curPathWeight > maxJoy[M[cur][secondFuckingIndex].Vertex] + M[cur][secondFuckingIndex].Weight))
						secondFuckingIndex = i;
				}
			}
			if(firstFuckingIndex != -1)
			{
				fuckingFork[cur].first = M[cur][firstFuckingIndex].Vertex;
				maxJoy[cur] += maxJoy[fuckingFork[cur].first] + M[cur][firstFuckingIndex].Weight;
				if(secondFuckingIndex != -1)
				{
					fuckingFork[cur].second = M[cur][secondFuckingIndex].Vertex;
					maxFuckingJoy[cur] +=(maxJoy[fuckingFork[cur].first] + M[cur][firstFuckingIndex].Weight +
										maxJoy[fuckingFork[cur].second] + M[cur][secondFuckingIndex].Weight);
				}
			}
		}
	}

	int pathLength;
	char res[10000], tmp[1000];

	void Print()
	{
		Process();
		pathLength = 0;
		strcpy(res, "");
		int maxJoyInd = max_element(maxJoy, maxJoy+n) - maxJoy,
			maxFuckingJoyInd = max_element(maxFuckingJoy, maxFuckingJoy+n) - maxFuckingJoy;

		if(maxJoy[maxJoyInd] > maxFuckingJoy[maxFuckingJoyInd])
		{
			printf("%d\n", maxJoy[maxJoyInd]);
			PrintUpDown(maxJoyInd);
		}
		else
		{
			printf("%d\n", maxFuckingJoy[maxFuckingJoyInd]);
			PrintDownUp(fuckingFork[maxFuckingJoyInd].first);
			sprintf(tmp,"%d",maxFuckingJoyInd+1);
			strcat(res,tmp);
			pathLength++;
			PrintUpDown(fuckingFork[maxFuckingJoyInd].second);
		}
		printf("%d\n%s",pathLength,res);
	}

	void PrintUpDown(int ver)
	{
		while(ver != -1)
		{
			sprintf(tmp," %d",ver+1);
			strcat(res,tmp);
			pathLength++;
			ver = fuckingFork[ver].first;
		}
	}

	void PrintDownUp(int ver)
	{
		if(ver != -1)
		{
			PrintDownUp(fuckingFork[ver].first);
			sprintf(tmp,"%d ",ver+1);
			strcat(res,tmp);
			pathLength++;
		}
	}
};

Graph g;

void main()
{
	//freopen("input.txt", "r", stdin);

	scanf("%d%d",&n,&k);
	for(int i = 0; i < n; i++)
	{
		int x;
		scanf("%d",&x);
		g.W[i] = x;
	}
	for(int i = 0; i < k; i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		g.AddEdge(a-1,b-1,c);
	}
	g.Print();
}