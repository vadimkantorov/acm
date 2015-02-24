#include <cstdio>
#include <vector>
#include <algorithm>
#define N 102
using namespace std;

struct Official
{
	int Day;
	vector<int> RequiredDocs;

	bool CanGetDoc(vector<int>& docs, int day)
	{
		if(day != Day)
			return false;
		for(int i = 0; i < RequiredDocs.size(); i++)
			if(find(docs.begin(), docs.end(), RequiredDocs[i]) == docs.end())
				return false;
		return true;
	}
};

Official A[N];
vector<int> docs, toget, newdocs;

void main()
{
	freopen("input.txt","r",stdin);
	
	int n,l,day,tmp;

	scanf("%d%d",&n,&l);
	for(int i = 0; i < n; i++)
		scanf("%d",&A[i].Day);
	for(int i = 0; i < n; i++)
	{
		scanf("%d",&tmp);
		while(tmp != 0)
		{
			A[i].RequiredDocs.push_back(tmp);
			scanf("%d",&tmp);
		}
	}
	scanf("%d",&day);
	scanf("%d",&tmp);
	while(tmp != 0)
	{
		docs.push_back(tmp);
		scanf("%d",&tmp);
	}
	scanf("%d",&tmp);
	while(tmp != 0)
	{
		toget.push_back(tmp);
		scanf("%d",&tmp);
	}

	for(int i = 0; i < docs.size(); i++)
		for(int j = 0; j < toget.size(); j++)
			toget.erase(remove(toget.begin(), toget.end(), docs[i]), toget.end());
	
	int daysneeded = 0;
	for(int i = 0; i < 10000; i++)
	{
		for(int j = 0; j < n; j++)
		{
			if(find(docs.begin(), docs.end(), j+1) == docs.end() && A[j].CanGetDoc(docs,day))
			{
				docs.push_back(j+1);
				newdocs.push_back(j+1);
				toget.erase(remove(toget.begin(), toget.end(), j+1),toget.end());
				break;
			}
		}
		if(!toget.empty())
			daysneeded++;
		else
			break;
		if(day == l-1)
			day = l;
		else
			day = (day+1)%l;
	}

	if(!toget.empty())
		puts("No Solution");
	else
	{
		printf("%d\n",daysneeded);
		for(int i = 0; i < newdocs.size(); i++)
			printf("%d ",newdocs[i]);
	}
}