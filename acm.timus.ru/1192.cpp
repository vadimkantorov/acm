#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
const double pi=3.1415926535;
void main()
{
	double V,a,k;
	cin>>V>>a>>k;
	printf("%.2f", sin(a*pi/90)*V*V*k/(10*(k-1)));//следует из кинематической формулы+считаем по сумме бесконечно уб геом прогрессии
}