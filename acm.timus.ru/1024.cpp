#include <cstdio>
#include <vector>
using namespace std;

int P[1002];
bool Visited[1002];

vector<int> cycleLengths;

void FindCycle(int ver)
{
	int cur = ver;
	int steps = 0;
	while(cur != ver || steps == 0)
	{
		Visited[cur] = true;
		cur = P[cur]-1;
		steps++;
	}
	cycleLengths.push_back(steps);
}

int GCD(int a, int b)
{
	int c;
	while((c = a%b) != 0)
	{
		a = b;
		b = c;
	}
	return b;
}

void main()
{
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%d",&P[i]);
	for(int i = 0; i < n; i++)
		if(!Visited[i])
			FindCycle(i);

	int lcm = 1;
	for(int i = 0; i < cycleLengths.size(); i++)
		lcm = (lcm *cycleLengths[i])/GCD(lcm, cycleLengths[i]);
	printf("%d",lcm);
}