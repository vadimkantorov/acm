#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

string A(int n)
{
	string res = "sin(1";
	bool minus = true;
	char str[] = "sin(xxx";
	for(int i = 2; i <= n; i++)
	{
		if(minus)
			res += '-';
		else
			res += '+';
		sprintf(str,"sin(%d",i);
		res += string(str);
		minus = !minus;
	}
	for(int i = 0; i < n; i++)
		res += ')';
	return res;
}

string S(int n)
{
	string res;
	for(int i = 1; i <= n-1; i++)
		res += '(';
	char str[] = "+xxx)";
	for(int i = 1; i <= n-1; i++)
	{
		res += A(i);
		sprintf(str,"+%d)",n+1-i);
		res += string(str);
	}
	return res + A(n) + "+1";
}

void main()
{
	int n;
	cin >> n;
	cout << S(n);
}