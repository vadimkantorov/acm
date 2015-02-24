#include <cstdio>
#include <cmath>
using namespace std;

unsigned long long int A[2][111112];
int k,n;
int last = 0;
void init()
{
	int a,b,cur;
	scanf("%d",&n);
	k = (int)ceil( ((double)n)/19 );
	cur = k - 1;
	last = n%19;
	if(last == 0) last = 19;
	for(int i = 0; i < last; i++)
	{
		scanf("%d %d",&a,&b);

		A[0][cur] = A[0][cur]*10 + a;
		A[1][cur] = A[1][cur]*10 + b;
	}
	cur--;

	for(int i = last; i < n; i+= 19,cur--)
	{
		for(int j = 0; j < 19; j++)
		{
			scanf("%d %d",&a,&b);

			A[0][cur] = A[0][cur]*10 + a;
			A[1][cur] = A[1][cur]*10 + b;
		}
	}
}
int digitscount(unsigned long long p)
{
	int count = 0;
	while(p / 10 != 0)
	{
		p/=10;
		count++;
	}
	return ++count;
}
void OutDigit(unsigned long long* p,int digits)
{
	int digs = digitscount(*p);
	for(int i = 0; i < digits-digs; i++)
	{
		printf("0");
	}
	printf("%I64u",*p);
}
void out()
{
	if(k != 1)
	{
		OutDigit(&A[1][k-1],last);
		for(int i = k-2; i >= 0; i--)
		{
			OutDigit(&A[1][i],19);
		}
	}
	else
	{
		OutDigit(&A[1][0],n);
	}
}

void main()
{
	init();
	int carry = 0,newcarry = 0;
	for(int i = 0; i < k; i++)
	{
		newcarry = (A[0][i] + A[1][i] + carry)/10000000000000000000;
		A[1][i] = (A[0][i] + A[1][i] + carry)%10000000000000000000;
		carry = newcarry;
	}
	out();
}