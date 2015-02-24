#include <cstdio>
#include <algorithm>
#include <vector>
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

vector<Lecture> res;

void main()
{
	//freopen("input.txt","r",stdin);
	
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
	{
		int s,f;
		scanf("%d%d",&s,&f);
		lectures[i].Start = min(s,f);
		lectures[i].Finish = max(s,f);
	}
	sort(lectures,lectures+n);

	res.push_back(lectures[0]);
	int m = 0;
	for(int i = 1; i < n; i++)
	{
		if(lectures[i].Start >= lectures[m].Finish)
		{
			res.push_back(lectures[i]);
			m = i;
		}
	}
	printf("%d\n",res.size());
	for(int i = 0; i < res.size(); i++)
		printf("%d %d\n",res[i].Start,res[i].Finish);
}