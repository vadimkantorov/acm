#include <cstdio>
#include <vector>
#include <utility>
#include <queue>

#ifndef _MSC_VER
#define _Adjust_heap __adjust_heap
#define _Push_heap __push_heap
#endif
using namespace std;

const int N = 77;
const double SQRT2 =  1.4142135623730950488016887242097;
const double INF = 1000000000.0;

int R[][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {-1,1}, {1,-1}, {-1,-1}};
double S[] = {1,1,1,1,SQRT2,SQRT2,SQRT2,SQRT2};

int n,m;

bool ishouse[N][N];
double D[N][N];

struct Elem
{
	int X,Y;
	Elem** Position;

	Elem() : X(-1), Y(-1), Position(NULL) { }
	Elem(int X, int Y) : X(X), Y(Y) { }
	
	bool operator< (const Elem& x) const
	{
		return D[X][Y] > D[x.X][x.Y];
	}

	Elem& operator=(const Elem& x)
	{
		X = x.X;
		Y = x.Y;
		Position = x.Position;

		if(Position != NULL)
			Position[GetKey()] = this;
		return *this;
	}

	int GetKey()
	{
		return X*100 + Y;
	}
};


struct PQ
{
	Elem* position[7578];
	Elem elems[5630];
	int size;

	PQ() : size(0) { }
	void IncreaseKey(int x, int y, double newd)
	{
		D[x][y] = newd;
		Elem* top = position[Top().GetKey()];
		Elem* tochange = position[x*100+y];
		
		
		//»ли это, или то
		//for(int i = tochange - top; i > 0 && *(top + (i+1)/2-1) < *(top + i); i = (i+1)/2-1 )
		//	swap(*(top + (i+1)/2-1), *(top + i));
		
		_Adjust_heap(top,tochange-top,size, *tochange);
		_Push_heap(top, tochange-top, 0, *tochange);
	}

	bool Empty()
	{
		return size == 0;
	}

	void Push(Elem el)
	{
		el.Position = position;
		elems[size++] = el;
		push_heap(elems,elems+size);
	}

	Elem Top()
	{
		return elems[0];
	}

	void Pop()
	{
		pop_heap(elems, elems + size);
		size--;
	}
};



void Dijkstra(int x0, int y0)
{
	PQ Q;
	
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
		{
			D[i][j] = (i == x0 && j == y0)?0:INF;
			Q.Push(Elem(i,j));
		}

	while(!Q.Empty())
	{
		Elem ver = Q.Top();
		Q.Pop();
		for(int k = 0; k < 8; k++)
		{
			int x = ver.X+R[k][0],
				y = ver.Y+R[k][1];
			
			if(	x >= 0 && x <= n-1 && 
				y >= 0 && y <= m-1 &&
				!ishouse[x][y])
			{
				double newd = D[ver.X][ver.Y] + S[k];
				if(newd < D[x][y])
					Q.IncreaseKey(x,y , newd);
			}
		}
	}
}

void main()
{
	//freopen("input.txt", "r", stdin);
	
	int k;
	double v;
	scanf("%d%d%d%lf\n",&n,&m,&k,&v);
	for(int i = 0; i < m; i++)
	{
		for(int j = 0; j < n; j++)
			ishouse[j][i] = (getchar() == '#');
		getchar();
	}
	
	int x0,y0;
	scanf("%d%d",&x0,&y0);
	x0--; y0--;

	double time = 0.0;
	for(int i = 0; i < k; i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		x--; y--;
		Dijkstra(x0,y0);
		if(D[x][y] < INF)
		{
			time += D[x][y]/v;
			x0 = x;
			y0 = y;
		}
	}
	printf("%.2lf",time);
}