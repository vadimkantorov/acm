#include "stdafx.h"
#include <iostream>
using namespace std;
int zeros = 0;
int ones = 0;
int twos = 0;
int threes = 0;
int fours = 0;
int fives = 0;
int sixes = 0;
int sevens = 0;
int eights = 0;
int nines = 0;
void F(int n)
{
	while(n!=0)
	{
		switch(n%10)
		{
		case 0:
			zeros++;
			break;
		case 1:
			ones++;
			break;
		case 2:
			twos++;
			break;
		case 3:
			threes++;
			break;
		case 4:
			fours++;
			break;
		case 5:
			fives++;
			break;
		case 6:
			sixes++;
			break;
		case 7:
			sevens++;
			break;
		case 8:
			eights++;
			break;
		default:
			nines++;
			break;
		}
		n/=10;
	}
}
void main()
{
	int n;
	cin>>n;
	//обработка единиц
	switch(n%10)
	{
	case 1:
		ones++;
		break;
	case 2:
		ones++;
		twos++;
		break;
	case 3:
		ones++;
		twos++;
		threes++;
		break;
	case 4:
		ones++;
		twos++;
		threes++;
		fours++;
		break;
	case 5:
		ones++;
		twos++;
		threes++;
		fours++;
		fives++;
		break;
	case 6:
		ones++;
		twos++;
		threes++;
		fours++;
		fives++;
		sixes++;
		break;
	case 7:
		ones++;
		twos++;
		threes++;
		fours++;
		fives++;
		sixes++;
		sevens++;
		break;
	case 8:
		ones++;
		twos++;
		threes++;
		fours++;
		fives++;
		sixes++;
		sevens++;
		eights++;
		break;
	case 9:
		ones++;
		twos++;
		threes++;
		fours++;
		fives++;
		sixes++;
		sevens++;
		eights++;
		nines++;
		break;
	}
	int b = (n-n%10)/10;
	for(int i = 0; i < b; i++)
	{
		zeros++;
		ones++;
		twos++;
		threes++;
		fours++;
		fives++;
		sixes++;
		sevens++;
		eights++;
		nines++;
	}
	//обработка единиц закончена
	
	//обработка десятков
	switch((n%100)/10)
	{
	case 1:
		ones += n%10+1;
		break;
	case 2:
		ones += 10;
		twos+= n%10+1;
		break;
	case 3:
		ones += 10;
		twos += 10;
		threes += n%10+1;
		break;
	case 4:
		ones += 10;
		twos += 10;
		threes += 10;
		fours += n%10+1;;
		break;
	case 5:
		ones += 10;
		twos += 10;
		threes += 10;
		fours += 10;
		fives += n%10+1;;
		break;
	case 6:
		ones += 10;
		twos += 10;
		threes += 10;
		fours += 10;
		fives += 10;
		sixes += n%10+1;;
		break;
	case 7:
		ones += 10;
		twos += 10;
		threes += 10;
		fours += 10;
		fives += 10;
		sixes += 10;
		sevens += n%10+1;;
		break;
	case 8:
		ones += 10;
		twos += 10;
		threes += 10;
		fours += 10;
		fives += 10;
		sixes += 10;
		sevens += 10;
		eights += n%10+1;;
		break;
	case 9:
		ones += 10;
		twos += 10;
		threes += 10;
		fours += 10;
		fives += 10;
		sixes += 10;
		sevens += 10;
		eights += 10;
		nines += n%10+1;;
		break;
	}
	b = (n-n%100)/100;
	for(int i = 0; i < b; i++)
	{
		zeros+=10;
		ones+=10;
		twos+=10;
		threes+=10;
		fours+=10;
		fives+=10;
		sixes+=10;
		sevens+=10;
		eights+=10;
		nines+=10;
	}

	//обработка десятков закончена
	//обработка сотен
	switch((n%1000)/100)
	{
	case 1:
		ones += n%100+1;
		break;
	case 2:
		ones += 100;
		twos+= n%100+1;
		break;
	case 3:
		ones += 100;
		twos += 100;
		threes += n%100+1;
		break;
	case 4:
		ones += 100;
		twos += 100;
		threes += 100;
		fours += n%100+1;;
		break;
	case 5:
		ones += 100;
		twos += 100;
		threes += 100;
		fours += 100;
		fives += n%100+1;;
		break;
	case 6:
		ones += 100;
		twos += 100;
		threes += 100;
		fours += 100;
		fives += 100;
		sixes += n%100+1;;
		break;
	case 7:
		ones += 100;
		twos += 100;
		threes += 100;
		fours += 100;
		fives += 100;
		sixes += 100;
		sevens += n%100+1;;
		break;
	case 8:
		ones += 100;
		twos += 100;
		threes += 100;
		fours += 100;
		fives += 100;
		sixes += 100;
		sevens += 100;
		eights += n%100+1;;
		break;
	case 9:
		ones += 100;
		twos += 100;
		threes += 100;
		fours += 100;
		fives += 100;
		sixes += 100;
		sevens += 100;
		eights += 100;
		nines += n%100+1;;
		break;
	}
	b = (n-n%1000)/1000;
	for(int i = 0; i < b; i++)
	{
		zeros+=100;
		ones+=100;
		twos+=100;
		threes+=100;
		fours+=100;
		fives+=100;
		sixes+=100;
		sevens+=100;
		eights+=100;
		nines+=100;
	}
	//обработка сотен закончилась
	//обработка тысяч
	switch((n%10000)/1000)
	{
	case 1:
		ones += n%1000+1;
		break;
	case 2:
		ones += 1000;
		twos+= n%1000+1;
		break;
	case 3:
		ones += 1000;
		twos += 1000;
		threes += n%1000+1;
		break;
	case 4:
		ones += 1000;
		twos += 1000;
		threes += 1000;
		fours += n%1000+1;;
		break;
	case 5:
		ones += 1000;
		twos += 1000;
		threes += 1000;
		fours += 1000;
		fives += n%1000+1;;
		break;
	case 6:
		ones += 1000;
		twos += 1000;
		threes += 1000;
		fours += 1000;
		fives += 1000;
		sixes += n%1000+1;;
		break;
	case 7:
		ones += 1000;
		twos += 1000;
		threes += 1000;
		fours += 1000;
		fives += 1000;
		sixes += 1000;
		sevens += n%1000+1;;
		break;
	case 8:
		ones += 1000;
		twos += 1000;
		threes += 1000;
		fours += 1000;
		fives += 1000;
		sixes += 1000;
		sevens += 1000;
		eights += n%1000+1;;
		break;
	case 9:
		ones += 1000;
		twos += 1000;
		threes += 1000;
		fours += 1000;
		fives += 1000;
		sixes += 1000;
		sevens += 1000;
		eights += 1000;
		nines += n%1000+1;;
		break;
	}
	b = (n-n%10000)/10000;
	for(int i = 0; i < b; i++)
	{
		zeros+=1000;
		ones+=1000;
		twos+=1000;
		threes+=1000;
		fours+=1000;
		fives+=1000;
		sixes+=1000;
		sevens+=1000;
		eights+=1000;
		nines+=1000;
	}
	//обработка тысяч закончена
	//обработка десятков тысяч
	switch((n%100000)/10000)
	{
	case 1:
		ones += n%10000+1;
		break;
	case 2:
		ones += 10000;
		twos+= n%10000+1;
		break;
	case 3:
		ones += 10000;
		twos += 10000;
		threes += n%10000+1;
		break;
	case 4:
		ones += 10000;
		twos += 10000;
		threes += 10000;
		fours += n%10000+1;;
		break;
	case 5:
		ones += 10000;
		twos += 10000;
		threes += 10000;
		fours += 10000;
		fives += n%10000+1;;
		break;
	case 6:
		ones += 10000;
		twos += 10000;
		threes += 10000;
		fours += 10000;
		fives += 10000;
		sixes += n%10000+1;;
		break;
	case 7:
		ones += 10000;
		twos += 10000;
		threes += 10000;
		fours += 10000;
		fives += 10000;
		sixes += 10000;
		sevens += n%10000+1;;
		break;
	case 8:
		ones += 10000;
		twos += 10000;
		threes += 10000;
		fours += 10000;
		fives += 10000;
		sixes += 10000;
		sevens += 10000;
		eights += n%10000+1;;
		break;
	case 9:
		ones += 10000;
		twos += 10000;
		threes += 10000;
		fours += 10000;
		fives += 10000;
		sixes += 10000;
		sevens += 10000;
		eights += 10000;
		nines += n%10000+1;;
		break;
	}
	b = (n-n%100000)/100000;
	for(int i = 0; i < b; i++)
	{
		zeros+=10000;
		ones+=10000;
		twos+=10000;
		threes+=10000;
		fours+=10000;
		fives+=10000;
		sixes+=10000;
		sevens+=10000;
		eights+=10000;
		nines+=10000;
	}
	//обработка десятков тысяч закончена
	//обработка сотен тысяч
	switch((n%1000000)/100000)
	{
	case 1:
		ones += n%100000+1;
		break;
	case 2:
		ones += 100000;
		twos+= n%100000+1;
		break;
	case 3:
		ones += 100000;
		twos += 100000;
		threes += n%100000+1;
		break;
	case 4:
		ones += 100000;
		twos += 100000;
		threes += 100000;
		fours += n%100000+1;;
		break;
	case 5:
		ones += 100000;
		twos += 100000;
		threes += 100000;
		fours += 100000;
		fives += n%100000+1;;
		break;
	case 6:
		ones += 100000;
		twos += 100000;
		threes += 100000;
		fours += 100000;
		fives += 100000;
		sixes += n%100000+1;;
		break;
	case 7:
		ones += 100000;
		twos += 100000;
		threes += 100000;
		fours += 100000;
		fives += 100000;
		sixes += 100000;
		sevens += n%100000+1;;
		break;
	case 8:
		ones += 100000;
		twos += 100000;
		threes += 100000;
		fours += 100000;
		fives += 100000;
		sixes += 100000;
		sevens += 100000;
		eights += n%100000+1;;
		break;
	case 9:
		ones += 100000;
		twos += 100000;
		threes += 100000;
		fours += 100000;
		fives += 100000;
		sixes += 100000;
		sevens += 100000;
		eights += 100000;
		nines += n%100000+1;;
		break;
	}
	b = (n-n%1000000)/1000000;
	for(int i = 0; i < b; i++)
	{
		zeros+=100000;
		ones+=100000;
		twos+=100000;
		threes+=100000;
		fours+=100000;
		fives+=100000;
		sixes+=100000;
		sevens+=100000;
		eights+=100000;
		nines+=100000;
	}
	//обработка сотен тысяч закончена
	//обработка миллионов
	switch((n%10000000)/1000000)
	{
	case 1:
		ones += n%1000000+1;
		break;
	case 2:
		ones += 1000000;
		twos+= n%1000000+1;
		break;
	case 3:
		ones += 1000000;
		twos += 1000000;
		threes += n%1000000+1;
		break;
	case 4:
		ones += 1000000;
		twos += 1000000;
		threes += 1000000;
		fours += n%1000000+1;;
		break;
	case 5:
		ones += 1000000;
		twos += 1000000;
		threes += 1000000;
		fours += 1000000;
		fives += n%1000000+1;;
		break;
	case 6:
		ones += 1000000;
		twos += 1000000;
		threes += 1000000;
		fours += 1000000;
		fives += 1000000;
		sixes += n%1000000+1;;
		break;
	case 7:
		ones += 1000000;
		twos += 1000000;
		threes += 1000000;
		fours += 1000000;
		fives += 1000000;
		sixes += 1000000;
		sevens += n%1000000+1;;
		break;
	case 8:
		ones += 1000000;
		twos += 1000000;
		threes += 1000000;
		fours += 1000000;
		fives += 1000000;
		sixes += 1000000;
		sevens += 1000000;
		eights += n%1000000+1;;
		break;
	case 9:
		ones += 1000000;
		twos += 1000000;
		threes += 1000000;
		fours += 1000000;
		fives += 1000000;
		sixes += 1000000;
		sevens += 1000000;
		eights += 1000000;
		nines += n%1000000+1;;
		break;
	}
	b = (n-n%10000000)/10000000;
	for(int i = 0; i < b; i++)
	{
		zeros+=1000000;
		ones+=1000000;
		twos+=1000000;
		threes+=1000000;
		fours+=1000000;
		fives+=1000000;
		sixes+=1000000;
		sevens+=1000000;
		eights+=1000000;
		nines+=1000000;
	}
	//обработка миллионов закончена
	//обработка десятков миллионов
	switch((n%100000000)/10000000)
	{
	case 1:
		ones += n%10000000+1;
		break;
	case 2:
		ones += 10000000;
		twos+= n%10000000+1;
		break;
	case 3:
		ones += 10000000;
		twos += 10000000;
		threes += n%10000000+1;
		break;
	case 4:
		ones += 10000000;
		twos += 10000000;
		threes += 10000000;
		fours += n%10000000+1;;
		break;
	case 5:
		ones += 10000000;
		twos += 10000000;
		threes += 10000000;
		fours += 10000000;
		fives += n%10000000+1;;
		break;
	case 6:
		ones += 10000000;
		twos += 10000000;
		threes += 10000000;
		fours += 10000000;
		fives += 10000000;
		sixes += n%10000000+1;;
		break;
	case 7:
		ones += 10000000;
		twos += 10000000;
		threes += 10000000;
		fours += 10000000;
		fives += 10000000;
		sixes += 10000000;
		sevens += n%10000000+1;;
		break;
	case 8:
		ones += 10000000;
		twos += 10000000;
		threes += 10000000;
		fours += 10000000;
		fives += 10000000;
		sixes += 10000000;
		sevens += 10000000;
		eights += n%10000000+1;;
		break;
	case 9:
		ones += 10000000;
		twos += 10000000;
		threes += 10000000;
		fours += 10000000;
		fives += 10000000;
		sixes += 10000000;
		sevens += 10000000;
		eights += 10000000;
		nines += n%10000000+1;;
		break;
	}
	b = (n-n%100000000)/100000000;
	for(int i = 0; i < b; i++)
	{
		zeros+=10000000;
		ones+=10000000;
		twos+=10000000;
		threes+=10000000;
		fours+=10000000;
		fives+=10000000;
		sixes+=10000000;
		sevens+=10000000;
		eights+=10000000;
		nines+=10000000;
	}
	//обработка десятков миллионов закончена
	//обработка сотен миллионов
	switch((n%1000000000)/100000000)
	{
	case 1:
		ones += n%100000000+1;
		break;
	case 2:
		ones += 100000000;
		twos+= n%100000000+1;
		break;
	case 3:
		ones += 100000000;
		twos += 100000000;
		threes += n%100000000+1;
		break;
	case 4:
		ones += 100000000;
		twos += 100000000;
		threes += 100000000;
		fours += n%100000000+1;;
		break;
	case 5:
		ones += 100000000;
		twos += 100000000;
		threes += 100000000;
		fours += 100000000;
		fives += n%100000000+1;;
		break;
	case 6:
		ones += 100000000;
		twos += 100000000;
		threes += 100000000;
		fours += 100000000;
		fives += 100000000;
		sixes += n%100000000+1;;
		break;
	case 7:
		ones += 100000000;
		twos += 100000000;
		threes += 100000000;
		fours += 100000000;
		fives += 100000000;
		sixes += 100000000;
		sevens += n%100000000+1;;
		break;
	case 8:
		ones += 100000000;
		twos += 100000000;
		threes += 100000000;
		fours += 100000000;
		fives += 100000000;
		sixes += 100000000;
		sevens += 100000000;
		eights += n%100000000+1;;
		break;
	case 9:
		ones += 100000000;
		twos += 100000000;
		threes += 100000000;
		fours += 100000000;
		fives += 100000000;
		sixes += 100000000;
		sevens += 100000000;
		eights += 100000000;
		nines += n%100000000+1;;
		break;
	}
	b = (n-n%1000000000)/1000000000;
	for(int i = 0; i < b; i++)
	{
		zeros+=100000000;
		ones+=100000000;
		twos+=100000000;
		threes+=100000000;
		fours+=100000000;
		fives+=100000000;
		sixes+=100000000;
		sevens+=100000000;
		eights+=100000000;
		nines+=100000000;
	}
	//обработка сотен миллионов закончена
	if(n/1000000000 != 0)
		ones++;
	/*for(int i = 1; i <= n; i++)
		F(i);*/
	cout<<zeros<<endl<<ones<<endl<<twos<<endl<<threes<<endl<<fours<<endl<<fives<<endl<<sixes<<endl<<sevens<<endl<<eights<<endl<<nines<<endl;
}