#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <algorithm>
using namespace std;

bool greater(int,int);

struct Vertex
{
	string* name;
	vector<short>* adj;
	
	int AdjCount()
	{
		return adj->size();
	}
	Vertex(string& _name)
	{
		name = new string(_name);
		adj = new vector<short>;
	}

	Vertex()
	{
		name = NULL;
		adj = NULL;
	}

	void AddAdj(short u)
	{
		adj->push_back(u);
	}

	void Sort()
	{
		sort(adj->begin(), adj->end(),greater);
	}
};

struct Graph
{
	//vector<Vertex> M;
	Vertex M[19750];
	int v;
	
	Graph()
	{
		v = 0;
	}
		
	int AddEdge(int u, string& name)
	{
		for(int i = 0; i < M[u].AdjCount(); i++)
		{
			//if(*(M[M[u].adj[i]].name) == name)
			//	return M[u].adj[i];
			if(*(M[       (*(M[u].adj))[i]     ].name) == name)
				return (*M[u].adj)[i];
		}
		M[v++] = Vertex(name);
		M[u].AddAdj(v-1);
		return v-1;
	}

	int V()
	{
		return v;
	}

	void AddRoot()
	{
		M[v++] = Vertex(string("Root"));
	}
};

Graph g;

bool greater(int a, int b)
{
	return (*g.M[a].name < *g.M[b].name);
}

void print(int v, int spaces)
{
	if(v != 0)
	{
		for(int i = 0; i < spaces; i++)
			cout << " ";
		cout << *(g.M[v].name) << endl;
	}
	for(int i = 0; i < g.M[v].AdjCount(); i++)
		print( (*g.M[v].adj)[i], spaces + 1);
}

void main()
{
	//freopen("input.txt","r",stdin);
	g.AddRoot();
	int n;
	cin >> n;
	cin.get();
	string tmp,name;
	for(int i = 0;i < n; i++)
	{
		cin >> tmp;
		tmp += '\\';
		int prev = 0;
		for(int j = 0; j < tmp.length(); j++)
		{
			if(tmp[j] != '\\')
				name += tmp[j];
			else
			{
				prev = g.AddEdge(prev,name);
				name = "";
			}
		}
	}

	for(int i = 0; i < g.V(); i++)
		g.M[i].Sort();
	print(0,-1);
}