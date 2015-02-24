#include <cstdio>
#include <cmath>

void P(long& x, long& y) {
    int i, j;
    if (x>0 && y>0) {
        for (i = 1; i <= x+y; i++) {
            y = x*x+y;
            x = x*x+y;
            y = sqrt(double(x+(y/labs(y))*(-labs(y))));
            for (j = 1; j <= 2*y; j++)
                x = x-y;
        }
    }
}

void main()
{
	long x,y;
	scanf("%d %d",&x,&y);
	//P(x,y);
	//printf("%d %d",x,y);
	if( x <= 0 || y <= 0) printf("%d %d",x,y);
	else if(x%2 == y%2) printf("%d %d",x,y);
	else printf("%d %d",y,x);
}