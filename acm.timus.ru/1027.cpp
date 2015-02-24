#include <iostream>
#include <cstdlib>
using std::cin;
using std::cout;

inline void yes()
{
	cout << "YES";
	exit(0);
}

inline void no()
{
	cout << "NO";
	exit(0);
}

inline bool eof(char c)
{
	return (c == std::char_traits<char>::eof());
}

enum lextype
{
	OPENBRACKET,
	CLOSEBRACKET,
	STAR,
	DIGIT,
	CHAR,
	END
};

struct lexeme
{
	char val;
	lextype type;
};

lexeme readlexeme(bool peek)
{
	lexeme l;
	if(peek)
		l.val = cin.peek();
	else
		l.val = cin.get();
	if(eof(l.val))
	{
		l.val = '\0';
		l.type = END;
	}
	else
	{
		switch(l.val)
		{
		case '(':
			l.type = OPENBRACKET;
			break;
		case ')':
			l.type = CLOSEBRACKET;
			break;
		case '*':
			l.type = STAR;
			break;
		case '=':
		case '+':
		case '-':
		case '/':
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			l.type = DIGIT;
			break;
		default:
			l.type = CHAR;
			break;
		}
	}
	return l;
}

inline lexeme readlexeme()
{
	return readlexeme(false);
}

inline lexeme peeklexeme()
{
	return readlexeme(true);
}

void main()
{
	freopen("input.txt","r",stdin);
	bool in_exp = false;
	bool in_comment = false;
	int brackets = 0;
	lexeme lex;
	while(true)
	{
		lex = readlexeme();
		if(lex.type == END)
		{
			if(in_exp || in_comment)
				no();
			else
				yes();
		}
		if(in_exp)
		{
			if(in_comment)
			{
				if(lex.type == STAR && peeklexeme().type == CLOSEBRACKET)
				{
					readlexeme();
					in_comment = false;
				}
			}
			else
			{
				if(lex.type == OPENBRACKET)
				{
					if(peeklexeme().type == STAR)
					{
						readlexeme();
						in_comment = true;
					}
					else
					{
						brackets++;
					}
				}
				else if(lex.type == CLOSEBRACKET)
				{
					brackets--;
					if(brackets == 0)
					{
						in_exp = false;
					}
					else
					{
						lexeme tmp = peeklexeme();
						if(tmp.type != DIGIT && tmp.type != OPENBRACKET && tmp.type != CLOSEBRACKET && tmp.val != '\n' && tmp.type != STAR)
							no();
					}
				}
				else if(lex.type != DIGIT && lex.val != '\n' && lex.type != STAR)
					no();
			}
		}
		else
		{
			if(in_comment)
			{
				if(lex.type == STAR && peeklexeme().type == CLOSEBRACKET)
				{
					readlexeme();
					in_comment = false;
				}
			}
			else
			{
				if(lex.type == OPENBRACKET)
				{
					if(peeklexeme().type == STAR)
					{
						readlexeme();
						in_comment = true;
					}
					else
					{
						brackets = 1;
						in_exp = true;
					}
				}
				else if(lex.type == CLOSEBRACKET)
					no();
			}
		}
	}
}