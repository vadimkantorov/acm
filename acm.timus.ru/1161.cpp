#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int X[102], n;

void main()
{
	//freopen("input.txt", "r", stdin);
	
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%d",&X[i]);
	sort(X,X+n);
	
	double res = X[n-1];
	for(int i = n-2; i >= 0; i--)
		res = 2*sqrt(res*X[i]);

	printf("%.2lf",res);
}