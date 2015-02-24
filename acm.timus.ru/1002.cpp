#define NUMBERLENGTH 100
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

char W[307201];
int end[50002];
char S[NUMBERLENGTH];

struct Graph
{
	vector<int> M[NUMBERLENGTH];
	int P[NUMBERLENGTH];
	bool visited[NUMBERLENGTH];
	
	void AddEdge(int u, int v)
	{
		M[u].push_back(v);
	}

	void Clear()
	{
		for(int i = 0; i < NUMBERLENGTH; i++)
		{
			P[i] = -1;
			visited[i] = false;
			M[i].clear();
		}
	}

	void BFS(int start)
	{
		visited[start] = true;
		
		queue<int> vers;
		vers.push(start);
		while(!vers.empty())
		{
			int v = vers.front();
			vers.pop();

			for(int i = 0; i < M[v].size(); i++)
			{
				if(!visited[M[v][i]])
				{
					visited[M[v][i]] = true;
					P[M[v][i]] = v;
					vers.push(M[v][i]);
				}
			}
		}
	}
};

bool ok(char* number, char* word, bool requireequal)
{
	int R[] = {2,2,2,3,3,3,4,4,1,1,5,5,6,6,0,7,0,7,7,8,8,8,9,9,9,0};
	
	int lenn = strlen(number);
	int lenw = strlen(word);
	if(lenw > lenn)
		return false;
	if(requireequal)
	{
		if(lenn != lenw)
			return false;
	}

	for(int i = 0; i < lenw; i++)
		if(R[word[i] - 'a'] != number[i]-'0')
			return false;
	return true;
}

Graph g;

void PrintParent(int from, int to, int n)
{
	if(from != -1)
	{
		PrintParent(g.P[from],from, n);
		char tmp = S[to];
		S[to] = '\0';
		for(int i = 1; i <= n; i++)
		{
			char x = W[end[i]];
			W[end[i]] = '\0';
			if(ok(S + from,W + end[i-1],true))
			{
				printf("%s ",W + end[i-1]);
				W[end[i]] = x;
				break;
			}
			W[end[i]] = x;
		}
		S[to] = tmp;
	}
}

void main() 
{
	//freopen("input.txt","r",stdin);
	char tmp[52];
	while(true)
	{
		gets(S);
		if(strcmp(S,"-1") == 0) break;
		g.Clear();
		int n;
		scanf("%d\n",&n);
		for(int i = 1; i <= n; i++)
		{
			gets(tmp);
			end[i] = end[i-1] + strlen(tmp);
			strcpy(W + end[i-1],tmp);
		}
		int len = strlen(S);
		for(int i = 0; i < len; i++)
		{
			for(int j = 1; j <= n; j++)
			{
				char x = W[end[j]];
				W[end[j]] = '\0';
				if(ok(S+i,W + end[j-1],false))
					g.AddEdge(i, i + strlen(W + end[j-1]));
				W[end[j]] = x;
			}
		}

		g.BFS(0);
		if(g.visited[len])
		{
			PrintParent(len,len,n);
			puts("");
		}
		else
			puts("No solution.");
	}
}