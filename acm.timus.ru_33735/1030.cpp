#include <cstdio>
#include <cmath>
#define SQR(x) ((x)*(x))

const double PI = 3.1415926535897932384626433832795;

char str[1000];

void Convert(double latitude, double longitude, double* sX, double* sY, double* sZ)
{
	*sX = cos(latitude*PI/(180*3600))*cos(longitude*PI/(180*3600));
	*sY = cos(latitude*PI/(180*3600))*sin(longitude*PI/(180*3600));
	*sZ = sin(latitude*PI/(180*3600));
}

void main()
{
	//freopen("input.txt", "r", stdin);

	int x1,x2,x3,y1,y2,y3,a1,a2,a3,b1,b2,b3;
	double sX, sY, sZ, iX, iY, iZ;
	double sLatitude, sLongitude, iLatitude, iLongitude;
	char sLatitudeDir, sLongitudeDir, iLatitudeDir, iLongitudeDir;

	gets(str);
	gets(str);
	gets(str);
	scanf("%d^%d'%d\" %c", &x1, &x2, &x3, &sLatitudeDir);
	gets(str);
	scanf("and %d^%d'%d\" %c", &y1, &y2, &y3, &sLongitudeDir);
	gets(str);
	gets(str);
	scanf("%d^%d'%d\" %c", &a1, &a2, &a3, &iLatitudeDir);
	gets(str);
	scanf("and %d^%d'%d\" %c", &b1, &b2, &b3, &iLongitudeDir);

	sLatitude = x1*3600 + x2*60 + x3;
	sLongitude = y1*3600 + y2*60 + y3;
	iLatitude = a1*3600 + a2*60 + a3;
	iLongitude = b1*3600 + b2*60 + b3;

	if(sLatitudeDir == 'S')
		sLatitude = -sLatitude;
	if(sLongitudeDir == 'E')
		sLongitude = -sLongitude;
	if(iLatitudeDir == 'S')
		iLatitude = -iLatitude;
	if(iLongitudeDir == 'E')
		iLongitude = -iLongitude;

	Convert(sLatitude, sLongitude, &sX, &sY, &sZ);
	Convert(iLatitude, iLongitude, &iX, &iY, &iZ);

	double alpha = acos((sX*iX + sY*iY + sZ*iZ)/
		sqrt(SQR(sX) + SQR(sY) + SQR(sZ))/
		sqrt(SQR(iX) + SQR(iY) + SQR(iZ)));
	double res = alpha*3437.5;
	printf("The distance to the iceberg: %.2lf miles.\n",res);
	if(100-res > 0.005)
		puts("DANGER!");
}