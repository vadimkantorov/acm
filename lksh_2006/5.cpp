#include <cstdio>
#include <stack>
using namespace std;

int main()
{
	stack<char> S;

	while(true)
	{
		char c = getchar();
		switch(c)
		{
		case '(':
		case '[':
			S.push(c);
			break;
		case ')':
		case ']':{
			if(S.empty())
			{
				puts("NO");
				return 0;
			}
			char x = S.top();
			S.pop();
			if((c == ')' && x != '(') ||
				(c == ']' && x != '['))
			{
				puts("NO");
				return 0;
			}
			break;}
		default:
			if(S.empty())
				puts("YES");
			else
				puts("NO");
			return 0;
		}
	}
	return 0;
}