#include <cstdio>
#include <cmath>
#define INF 1000000000
#define SQR(x) ((x)*(x))

const double k = 0.4472135954999;
const int N = 52;
double X[N+1][N+1];

void main()
{
	for(int i = 0; i <= N; i++)
		for(int j = 0; j <= N; j++)
			X[i][j] = INF;
	X[0][0] = 0;
	
	int n,m;
	scanf("%d%d",&n,&m);

	double tmp;
	for(int i = 0; i <= n; i++)
	{
		for(int j = 0; j <= m; j++)
			for(int x = 0; x <= i; x++)
				for(int y = 0; y < j; y++)
				{
					tmp = k*(sqrt(double(SQR(x-i) + SQR(y-j))))  /(sqrt(double(m-j))+sqrt(double(m-y)));
					if(tmp + X[x][y] < X[i][j])
						X[i][j] = tmp + X[x][y];
				}
	}
	
	printf("%.7lf",X[n][m]);
}