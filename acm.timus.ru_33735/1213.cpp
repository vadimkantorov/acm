#include <cstdio>
#include <string>
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <queue>
using namespace std;

struct Graph
{
	map<string,int> dict;
	vector<int> M[40];
	int verCnt;
	bool visited[40];

	void AddEdge(string a, string b)
	{
		if(dict.find(a) == dict.end())
			dict.insert(make_pair(a,++verCnt));
		if(dict.find(b) == dict.end())
			dict.insert(make_pair(b,++verCnt));

		int u = dict[a], v = dict[b];
		M[u].push_back(v);
		M[v].push_back(u);
	}
	
	int BFS(int start)
	{
		int res = 0;
		queue<int> Q;
		Q.push(start);
		visited[start] = true;

		while(!Q.empty())
		{
			int v = Q.front();
			Q.pop();

			for(int i = 0; i < M[v].size(); i++)
			{
				int u = M[v][i];
				if(!visited[u])
				{
					res++;
					Q.push(u);
					visited[u] = true;
				}
			}
		}
		return res;
	}
} g;

void main()
{
	//freopen("input.txt","r",stdin);
	
	string gate;
	getline(cin,gate);

	char a[30], b[30];
	while(scanf("%[^-#]-%s\n",a,b) > 0)
	{
		string A(a), B(b);
		g.AddEdge(A,B);
	}
	printf("%d",g.BFS(g.dict[gate]));
}