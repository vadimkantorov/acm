#include <cstdio>
#include <cmath>

const int N = 505;
const double EPS = 1e-9;
double x[N], y[N], z[N], vx[N], vy[N], vz[N];

double mint = 1e+9;
bool ok = true;
int mini = 0, minj = 0;

double sqr(double x)
{
	return x*x;
}

bool EQ(double x, double y)
{
	return fabs(x-y) <= EPS;
}

bool GT(double x, double y)
{
	return x-EPS > y;
}

bool GE(double x, double y)
{
	return GT(x,y) || EQ(x,y);
}

double LT(double x, double y)
{
	return x+EPS < y;
}

double LE(double x, double y)
{
	return LT(x,y) || EQ(x,y);
}

int main()
{
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);

	int n;
	double d;                                                                                                                                                                                                                                                                                                                                                                                                                                     
	scanf("%d%lf",&n,&d);
	for(int i = 0; i < n; i++)
		scanf("%lf%lf%lf%lf%lf%lf",&x[i],&y[i],&z[i],&vx[i],&vy[i],&vz[i]);

	for(int i = 0; i < n; i++)
		for(int j = i+1; j < n; j++)
		{
			double Vx = vx[j] - vx[i];
			double Vy = vy[j] - vy[i];
			double Vz = vz[j] - vz[i];

			double X = x[j]-x[i];
			double Y = y[j]-y[i];
			double Z = z[j]-z[i];

			double a = sqr(Vx) + sqr(Vy) + sqr(Vz);
			if(!EQ(a,0))
			{
				double b = 2*(Vx*X + Vy*Y + Vz*Z);
				double c = sqr(X) + sqr(Y) + sqr(Z) - sqr(d);
				double D = sqr(b)-4*a*c;

				if(GE(D,0))
				{
if(EQ(D,0)) D = 0;					
double t = (-b + sqrt(D))/(2*a);
					if(GT(t,0) && LT(t,mint))
					{
						ok = false;
						mint = t;
						mini = i;
						minj = j;
					}
					
					t = (-b - sqrt(D))/(2*a);
					if(GT(t,0) && LT(t,mint))
					{
						ok = false;
						mint = t;
						mini = i;
						minj = j;
					}
				}
			}
		}

	if(ok)
		puts("OK");
	else
		printf("ALARM!\n%lf %d %d",mint,mini+1,minj+1);

	return 0;
}