#include <cstdio>
#include <cstring>

char str[10002];

bool IsPalindrome(int l, int r)
{
	for(int i = 0; i < r-l; i++)
	{
		if(str[l + i] != str[r - i])
			return false;
	}
	return true;
}

int FindLongestPalindromeFromRight()
{
	int len = strlen(str);
	int befbeg = len-1;
	int beg = len-1;
	for(int i = len-1; i >= len/2 ; i--)
	{
		if(IsPalindrome(i - (len-1 - i),len-1))
		{
			befbeg = beg;
			beg = i - (len-1 - i);
		}
		if(IsPalindrome(i - (len-1 - i)-1,len-1))
		{
			befbeg = beg;
			beg = i - (len-1 - i)-1;
		}
	}
	if(beg == 0)
		beg = befbeg;
	return beg;
}

void main()
{
	//freopen("input.txt","r",stdin);
	
	gets(str);
	printf("%s",str);
	if(strlen(str) != 1)
	{
		int beg = FindLongestPalindromeFromRight();
		for(int i = beg-1;i >= 0; i--) putchar(str[i]);
	}
	else
		putchar(str[0]);
}