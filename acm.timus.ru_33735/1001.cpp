#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

vector<double> Ds;

void main()
{
	//freopen("input.txt","r",stdin);
	
	double d;
	while(scanf("%lf",&d) > 0)
		Ds.push_back(sqrt(d));
	for(int i = Ds.size()-1; i >= 0; i--)
		printf("%.4lf\n",Ds[i]);
}