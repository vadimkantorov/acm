#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <locale>
using namespace std;

void main()
{
	srand(time(NULL));
	unsigned char c;
	for(int i = 0;i<1000000;)
	{
		c = (unsigned char)rand();
		if(isalpha(c))
		{
			cout<<(unsigned char)tolower(c);
			i++;
		}
	}
}