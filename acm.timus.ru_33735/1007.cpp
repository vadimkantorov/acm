#include <cstdio>
#define N 1002

char M[N];
int T[N], ones, length, n;

void ProcessWord()
{
	M[length] = '\0';
	if(length == n)
	{
		if(ones % (n+1) != 0)
		{
			for(int j = 0; j < length; j++)
			{
				if(M[j] == '1')
				{
					if((ones-j-1) % (n+1) == 0)
					{
						M[j] = '0';
						break;
					}
				}
			}
		}
		puts(M);
	}
	else
	{
		T[length] = 0;
		for(int j = length-1; j >= 0; j--)
			T[j] = T[j+1] + (M[j] == '1');

		if(length == n-1)
		{
			bool printed = false;
			
			for(int j = 0; j <= length; j++)
			{
				int mas[] = {0, j+1};
				for(int k = 0; k < 2; k++)
				{
					if((ones + T[j] + mas[k])% (n+1) == 0)
					{
						if(j < length)
						{
							char tmp = M[j];
							M[j] = '\0';
							printf("%s%d%c%s\n",M,mas[k] != 0,tmp,M+j+1);
						}
						else
							printf("%s%d\n",M,mas[k] != 0);
						printed = true;
						break;
					}
				}
				if(printed)
					break;
			}
			if(!printed)
				printf("%s0\n",M);
		}
		else if(length == n+1)
		{
			for(int j = 0; j <= length; j++)
			{
				int sub = (M[j] == '1')?j+1:0;
				if( (ones - sub - T[j+1]) % (n+1) == 0)
				{
					M[j] = '\0';
					printf("%s%s\n", M, M + j+1);
					break;
				}
			}
		}
	}

}

void main()
{
	freopen("input.txt", "r", stdin);
	
	scanf("%d\n",&n);
	while(true)
	{
		ones = 0;
		length = 0;
		while(true)
		{
			char c = getchar();
			if(c == '0' || c == '1')
			{
				M[length] = c;
				if(c == '1')
					ones += length + 1;
				length++;
			}
			else if(c == '\n' && length != 0)
				break;
			else if(c == EOF)
			{
				ProcessWord();
				return;
			}
		}
		ProcessWord();
	}
}