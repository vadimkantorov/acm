#include <iostream>
#include <cmath>

using namespace std;
#define ARR 300001
void main()
{
	bool flag = true;
	int count = 0;
	
	char A[ARR];
	A[0] = 0;
	A[1] = 1;
	A[2] = 1;
	A[3] = 2;
	for(int i = 4; i < ARR; i += 4)
	{
		A[i] = 0;
		if( i + 1 < ARR)
		{
			if(flag)
			{
				A[i + 1] = 2;
				flag = false;
			}
			else
			{
				A[i + 1] = 1;
				if( ++count == 4)
				{
					flag = true;
					count = 0;
				}
			}
		}
		if( i + 2 < ARR)
			A[i + 2] = 1;
		if( i + 3 < ARR)
			A[i + 3] = 2;
		//0212*1
		//0112*4
	}
	int n;
	cin >> n;
	printf("%d",A[n]);
}