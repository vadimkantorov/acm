#include <cstdio>
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

char tmp[30];
string s;

struct Mot
{
	char Dir;
	int Time;
};

Mot mots[6000000];
int motcnt = 0;

int grades[10];
//0 - Perfect
//1 - Great
//2 - Good
//3 - Boo
//4 - Miss

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
#endif
	
	int seconds,minutes;
	char mode;

	scanf("%d:%d %c%s\n",&minutes,&seconds,&mode,tmp);
	getline(cin,s);
	
	Mot t;
	while(scanf("%d %c\n",&t.Time,&t.Dir) > 0)
		mots[motcnt++] = t;
	
	int ms = (minutes*60 + seconds)*1000;
	int period = 0;
	if(mode == 'E')
		period = 1000;
	else if(mode == 'M')
		period = 500;
	else
		period = 250;

	int diff = 1;
	if(mode == 'M')
		diff = 2;
	else if(mode == 'H')
		diff = 3;
	__int64 B = 1000000*diff;
	__int64 N = 0;//motcnt;//s.length();
	__int64 stepS = 0;
	__int64 comboS = 0;
	int sameCnt = 0;
	__int64 dancePs = 0;
	
	int mi = 0;
	int time = 0;
	for(int i = 0; i < s.length(); i++)
	{
		if(s[i] != 'N')
		{
			N++;
			//TODO: check <=
			while(mi+1 < motcnt && mots[mi].Time < time)
				mi++;
			
			if(time <= mots[mi].Time && mots[mi].Time < time + period)
			{
				int p = 0, q = 0;
				//MISS
				if(mots[mi].Dir != s[i])
				{
					grades[4]++;
					sameCnt = 0;
					if(dancePs >= 0)
						dancePs -= 5;
				}
				else
				{
					//PERFECT
					if(mots[mi].Time - time < period*4/10)
					{
						grades[0]++;
						p = 10;
						q = 55;
						sameCnt++;
						if(dancePs >= 0)
							dancePs += 2;
					}
					//GREAT
					else if(mots[mi].Time - time < period*7/10)
					{
						grades[1]++;
						p = 5;
						q = 33;
						sameCnt++;
						if(dancePs >= 0)
							dancePs += 1;
					}
					//GOOD
					else
					{
						grades[2]++;
						sameCnt++;
					}
				}

				stepS += p*N;
				comboS += q*sameCnt;
			}
			//BOO
			else
			{
				grades[3]++;
				sameCnt = 0;
				if(dancePs >= 0)
					dancePs -= 4;
			}
		}
		time += period;
	}

	//Grades
	printf("Perfect: %d\n",grades[0]);
	printf("Great: %d\n",grades[1]);
	printf("Good: %d\n",grades[2]);
	printf("Boo: %d\n",grades[3]);
	printf("Miss: %d\n",grades[4]);
	
	for(int i = 0; i < 20; i++)
		putchar('-');
	puts("");
	
	//Stage Score
	__int64 S = N*(N+1)/2;
	stepS *= (B/S);
	printf("Stage Score: %I64d\n",stepS);

	//Combo Bonus
	printf("Combo Bonus: %I64d\n",comboS);

	//Dance Level Bonus
	__int64 dlb = ceil(8./10.);
	if(dancePs < 0)
		dlb = 0;
	else if(grades[0] == N)
		dlb = 10000000;
	else if(grades[0] + grades[1] == N)
		dlb = 1000000;
	else if(dancePs >= ceil(2.*N*8/10))
		dlb = 100000;
	else if(dancePs >= ceil(2.*N*64/100))
		dlb = 10000;
	else if(dancePs >= ceil(2.*N*5/10))
		dlb = 1000;
	else
		dlb = 100;
	printf("Dance Level Bonus: %I64d\n",dlb);

	//Total Score
	printf("Total Score: %I64d\n",stepS + comboS + dlb);
	return 0;
}