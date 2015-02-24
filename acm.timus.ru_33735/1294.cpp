#include <cstdio>
#include <cmath>
#define SQR(x) ((x)*(x))

void main()
{
	__int64 AD,AC,BD,BC;
	scanf("%I64d%I64d%I64d%I64d",&AD,&AC,&BD,&BC);

	if(AC*AD == BC*BD)
	{
		puts("Impossible.");
		return;
	}

	int res = floor(
		sqrt(double(AC*AD*(SQR(BC) + SQR(BD)) - BC*BD*(SQR(AC) + SQR(AD))) / (AC*AD - BC*BD))*1000
		+ 0.5);
	printf("Distance is %d km.", res);
}