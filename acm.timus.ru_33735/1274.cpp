#include <cstdio>
#include <cmath>

struct Fraction
{
	int numerator;
	int denominator;
	
	Fraction() { }
	Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator) { }

	void Reduce()
	{
		int a = abs(numerator), b = abs(denominator), c;
		while((c = a%b) != 0)
		{
			a = b;
			b = c;
		}

		numerator /= b;
		denominator /= b;

		if(	(numerator < 0 && denominator < 0) ||
			(numerator > 0 && denominator < 0) )
		{
			numerator *= -1;
			denominator *= -1;
		}
	}

	void Scan()
	{
		int intPart, num, denom, sign = 1;

		char tmp = getchar();
		if(tmp == '-')
			sign = -1;
		else
			ungetc(tmp, stdin);

		scanf("%d",&intPart);
		tmp = getchar();
		if(tmp == ' ')
			scanf("%d/%d\n",&num,&denom);
		else if(tmp != '\n' && tmp != '\0')
		{
			num = intPart;
			intPart = 0;
			scanf("%d\n",&denom);
		}
		else
		{
			num = 0;
			denom = 1;
		}

		numerator = sign*(intPart*denom + num);
		denominator = denom;
		
		Reduce();
	}

	void Print()
	{
		if(numerator < 0)
		{
			numerator *= -1;
			putchar('-');
		}
		
		int intPart = numerator / denominator;
		if(numerator == 0)
			putchar('0');
		else
		{
			if(intPart != 0)
				printf("%d ",intPart);
			if(intPart*denominator != numerator)
				printf("%d/%d",numerator - intPart*denominator,denominator);
		}
	}

	Fraction operator*(Fraction f)
	{
		Fraction res(numerator * f.numerator, denominator*f.denominator);
		res.Reduce();
		return res;
	}

	Fraction operator+(Fraction f)
	{
		Fraction res(numerator*f.denominator + denominator*f.numerator, denominator*f.denominator);
		res.Reduce();
		return res;
	}

	Fraction operator-(Fraction f)
	{
		f.numerator *= -1;
		return (*this)+f;
	}

	Fraction operator/(Fraction f)
	{
		return (*this)*Fraction(f.denominator, f.numerator);
	}
};

void main()
{
	freopen("input.txt", "r", stdin);
	
	Fraction A,B;
	char oper;

	A.Scan();
	scanf("%c\n", &oper);
	B.Scan();
	
	switch(oper)
	{
	case '+':
		(A+B).Print();
		break;
	case '*':
		(A*B).Print();
		break;
	case '-':
		(A-B).Print();
		break;
	case '/':
		(A/B).Print();
		break;
	}
}