#include <string>
#include <iostream>
#include <vector>

using namespace std;

vector<string> dict;

string test(string word)
{
	string repl = word;
	for(int i = 0; i < dict.size(); i++)
	{
		if(word.length() == dict[i].length())
		{
			int count = 0;
			for(int j = 0; j < word.length(); j++)
				if(word[j] != dict[i][j]) count++;
			if(count == 1)
			{
				repl = dict[i];
				break;
			}
		}
	}
	return repl;
}

bool issmall(char c)
{
	return (c >= 'a' && c <= 'z');
}

void main()
{
	bool in_word = false;
	int errc = 0;
	string word,repl;
	char c;	

	while( true )
	{
		cin >> repl;
		if(repl == "#")
		{
			cin.get();
			break;
		}
		dict.push_back(repl);
	}
	
	while(true)
	{
		c = cin.get();
		if(c == -1) break;
		if(in_word)
		{
			if(issmall(c))
				word += c;
			else
			{
				in_word = false;
				repl = test(word);
				if(repl != word) errc++;
				cout << repl << c;
			}
		}
		else
		{
			if(issmall(c))
			{
				in_word = true;
				word = "";
				word += c;
			}
			else
				cout << c;
		}
	}
	cout << errc;
}