#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 100005;
const int GOLEFT = 0;
const int GORIGHT = 1;

struct Point
{
	int X,Y;
	int Index;

	bool operator<(const Point& p) const
	{
		return Y > p.Y;
	}
};

struct PointChain
{
	int Cur;
	int Prev;
	int Count;
	int Dir;

	bool operator<(const PointChain& p) const
	{
		return Count < p.Count;
	}

	PointChain()
	{
		Prev = -1;
		Count = 0;
		Cur = -1;
		Dir = GOLEFT;
	}

	PointChain Prolong(int index, int dir)
	{
		PointChain chain;
		chain.Prev = Count != 0 ? Cur : -1;
		chain.Count = Count+1;
		chain.Cur = index;
		chain.Dir = dir;
		return chain;
	}
};

struct FenwickMaximizer
{
	PointChain ft[N];

	int Delta(int x)
	{
		return x & (-x);
	}

	void Insert(int x, PointChain val)
	{
		while(x < N)
		{
			ft[x] = max(ft[x],val);
			x += Delta(x);
		}
	}

	PointChain Max(int x)
	{
		PointChain maxVal;
		while(x > 0)
		{
			maxVal = max(maxVal,ft[x]);
			x -= Delta(x);
		}
		return maxVal;
	}
};

Point ps[N];

FenwickMaximizer leftMaximizers[2], rightMaximizers[2];
PointChain res[N][2];
vector<int> result;

void Print(PointChain v)
{
	printf("%d\n",v.Count);
	int cur = v.Cur;
	int curdir = v.Dir;
	while(cur != -1)
	{
		result.push_back(ps[cur].Index);
		cur = res[cur][curdir].Prev;
		curdir = 1-curdir;
	}

	for(int i = result.size()-1; i >= 0; i--)
		printf("%d ",result[i]);
}

void ComputeDP(int n)
{
	for(int i = 0; i < n; i++)
	{
		res[i][GOLEFT] = leftMaximizers[GORIGHT].Max(ps[i].X-1).Prolong(i, GOLEFT);
		res[i][GORIGHT] = rightMaximizers[GOLEFT].Max(100000-(ps[i].X+1)).Prolong(i, GORIGHT);

		leftMaximizers[GOLEFT].
			Insert(ps[i].X,
			res[i][GOLEFT]
		);
		leftMaximizers[GORIGHT].
			Insert(ps[i].X,
			res[i][GORIGHT]
		);
		rightMaximizers[GOLEFT].
			Insert(100000-ps[i].X,
			leftMaximizers[GORIGHT].Max(ps[i].X-1).Prolong(i, GOLEFT)
		);
		rightMaximizers[GORIGHT].
			Insert(100000-ps[i].X,
			rightMaximizers[GOLEFT].Max(100000-(ps[i].X+1)).Prolong(i, GORIGHT)
		);
	}
}

void main()
{
	//freopen("input.txt","r",stdin);
	
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d%d",&ps[i].X, &ps[i].Y);
		ps[i].Index = i+1;
	}
	sort(ps,ps+n);

	ComputeDP(n);
	Print(max(leftMaximizers[GOLEFT].Max(100000), leftMaximizers[GORIGHT].Max(100000)));
}