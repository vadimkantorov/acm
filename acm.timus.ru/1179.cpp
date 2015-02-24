#include <cstdio>

bool inNumber[36];
int numbersCount[36];

bool IsDigit(char c, int k)
{
	if(c != '\n' && c != ' ')
	{
		if(c >= '0' && c <= '9')
			return (c - '0') < k;
		return (c - 'A' + 10) < k;
	}
	return false;
}

void main()
{
	//freopen("input.txt","r",stdin);
	
	while(true)
	{
		char t = getchar();
		char c = t;
		if( t == EOF)
			c = '\n';
		for(int k = 2; k <= 36; k++)
		{
			if(inNumber[k-1])
			{
				if(!IsDigit(c,k))
				{
					inNumber[k-1] = false;
					numbersCount[k-1]++;
				}
			}
			else
			{
				if(IsDigit(c,k))
					inNumber[k-1] = true;
			}
		}
		if( t == EOF)
			break;
	}
	int maxk = 0, maxn = 0;
	for(int i = 0; i < 36; i++)
	{
		if(numbersCount[i] > maxn)
		{
			maxn = numbersCount[i];
			maxk = i+1;
		}
	}
	printf("%d %d",maxk, maxn);
}