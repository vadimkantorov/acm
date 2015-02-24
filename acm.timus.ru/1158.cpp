#include <cstdio>
#include <queue>
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

const int N = 600;
const int M = 60;
const int AbcLen = 500;

struct AhoCorasick
{
	int trie[N][AbcLen];
	int fail[N];
	bool IsTerminal[N];
	int Size;

	AhoCorasick()
	{
		Size = 1;
		fill_n(fail,N,0);
		fill_n(IsTerminal,N,false);
		for(int i = 0; i < N; i++)
			fill_n(trie[i],AbcLen,-1);
	}

	void Insert(string& word)
	{
		int cur = 0;
		for(int i = 0; i < word.length(); i++)
		{
			int& dir = trie[cur][(unsigned char)word[i]];
			
			if(dir != -1)
				cur = dir;
			else
			{
				dir = Size;
				cur = Size++;
			}
		}
		IsTerminal[cur] = true;
	}

	int g(int pos, char c)
	{
		int dir = trie[pos][(unsigned char)c];
		if(pos == 0 && dir == -1)
			return 0;

		return dir;
	}

	void Preprocess(string& abc)
	{
		queue<int> Q;
		
		for(int i = 0; i < abc.length(); i++)
		{
			int dest = g(0,abc[i]);
			if(dest != 0)
				Q.push(dest);
		}
		
		while(!Q.empty())
		{
			int cur = Q.front();
			Q.pop();

			for(int i = 0; i < abc.length(); i++)
			{
				char c = abc[i];
				int dest = g(cur,c);
				if(dest != -1)
				{
					Q.push(dest);
					int f = fail[cur];
					while(g(f,c) == -1)
						f = fail[f];
					fail[dest] = g(f,c);
					if(IsTerminal[fail[dest]])
						IsTerminal[dest] = true;
				}
			}
		}
	}

	int GoTo(int pos, char c)
	{
		if(g(pos,c) != -1)
			return g(pos,c);
		
		int f = fail[pos];
		while(g(f,c) == -1)
			f = fail[f];
		return g(f,c);
	}
};

AhoCorasick searcher;
string abc;
int m;

struct BigInteger
{
	static const int Len = 100;
	char M[Len];

	BigInteger()
	{
		*this = 0;
	}
	
	void Print()
	{
		bool print = false;
		for(int i = Len-1; i >= 0; i--)
		{
			if(M[i] != 0 || i == 0)
				print = true;
			if(print)
				putchar('0'+M[i]);
		}
	}

	void operator=(int x)
	{
		fill_n(M,Len,0);
		M[0] = x;
	}

	void operator+=(BigInteger& x)
	{
		int carry = 0;
		for(int i = 0; i < Len; i++)
		{
			int newcarry = (M[i] + x.M[i] + carry)/10;
			M[i] = (M[i] + x.M[i] + carry)%10;
			carry = newcarry;
		}
	}
};

BigInteger dp1[N], dp2[N];

BigInteger& DP()
{
	BigInteger *work = dp2, *old = dp1;
	
	for(int i = 0; i < searcher.Size; i++)
		old[i] = 1;
	
	for(int eaten = m-1; eaten >= 0; eaten--)
	{
		for(int pos = 0; pos < searcher.Size; pos++)
		{
			work[pos] = 0;
			for(int i = 0; i < abc.length(); i++)
			{
				int dest = searcher.GoTo(pos, abc[i]);
				if(!searcher.IsTerminal[dest])
					work[pos] += old[dest];
			}
		}
		swap(work, old);
	}
	return old[0];
}

void main()
{
	//freopen("input.txt","r",stdin);
	
	int n,p;
	scanf("%d%d%d\n",&n,&m,&p);

	getline(cin,abc);

	for(int i = 0; i < p; i++)
	{
		string word;
		getline(cin,word);
		searcher.Insert(word);
	}

	searcher.Preprocess(abc);
	DP().Print();
}