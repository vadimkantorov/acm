#include <stdio.h>
#define SQ2 0.7071067811865475244

double shift[2][9] = { {-SQ2,0,SQ2,-1,0,1,-SQ2,0,SQ2} , {-SQ2,-1,-SQ2,0,0,0,SQ2,1,SQ2} }; 
void main()
{
	double x = 0.0,y = 0.0;
	
	char c;
	while(scanf("%c",&c) > 0)
	{
		if(c == '\n' || c == '0')
			break;
		x += shift[0][c-'0'-1];
		y += shift[1][c-'0'-1];
	}
	printf("%.10lf %.10lf",x,y);
}