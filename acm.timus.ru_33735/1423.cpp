#include <cstdio>
#include <cstring>
const int NMAX = 250003;
char T[2*NMAX],P[NMAX];
int prf[NMAX];

void ComputePrefixFunction()
{
	int m = strlen(P);
	prf[1] = 0;
	int k = 0;

	for(int i = 2; i <= m; i++)
	{
		while(k > 0 && P[i-1] != P[k])
			k = prf[k];
		if(P[i-1] == P[k])
			k++;
		
		prf[i] = k;
	}
}

int KMP()
{
	int n = strlen(T), m = strlen(P);
	if(n < m)
		return -1;

	ComputePrefixFunction();
	int k = 0;
	for(int j = 0; j < n; j++)
	{
		while(k > 0 && T[j] != P[k])
			k = prf[k];
		if(T[j] == P[k])
			k++;
		if(k == m)
			return j-m+1;
	}

	return -1;
}

void main()
{
	//freopen("input.txt","r",stdin);
	
	int n;
	scanf("%d\n",&n);
	gets(T);
	strncat(T,T,strlen(T));
	gets(P);
	
	int kmp = KMP();
	if(kmp == -1)
		puts("-1");
	else
		printf("%d",(n-kmp)%n);
}