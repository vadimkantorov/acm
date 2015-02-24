#include <stdio.h>

//PREBUILD
/*int sum(int x)
{
	int n = 0;
	while(x != 0)
	{
		n += x%10;
		x /= 10;
	}
	return n;
}*/
int A[] = {10,670,55252,4816030};
void main()
{
	int n;
	scanf("%d", &n);
	switch(n)
	{
	case 2:
		printf("%d",A[0]);
		break;
	case 4:
		printf("%d",A[1]);
		break;
	case 6:
		printf("%d",A[2]);
		break;
	case 8:
		printf("%d",A[3]);
		break;
	}
	//PREBUILD
	/*int count = 0;
	for(int i = 0; i <= 9999;i++)//here n/2 nines
	{
		for(int j = 0; j <= 9999; j++)//and here n/2 nines too
		{
			if(sum(i) == sum(j))
				count++;
		}
	}*/
}