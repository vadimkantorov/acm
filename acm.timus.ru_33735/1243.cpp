#include <stdio.h>
#include <string.h>

void main()
{
	char M[60];
	gets(M);
	int len = strlen(M);
	for(int i = 0; i < len; i++)	M[i] -= '0';
	int sum = 0;
	bool plus = true;
	
	for(int i = len - 1; i >= len%3; i-= 3)
	{
		if(plus)	sum += M[i] + 10*M[i-1] + 100*M[i-2];
		else		sum -= M[i] + 10*M[i-1] + 100*M[i-2];
		
		plus = !plus;
	}
	
	if(len%3 == 1)
	{
		if(plus)	sum += M[0];
		else		sum -= M[0];
	}
	else if(len%3 == 2)
	{
		if(plus)	sum += 10*M[0] + M[1];
		else		sum -= 10*M[0] + M[1];;
	}
	
	sum = sum%7 + 7;
	printf("%d",sum%7);
}