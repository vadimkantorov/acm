#include <cstdio>
#include <cctype>

int main()
{
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);

	bool newSent = true;
	while(true)
	{
		char c = getchar();
		if(c == EOF)
			break;

		if(isalpha(c))
		{
			if(newSent)
			{
				putchar(toupper(c));
				newSent = false;
			}
			else
				putchar(tolower(c));
		}
		else
		{
			if(c == '!' || c == '?' || c == '.')
				newSent = true;
			putchar(c);
		}
	}

	return 0;
}