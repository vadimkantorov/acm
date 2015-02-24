#include <cstdio>

int ind = 0;

void right()
{
	if(ind == 79) ind = 0; //79 - последний
	else ind++;
}
void left()
{
	if (ind > 0)  ind--;
}
void main()
{
	char c, a[81] = "                                                                                ";
	while( scanf("%c", &c) > 0 && c != '\n')
	{
		switch(c)
		{
		case '>':
			right();
			break;
		case '<':
			left();
			break;
		default:
			a[ind]=c;
			right();
			break;
		}
	}
	printf("%s",a);
}
