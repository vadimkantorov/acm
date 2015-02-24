#include "stdafx.h"
#include <iostream>
#include <cmath>
using namespace std;

void main()
{
		int n;
		cin >> n;
		double curr,num;
		for (int i = 0; i < n; i++)
		{
			cin >> curr;
			num = (sqrt(8*curr-7)-1)/2;
			if(num - floor(num) == 0)
				cout<<"1 ";
			else
				cout<<"0 ";
		}
}