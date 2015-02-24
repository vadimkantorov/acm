#include <cstdio>
#include <string>
using namespace std;

void main()
{
	//freopen("input.txt", "r", stdin);
	
	char cur;
	string buf;
	string prev = "   ";
	bool waiting = false;

	while( true )
	{
		cur = getchar();
		if(cur == 34) // "
		{
			if(prev[prev.length()-1] == '\\')
			{
				if(waiting)
					buf += cur;
				else
					putchar(cur);
				continue;
			}
			if(waiting)
			{
				waiting = false;
				printf("``%s''",buf.c_str());
			}
			else
			{
				buf = "";
				waiting = true;
			}
		}
		else
		{
			if( (cur == 'r' && prev == "\\pa") || 
				(cur == '\n' && prev[prev.length()-1] == '\n') || (cur == EOF) )
			{
				if(waiting)
				{
					waiting = false;
					printf("%s",buf.c_str());
				}
			}
			if(cur != EOF)
			{
				if(waiting)
					buf += cur;
				else
					putchar(cur);
				prev = prev.substr(1, prev.length()-1) + cur;
			}
		}
		if(cur == EOF)
			break;
	}
}