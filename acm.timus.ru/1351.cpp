#include <stdio.h>

void main()
{
	int D,X1,Y1,X2,Y2,n;
	scanf("%d %d %d %d %d %d", &D, &X1, &Y1, &X2, &Y2, &n);
	
	int x,y;
	for(int i = 0; i < n; i++)
	{
		scanf("%d %d",&x, &y);
		if(x*x + y*y <= D*D && (X1*y - Y1*x >= 0 && X2*y - Y2*x <= 0))
			printf("YES\n");
		else
			printf("NO\n");
	}
}