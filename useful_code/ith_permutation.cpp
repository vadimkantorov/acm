#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int C[30], M[30];

__int64 Factorial(int n)
{
	__int64 res = 1;
	for(int i = 2; i <= n; i++)
		res *= i;
	return res;
}

void PrintIthPerm(string s, int n)
{
	string res;
	
	for(int i = 0; i < s.length(); i++)
		C[s[i]-'a']++;

	for(int i = 0; i < s.length(); i++)
	{
		fill_n(M,30,0);

		for(int j = 0; j < 26; j++)
		{
			if(C[j] != 0)
			{
				int letBefore = -1;
				for(int k = j-1; k >= 0; k--)
				{
					if(M[k] != 0)
					{
						letBefore = k;
						break;
					}
				}
				if(letbefore == -1)
				{
				M[j] += M[letBefore];
				__int64 sum = 0;
				__int64 product = 1;
				for(int k = 0; k < 26; k++)
				{
					if(k != letBefore)
					{
						sum += C[k];
						product *= Factorial(C[k]);
					}
				}
				__int64 perms = Factorial(sum)/product;
				M[j] += perms;
				if(n <= M[j])
				{
					C[j]--;
					n -= M[j];
					res += ('a' + j);
				}
			}
		}
	}
	printf("%s",res.c_str());
}

void main()
{
	PrintIthPerm("abca",1);
}