#include <cstdio>
#include <algorithm>
#define N 100002
using namespace std;

struct Lecture
{
	int Start, Finish;

	bool operator<(Lecture& l)
	{
		if(Finish != l.Finish)
			return Finish < l.Finish;
		return Start < l.Start;
	}
};

Lecture lectures[N];

void main()
{
	//freopen("input.txt","r",stdin);
	
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%d%d",&lectures[i].Start,&lectures[i].Finish);
	sort(lectures,lectures+n);

	int count = 1, m = 0;
	for(int i = 1; i < n; i++)
	{
		if(lectures[i].Start > lectures[m].Finish)
		{
			count++;
			m = i;
		}
	}
	printf("%d",count);
}