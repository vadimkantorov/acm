#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

string days[7] = 
{
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
	"Sunday"
};

string months[4] =
{
	"September",
	"October",
	"November",
	"December"
};

struct day
{
	int day_day;
	int day_month;
	int day_num;
};

int dni[7];
int inds[7];
int main()
{
	//freopen("input.txt","r",stdin);
	
	string in_day, in_month;
	int in_num, in;
	day last;
	cin>>in_day>>in_month>>last.day_num;
	for(int i=0; i<7; i++)
		if(in_day == days[i])
		{
			in = (i + 1) % 7;
			break;
		}
	day now={in, 0, 2};
	last.day_day = -1;
	for(int i=0; i<4; i++)
		if(in_month == months[i])
		{
			last.day_month = i;
			break;
		}
	int A,B;
	cin>>A>>B;
	while(now.day_month != last.day_month ||
			now.day_num != last.day_num)
	{
		dni[now.day_day]++;
		now.day_day = (now.day_day+1)%7;
		now.day_num++;
		if(now.day_num == 31 && now.day_month == 0)
		{
			now.day_month = 1;
			now.day_num = 1;
		}
		if(now.day_num == 32 && now.day_month == 1)
		{
			now.day_month = 2;
			now.day_num = 1;
		}
		if(now.day_num == 31 && now.day_month == 2)
		{
			now.day_month = 3;
			now.day_num = 1;
		}
	}
//	int inds[7];
	//memset(inds, 0, sizeof(inds));
	for(inds[0] = 0; inds[0] < 2; inds[0]++)
		for(inds[1] = 0; inds[1] < 2; inds[1]++)
			for(inds[2] = 0; inds[2] < 2; inds[2]++)
				for(inds[3] = 0; inds[3] < 2; inds[3]++)
					for(inds[4] = 0; inds[4] < 2; inds[4]++)
						for(inds[5] = 0; inds[5] < 2; inds[5]++)
							for(inds[6] = 0; inds[6] < 2; inds[6]++)
							{
								int result = 0;
								for(int i = 0; i < 7; i++)
									if(inds[i])	result += dni[i];
								
								if(result >= A && result <= B)
								{
									int count = 0;
									for(int i = 0; i < 7; i++)
										if(inds[i])count++;
									cout << count << endl;
									for(int i = 0; i < 7; i++)
										if(inds[i])	cout << days[i] << endl;
									return 0;
								}
							}
	cout << "Impossible";
	return 0;
}