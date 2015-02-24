#include <cstring>
#include <cstdio>
#include <queue>
#include <bitset>
using namespace std;

struct Node
{
	int LeftSon;
	int RightSibling;
	int Final;
	int Fail;
	char Label;

	bitset<260> helper;

	Node() : LeftSon(-1), RightSibling(-1), Final(0), Label('\0'), Fail(0)
	{
	}
};

Node trie[100005];
int nodeCnt = 1;

void AddWord2(char* word)
{
	int ver = 0, len = strlen(word);
	for(int i = 0; i < len; i++)
	{
		bool found = false;
		int prev = -1;
		for(int son = trie[ver].LeftSon; son != -1; son = trie[son].RightSibling)
		{
			prev = son;
			if(trie[son].Label == word[i])
			{
				found = true;
				ver = son;
				break;
			}
		}
		if(!found)
		{
			trie[ver].helper[word[i]+128] = true;
			trie[nodeCnt].Label = word[i];

			if(prev == -1)
				trie[ver].LeftSon = nodeCnt;
			else
				trie[prev].RightSibling = nodeCnt;
			
			ver = nodeCnt++;
		}
	}
	trie[ver].Final = len;
}

void AddWord(char* word)
{
	int ver = 0, len = strlen(word);
	for(int i = 0; i < len; i++)
	{
		bool found = false;
		for(int son = trie[ver].LeftSon; son != -1; son = trie[son].RightSibling)
		{
			if(trie[son].Label == word[i])
			{
				found = true;
				ver = son;
				break;
			}
		}
		if(!found)
		{
			trie[ver].helper[word[i]+128] = true;
			trie[nodeCnt].RightSibling = trie[ver].LeftSon;
			trie[nodeCnt].Label = word[i];
			trie[ver].LeftSon = nodeCnt;
			ver = nodeCnt++;
		}
	}
	trie[ver].Final = len;
}

int GoTo(int u, char c)
{
	static prevu = -1;
	static char prevc = '\0';
	static int prevres = -2;
	
	if(prevres != -2 && prevu == u && prevc == c)
		return prevres;

	prevu = u;
	prevc = c;
	
	if(trie[u].helper[c + 128])
	{
		for(int son = trie[u].LeftSon; son != -1; son = trie[son].RightSibling)
		{
			if(trie[son].Label == c)
			{
				prevres = son;
				return prevres;
			}
		}
	}
	prevres = u == 0 ? 0 : -1;
	return prevres;
}

void ComputeFail()
{
	queue<int> Q;
	for(int son = trie[0].LeftSon; son != -1; son = trie[son].RightSibling)
	{
		trie[son].Fail = 0;
		Q.push(son);
	}

	while(!Q.empty())
	{
		int r = Q.front();
		Q.pop();

		for(int son = trie[r].LeftSon; son != -1; son = trie[son].RightSibling)
		{
			char a = trie[son].Label;
			int u = son;
			Q.push(u);
			int ver = trie[r].Fail;
			while(GoTo(ver,a) == -1)
				ver = trie[ver].Fail;
			trie[u].Fail = GoTo(ver,a);

			int& fu = trie[u].Final;
			int ffu = trie[trie[u].Fail].Final;
			if(ffu > fu)
				fu = ffu;
		}
	}
}

char S[900005];
void main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	int n,m;
	scanf("%d",&n);
	
	getchar();
	for(int i = 0; i < n; i++)
	{
		gets(S);
		AddWord2(S);
	}
	ComputeFail();
	//puts("5401 14");
	//exit(0);
	scanf("%d",&m);
	getchar();
	for(int j = 1; j <= m; j++)
	{
		gets(S);
		int ver = 0;
		int len = strlen(S);

		for(int i = 0; i < len; i++)
		{
			int tmp;
			while( GoTo(ver,S[i]) == -1)
				ver = trie[ver].Fail;
			ver = GoTo(ver,S[i]);
			if(trie[ver].Final != 0)
			{
				int minlen = 0;
				int minend = 1e9;
				while(i < len && ver != -1)
				{
					int fin = trie[ver].Final;
					if(fin != 0)
					{
						minend = i;
						minlen = fin;
					}

					ver = GoTo(ver,S[++i]);
				}
				printf("%d %d",j,minend+1-minlen+1);
				return;
			}
		}
	}
	puts("Passed");
}