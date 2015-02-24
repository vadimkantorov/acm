#include <cstdio>

enum lexeme
{
	IN,
	OUT,
	PUT,
	ON,
	E,
	FUCK,
	EOL,
	NIL
};

lexeme buf = NIL;

void unreadlexeme(lexeme l)
{
	buf = l;
}

lexeme readlexeme(bool peek)
{
	lexeme l;
	if(buf != NIL)
	{
		l = buf;
		if(!peek)
			buf = NIL;
	}
	else{
	char c = getchar();
	switch(c)
	{
	case EOF:
	case '\n':
		l = EOL;
		break;
	case 'e':
		l = E;
		break;
	case 'p':{
		char c1 = getchar(), c2 = getchar();
		if(c1 != 'u' || c2 != 't')
		{
			l = FUCK;
			ungetc(c2,stdin);
			ungetc(c1,stdin);
		}
		else
			l = PUT;
		break;}
	case 'i':{
		char c1 = getchar();
		if(c1 != 'n')
		{
			l = FUCK;
			ungetc(c1,stdin);
		}
		else
			l = IN;
		break;}
	case 'o':{
		char c1 = getchar();
		if(c1 == 'n')
			l = ON;
		else
		{
			char c2 = getchar();
			if(c1 != 'u' || c2 != 't' )
			{
				l = FUCK;
				ungetc(c2,stdin);
				ungetc(c1,stdin);
			}
			else
				l = OUT;
		}
		break;}
	default:
		l = FUCK;
		break;
	}
	if(peek)
		ungetc(c,stdin);}
	return l;
}

lexeme peeklexeme()
{
	return readlexeme(true);
}

lexeme readlexeme()
{
	return readlexeme(false);
}

enum state
{
	AFTER_IO,

	AFTER_IOPUT,
	AFTER_IOPUTON,

	AFTER_PUT,
	AFTER_ON,

	COMMON
};
inline void yes()
{
	puts("YES");
}
inline void no()
{
	puts("NO");
}
void main()
{
	//freopen("input.txt","r",stdin);
	
	int n;
	scanf("%d\n",&n);
	state context;
	lexeme l;
	for(int i = 0; i < n; i++)
	{
		context = COMMON;
		while( true )
		{
			l = readlexeme();
			if(l == EOL)
			{
				if(context != AFTER_ON && context != AFTER_PUT )
					yes();
				else
					no();
				break;
			}
			if(l == FUCK)
			{
				no();
				while(readlexeme() != EOL);
				break;
			}
			switch(context)
			{
			case COMMON:
				switch(l)
				{
				case IN:
				case OUT:			
					context = AFTER_IO;
					break;
				case PUT:
					context = AFTER_PUT;
					break;
				case ON:
					context = AFTER_ON;
					break;
				default:
					unreadlexeme(FUCK);
					break;
				}
				break;
			case AFTER_ON:
				if(l != E)
					unreadlexeme(FUCK);
				else
					context = COMMON;
				break;
			case AFTER_PUT:
				if(l != ON)
					unreadlexeme(FUCK);
				else
					context = COMMON;
				break;
			case AFTER_IO:
				if(l != PUT)
				{
					context = COMMON;
					unreadlexeme(l);
				}
				else
					context = AFTER_IOPUT;
				break;
			case AFTER_IOPUT:
				if(l != ON)
				{
					context = COMMON;
					unreadlexeme(l);
				}
				else
					context = AFTER_IOPUTON;
				break;
			case AFTER_IOPUTON:
				if(l != E)
					unreadlexeme(l);
				context = COMMON;
				break;
			}
		}
	}
}