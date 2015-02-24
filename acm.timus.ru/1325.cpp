#include <cstdio>
#include <algorithm>
#define N 505
#define INF 1000000000
#ifndef _MSC_VER
#define _Adjust_heap __adjust_heap
#define _Push_heap __push_heap
#endif
using namespace std;

int plan[N][N],n,m;

struct Elem
{
	int X,Y;
	int Changes;
	int Length;
	Elem** position;

	Elem() : Changes(INF), X(-1), Y(-1), Length(INF), position(NULL) { }
	Elem(int X,int Y) : Changes(INF), X(X), Y(Y), Length(INF), position(NULL) { }

	bool operator<(const Elem& elem) const
	{
		if(Changes != elem.Changes)
			return Changes > elem.Changes;
		return Length > elem.Length;
	}

	Elem& operator=(const Elem& elem)
	{
		X = elem.X;
		Y = elem.Y;
		Changes = elem.Changes;
		Length = elem.Length;
		position = elem.position;
		position[GetKey()] = this;
		return *this;
	}
	
	int GetKey()
	{
		return X*1000+Y;
	}
};

struct PQ
{
	Elem elems[N*N];
	Elem* position[500600];
	int size;

	PQ() : size(0) { }

	bool Empty()
	{
		return size == 0;
	}
	
	void Push(Elem el)
	{
		el.position = position;
		elems[size++] = el;
		push_heap(elems, elems+size);
	}

	Elem Top()
	{
		return elems[0];
	}

	void Pop()
	{
		pop_heap(elems, elems+size);
		size--;
	}

	void IncreaseKey(int x, int y, int length, int changes)
	{
		bool change = false;
		Elem* tochange = position[x*1000+y];
		if(changes != tochange->Changes)
			change = changes < tochange->Changes;
		else
			change = length < tochange->Length;
		if(change)
		{
			tochange->Length = length;
			tochange->Changes = changes;

			Elem* top = position[Top().GetKey()];
			int hole = tochange - top;
			_Adjust_heap(elems,hole,size,*tochange);
			_Push_heap(elems,hole,0,*tochange);
		}
	}
};

PQ Q;

Elem Dijkstra(int x0, int y0, int x1, int y1)
{
	int dy[] = {0,0,1,1,1,-1,-1,-1};
	int dx[] = {-1,1,-1,0,1,-1,0,1};
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
		{
			Elem el = Elem(i,j);
			if(i == x0 && j == y0)
			{
				el.Length = 0;
				el.Changes = 0;
			}
			Q.Push(el);
		}
	while(!Q.Empty())
	{
		Elem ver = Q.Top();
		Q.Pop();
		
		for(int k = 0; k < 8; k++)
		{
			int x = ver.X + dx[k];
			int y = ver.Y + dy[k];

			if(x >= 0 && y >= 0 && x < n && y < m && plan[x][y] != 0)
				Q.IncreaseKey(x,y,ver.Length+1,ver.Changes+(plan[ver.X][ver.Y] != plan[x][y]));
		}
	}
	return *Q.position[x1*1000+y1];
}

void main()
{
	//freopen("input.txt","r",stdin);
	
	int x0,y0,x1,y1;
	scanf("%d%d%d%d%d%d\n",&m,&n,&x0,&y0,&x1,&y1);
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
			plan[j][i] = getchar() -'0';
		getchar();
	}
	int t;
	Elem el = Dijkstra(y0-1, x0-1,y1-1,x1-1);
	if(el.Length >= INF)
		puts("0 0");
	else
		printf("%d %d",el.Length+1,el.Changes);
}