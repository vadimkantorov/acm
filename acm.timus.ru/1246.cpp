#include <cstdio>
#include <utility>
#define N 200002
using namespace std;

pair<double,double> ps[N];

void main()
{
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%lf%lf",&ps[i].first,&ps[i].second);
	
	ps[n] = ps[0];
	double res = 0;
	for(int i = 0; i < n; i++)
		res += (ps[i].first-ps[i+1].first)*(ps[i].second+ps[i+1].second)/2;
	if(res > 0)
		puts("ccw");
	else
		puts("cw");
}