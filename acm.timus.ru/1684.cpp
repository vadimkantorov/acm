#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

const int N = 200000;

char S[N];
int len, pf[N];

vector<string> res;

void ComputePrefixFunction()
{
	int k = pf[0] = pf[1] = 0;

	for(int i = 2; i <= len; i++)
	{
		while(k > 0 && S[k] != S[i-1])
			k = pf[k];
		if(S[k] == S[i-1])
			k++;
		
		pf[i] = k;
	}
}

void main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	
	gets(S);
	int slen = strlen(S);
	S[slen] = '$';
	gets(S + slen + 1);

	len = strlen(S);

	ComputePrefixFunction();

	for(int i = len; S[i-1] != '$'; i -= pf[i])
	{
		if(pf[i] == 0)
		{
			puts("Yes");
			return;
		}

		string prefix;
		for(int j = i-pf[i]; j <= i-1; j++)
			prefix += S[j];

		res.push_back(prefix);
	}

	puts("No");
	for(int i = res.size() -1; i >= 0; i--)
		printf("%s ",res[i].c_str());
}