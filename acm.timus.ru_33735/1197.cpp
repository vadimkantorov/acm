#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

void main()
{
	int n,k;
	cin>>n;
	string s;
	char c;
	for( int i = 0; i < n; i++ )
	{
		cin>>s;
		c = s[0];
		k=s[1]-48;
		switch(c)
		{
		case 'a':
		case 'h':
			switch(k)
			{
			case 1:
			case 8:
				cout<<2;
				break;
			case 2:
			case 7:
				cout<<3;
				break;
			default:
				cout<<4;
				break;
			}
			break;
		case 'b':
		case 'g':
			switch(k)
			{
			case 1:
			case 8:
				cout<<3;
				break;
			case 2:
			case 7:
				cout<<4;
				break;
			default:
				cout<<6;
				break;
			}
			break;
		default:
			switch(k)
			{
			case 1:
			case 8:
				cout<<4;
				break;
			case 2:
			case 7:
				cout<<6;
				break;
			default:
				cout<<8;
				break;
			}
			break;
		}
		cout<<endl;
	}
}