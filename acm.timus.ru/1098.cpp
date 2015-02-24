#include <cstdio>
#include <cstring>
using namespace std;
char S[30010];
int g(int x,int n)
{
	return (x%n==0)?n:x%n;
}
void main()
{
	
	for(int i =0;scanf("%c",&S[i])>0;)
	{
		if(S[i] != '\n')
			i++;
		else
			S[i] = '\0';
	}
	int n=strlen(S),k=1999,prev,next;
	next = (k%2 == 0)?1:2;
	if(n==1)
		next = 1;
	for(int i = 3; i<=n;i++)
	{
        prev=next;
		next=g((prev+k),i);
	}
	switch(S[next-1])
	{
	case '?':
		printf("Yes");
		break;
	case ' ':
		printf("No");
		break;
	default:
		printf("No comments");
		break;		
	}
}