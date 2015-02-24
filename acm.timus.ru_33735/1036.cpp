#include <stdio.h>
#define N 100
struct bigint
{
	__int16 D[2*N];
	
	bigint()
	{
		for(int i = 0 ;i < N; i++) D[i] = 0;
	}

	void normalize()
	{
		int carry = 0, tmp;
		for(int i = 0; i < N; i++)
		{
			tmp = carry;
			carry = (tmp + D[i]) / 10;
			D[i] = (tmp + D[i]) % 10;
		}
	}
	
	void operator+= (bigint& x)
	{
		for(int i = 0; i < N; i++)
			D[i] += x.D[i];
		
		normalize();
	}
	
	bigint operator* (bigint& x)
	{
		bigint res;
		for(int i =0; i < N; i++)
			for(int j =0; j < N; j++)
				res.D[i+j] += D[i]*x.D[j];
		res.normalize();
		return res;
	}
	void print()
	{
		int i = N-1;
		for(; i >= 0 && D[i] == 0;) i--;
		if(i == -1) {printf("0"); return;}
		for(; i >= 0; i--)
			printf("%d",(int)D[i]);
	}
	
	void assign(__int16 c)
	{
		D[0] = c;
	}

};

bigint A[2][502];

void main()
{
	int n,k;
	scanf("%d %d",&n, &k);
	if(k % 2 == 1) {printf("0");return; };
	k /= 2;

	bigint one,zero;
	one.assign(1);
	for(int i = 0; i < 10; i++)
		A[0][i] = one;

	for(int i = 2; i <= n; i++)
	{
		for(int s = 0; s <= k; s++)
		{
			for(int j = 0; j <= 9 && s >= j; j++)
			{
				A[1][s] += A[0][s-j];
			}
		}
		
		//bigint* tmp = A[0];
		//A[0] = A[1];
		//A[1] = tmp;
		
		for(int i = 0; i <= k; i++)
		{
			A[0][i] = A[1][i];
			A[1][i] = zero;
		}
	}
	bigint res = A[0][k]*A[0][k];
	res.print();
}