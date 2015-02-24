#include <cstdio>
#include <utility>
#define N 1002
#define M 100002
using namespace std;

int map[N];
pair<int,int> req[M];

void main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i = 0; i < m; i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		req[i] = pair<int,int>(a,b);
	}
	for(int i = 0; i < n; i++)
	{
		int aux;
		scanf("%d",&aux);
		map[aux] = i;
	}

	for(int i = 0; i < m; i++)
	{
		if(map[req[i].first] > map[req[i].second])
		{
			puts("NO");
			return;
		}
	}
	puts("YES");
}