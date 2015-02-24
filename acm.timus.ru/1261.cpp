#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

string ConvertToTernary(int n)
{
	string res;
	while(n != 0)
	{
		res += '0' + n%3;
		n /= 3;
	}
	reverse(res.begin(), res.end());
	return res;
}

int ConvertToDecimal(string ternary)
{
	int pows[16] = {1};
	for(int i = 1; i <= 15; i++)
		pows[i] = pows[i-1]*3;
	
	int res = 0;
	for(int i = ternary.length()-1; i >= 0; i--)
		res += pows[ternary.length()-1 - i]*(ternary[i]-'0');
	return res;
}


void main()
{
	int n;
	scanf("%d",&n);

	string tern = ConvertToTernary(n);
	int mod = 0;
	for(int i = tern.length()-1; i >= 0; i--)
	{
		if(tern[i] == '2' || (tern[i] == '1' && mod == 1))
		{
			tern[i] = '0';
			mod = 1;
		}
		else if(tern[i] == '0' && mod == 1)
		{
			tern[i] = '1';
			mod = 0;
		}
	}
	//if(mod != 0)
		tern.insert(0,"1");
	
	int res = ConvertToDecimal(tern);
	//printf("%s %s\n", tern.c_str(), ConvertToTernary(res - n).c_str());
	printf("%d %d",res,res-n);
}