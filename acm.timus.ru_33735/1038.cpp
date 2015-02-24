#include <stdio.h>

bool iscapital(char c)
{
	return (c >= 'A' && c <= 'Z');
}

bool issmall(char c)
{
	return (c >= 'a' && c <= 'z');
}

bool isalpha(char c)
{
	return issmall(c) || iscapital(c);
}

bool isstop(char c)
{
	return (c == '.' || c == '?' || c == '!');
}

bool ispunct(char c)
{
	return (!iscapital(c) && !issmall(c) && !isstop(c));
}


void main()
{
	int errc = 0;
	bool in_sentence = false;
	bool in_word = false;
	
	char c;
	
	while(scanf("%c",&c) > 0)
	{
		if(in_sentence)
		{
			if(in_word)
			{
				if(iscapital(c)) 
					errc++;
				if(ispunct(c)) 
					in_word = false;
			}
			else
			{
				if(isalpha(c)) 
					in_word = true;
			}
			if(isstop(c)) 
				in_sentence = false;
		}
		else
		{
			if(isalpha(c))
			{ 
				in_sentence = true;
				in_word = true;
				if(!iscapital(c)) 
					errc++;
			}
		}
	}
	printf("%d",errc);
}