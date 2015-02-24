#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> F[4];
string names[4] = {"Slytherin","Hufflepuff","Gryffindor","Ravenclaw"};

void main()
{
	int n;
	cin >> n;
	string name,fac;
	getline(cin,name);
	for(int i = 0; i < n; i++)
	{
		getline(cin,name);
		getline(cin,fac);
		for(int j = 0; j < 4; j++)
			if(fac == names[j])
			{
				F[j].push_back(name);
				break;
			}
	}
	for(int i = 0; i < 4; i++)
	{
		cout << names[i] << ":\n";
		for(int j = 0; j < F[i].size(); j++)
			cout << F[i][j] << endl;
		cout << endl;
	}
}