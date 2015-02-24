#include <cstdio>

void main()
{
	char c;
	int sum = 0;
	while( (c = getchar()) != '\n' && c != EOF)
		sum += c - '0';
	sum = (sum%3+3)%3;
	if(sum == 0)
		puts("2");
	else
		printf("1\n%d",sum);
}