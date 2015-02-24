#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

string keywords[] =  {"and", "array", "begin", "case", "class", "const", "div", "do", "else", "end", "for", "function", "if", "implementation", "interface", "mod", "not", "of", "or", "procedure", "program", "record", "repeat", "shl", "shr", "string", "then", "to", "type", "unit", "until", "uses", "var", "with", "while"};
string opencomment = "<span class=comment>";
string openkeyword = "<span class=keyword>";
string opennumber = "<span class=number>";
string openstring = "<span class=string>";
string closespan = "</span>";

inline bool isidchar(char c)
{
	return (c == '_' || (c <= '9' && c >= '0') || ( (c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A')));
}
bool iskeyword(string word)
{
	for(int i = 0; i < word.size(); i++)
		word[i] = tolower(word[i]);
	for(int i = 0; i < 36; i++)
		if(word == keywords[i])
			return true;
	return false;
}

enum state
{
	INNORMAL,
	INSIMPLESTRING,
	INCOMPLEXSTRING,
	INSIMPLECOMMENT,
	INCOMPLEXCOMMENT,
	INNUMBER,
	INID
};

enum lexeme
{
	QUOTE,
	SHARP,
	LEFTCURLY,
	RIGHTCURLY,
    OPENCOMPLEXCOMMENT,
	EOL,
	END,
	POINT,
	DIGIT,
	IDCHAR,
	CHAR
};

struct lextype
{
	lexeme lex;
	string val;
};

lextype readlexeme(bool peek)
{
	lextype l;
	l.val = " ";
    l.val[0] = cin.get();
	if(l.val[0] == char_traits<char>::eof())
	{
		l.val = "\0";
		l.lex = END;
		return l;
	}
	if(l.val[0] == '/')
	{
		if(cin.peek() == '/')
		{
			if(!peek)
				cin.get();
			l.val += '/';
			l.lex = OPENCOMPLEXCOMMENT;
		}
	}
	else
	{
		switch(l.val[0])
		{
		case '_':
			l.lex = IDCHAR;
			break;
		case '.':
			l.lex = POINT;
			break;
		case '#':
			l.lex = SHARP;
			break;
		case '{':
			l.lex = LEFTCURLY;
			break;
		case '}':
			l.lex = RIGHTCURLY;
			break;
		case '\'':
			l.lex = QUOTE;
			break;
		case '\n':
			l.lex = EOL;
			break;
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
			l.lex = DIGIT;
			break;
		default:
			if(isidchar(l.val[0]))
				l.lex = IDCHAR;
			else
				l.lex = CHAR;
			break;
		}
	}
	if(peek)
		cin.unget();
	return l;
}

inline lextype peeklexeme()
{
	return readlexeme(true);
}


inline lextype readlexeme()
{
	return readlexeme(false);
}
void main()
{	
	//freopen("input.txt","r",stdin);
	
	state context = INNORMAL;
	string buf;
	bool pointfound = false;
	lextype lex;
	while(true)
	{
		lex = readlexeme();
		if(lex.lex == END)
			return;
		switch(context)
		{
		case INNORMAL:
			switch(lex.lex)
			{
			case DIGIT:{
				lextype tmp = peeklexeme();
				if(tmp.lex == POINT || tmp.lex == DIGIT)
				{
					buf += lex.val;
					context = INNUMBER;
				}
				else
					cout << opennumber << lex.val << closespan;
				break;}
			
			case SHARP:
				if(peeklexeme().lex == DIGIT)
				{
					buf += lex.val;
					context = INCOMPLEXSTRING;
				}
				else
					cout << lex.val;
				break;
			case IDCHAR:{
				lextype tmp = peeklexeme();
				if(tmp.lex == IDCHAR || tmp.lex == DIGIT)
				{
					buf += lex.val;
					context = INID;
				}
				else
					cout << lex.val;
				break;}
			case LEFTCURLY:
				buf += lex.val;
				context = INSIMPLECOMMENT;
				break;
			case OPENCOMPLEXCOMMENT:
				buf += lex.val;
				context = INCOMPLEXCOMMENT;
				break;
			case QUOTE:
				buf += lex.val;
				context = INSIMPLESTRING;
				break;
			default:
				cout << lex.val;
				break;
			}
			break;
		case INID:{
			buf += lex.val;
			lextype tmp = peeklexeme();
			if(tmp.lex != IDCHAR && tmp.lex != DIGIT)
			{
				context = INNORMAL;
				if(iskeyword(buf))
					cout << openkeyword << buf << closespan;
				else
					cout << buf;
				buf = "";
			}
			break;}
		case INCOMPLEXSTRING:{
			buf += lex.val;
			if(peeklexeme().lex != DIGIT)
			{
				context = INNORMAL;
				cout << openstring << buf << closespan;
				buf = "";
			}
			break;}
		case INNUMBER:{
			if(lex.lex == DIGIT)
			{
				buf += lex.val;
				lextype tmp = peeklexeme();
				if(tmp.lex != DIGIT && tmp.lex != POINT)
				{
					pointfound = false;
					context = INNORMAL;
					cout << opennumber << buf << closespan;
					buf = "";
				}
				break;
			}
			if(lex.lex == POINT)
			{
				if(pointfound == false)
				{
					if(peeklexeme().lex == DIGIT)
					{
						pointfound = true;
						buf += lex.val;
						break;
					}
				}
			}
			pointfound = false;
			context = INNORMAL;
			cout << opennumber << buf << closespan;
			buf = "";
			cout << lex.val;
			break;}
		case INSIMPLESTRING:
			buf += lex.val;
			if(lex.lex == QUOTE)
			{
				context = INNORMAL;
				cout << openstring << buf << closespan;
				buf = "";
			}
			break;
		case INSIMPLECOMMENT:
			buf += lex.val;
			if(lex.lex == RIGHTCURLY)
			{
				context = INNORMAL;
				cout << opencomment << buf << closespan;
				buf = "";
			}
			break;
		case INCOMPLEXCOMMENT:
			if(lex.lex == EOL)
			{
				context = INNORMAL;
				cout << opencomment << buf << closespan;
				buf = "";
				cout << lex.val;
			}
			else
				buf += lex.val;
			break;
		}
	}
}
