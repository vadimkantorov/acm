#include <stdio.h>
#include <locale>
void main()
{
	char c;
	char word[256];
	int index = 0;
	bool inword = false;

	while(scanf("%c",&c) > 0)
	{
		if(inword)
		{
			if(isalpha(c))
				word[index++] = c;
			else
			{
				inword = false;
				for(int i = index-1; i >= 0; i--)
					printf("%c",word[i]);
				printf("%c",c);
				index = 0;
			}
		}
		else
		{
			if(isalpha(c))
			{
				inword = true;
				word[index++] = c;
			}
			else
				printf("%c",c);
		}
	}
	if(inword)
	{
		for(int i = index-1; i >= 0; i--)
			printf("%c",word[i]);
	}
}