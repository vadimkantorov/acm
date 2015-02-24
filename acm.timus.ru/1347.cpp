#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

string tmp;
struct blogger
{
	string name;
	vector<string> frs;

	blogger(string _name) : name(_name)	{ }
	void addfriend(string fr)
	{
		if(fr != name && find(frs.begin(), frs.end(),  tmp) == frs.end())
			frs.push_back(tmp);
	}
	void sort()
	{
		std::sort(frs.begin(), frs.end());
	}
};
typedef vector<blogger> frm;
frm friends;


string readuntil(char c)
{
	tmp = "";
	char ch;
	while((ch=getchar()) != c)
		tmp += ch;
	return tmp;
}

void main()
{
	//freopen("input.txt","r",stdin);
	
	int n;
	cin >> n;
	getline(cin,tmp);
	int curblogger = -1;
	for(int i = 0; i < n; i++)
	{
		string name;
		getline(cin,name);
		friends.push_back(blogger(name));
		curblogger = friends.size()-1;
		while(true)
		{
			readuntil('<');
			tmp = readuntil('>');
			if(tmp == "friend")
			{
				tmp = readuntil('<');
				friends[curblogger].addfriend(tmp);
				readuntil('>');
			}
			else if(tmp == "/blog")
			{
				getline(cin,tmp);
				break;
			}
		}
	}

	for(int i = 0; i < friends.size(); i++)
		friends[i].sort();

	for(frm::iterator i = friends.begin(); i != friends.end(); i++)
	{	
		if(i != friends.begin())
			cout << endl << endl;
		
		cout << i->name << endl;
		
		bool first = true;
		cout << "1: ";
		for(int j = 0; j < (i->frs).size(); j++)
		{
			if(first)
			{
				cout << (i->frs)[j];
				first = false;
			}
			else
				cout << ", " << (i->frs)[j];
		}
		first = true;
		cout << endl << "2: ";
		
		vector<string> frof;

		for(frm::iterator j = friends.begin(); j != friends.end();j++)
		{
			vector<string>::iterator fr = find((j->frs).begin(),(j->frs).end(),i->name);
			if(fr != (j->frs).end())
			{
				frof.push_back(j->name);
			}
		}

		sort(frof.begin(), frof.end());

		for(int j = 0; j < frof.size(); j++)
		{
			if(first)
			{
				cout << frof[j];
				first = false;
			}
			else
				cout << ", " << frof[j];
		}

		cout << endl << "3: ";
		first = true;
		for(vector<string>::iterator j = (i->frs).begin(); j != (i->frs).end(); j++)
		{
			frm::iterator it = friends.end();
			for(frm::iterator k = friends.begin(); k != friends.end(); k++)
				if(k->name == *j)
				{
					it = k;
					break;
				}
			if(it != friends.end())
			{
				vector<string>::iterator fr = find((it->frs).begin(), (it->frs).end(), i->name);
				if(fr  != (it->frs).end())
				{
					if(first)
					{
						cout << *j;
						first = false;
					}
					else
						cout << ", " << *j;
				}
			}
		}
	}
}