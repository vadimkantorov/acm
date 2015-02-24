#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

enum VertexState
{
	NOTDISCOVERED,
	DISCOVERED,
	FINISHED	
};

struct SampleNecrologue
{
	int M[11];
	string contents;
	
	void Scan()
	{		
		string str;
		while(true)
		{
			getline(cin,str);
			if(str.length() > 0 && str[str.length()-1] == '#')
			{
				contents += str.substr(0, str.length()-1);
				break;
			}
			else
				contents += str + '\n';
		}

		fill(M,M+10,0);
		for(int i = 0; i < contents.length(); i++)
			if(contents[i] == '*')
				M[contents[++i]-'0'-1]++;
	}

	void Print();
};

SampleNecrologue necro[11];

void SampleNecrologue::Print()
{
	for(int i = 0; i < contents.length(); i++)
	{
		if(contents[i] == '*')
			necro[contents[++i]-'0'-1].Print();
		else
			putchar(contents[i]);
	}
}

VertexState color[11];

int DFS(int start)
{
	color[start] = DISCOVERED;
	
	int tmp = necro[start].contents.length();
	for(int i = 0; i < 10; i++)
		tmp -= necro[start].M[i]*2;
	
	for(int i = 0; i < 10; i++)
	{
		if(necro[start].M[i] != 0)
		{
			if(color[i] != DISCOVERED)
			{
				tmp += necro[start].M[i]*DFS(i);
				tmp = min(tmp,1000002);
			}
			else
				return 1000002;
		}
	}
	
	color[start] = FINISHED;
	return min(tmp, 1000002);
}

void main()
{
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	
	int n;
	scanf("%d\n",&n);
	for(int i = 0; i < n; i++)
	{
		necro[i].Scan();
		color[i] = NOTDISCOVERED;
	}
	
	if(DFS(0) <= 1000000)
		necro[0].Print();
	else
		putchar('#');
}