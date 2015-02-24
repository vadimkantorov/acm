#include <cstdio>
#include <vector>
#include <algorithm>
#include <locale>
using namespace std;

struct Card
{
	char Mast, Dost;

	void Scan()
	{
		Dost = getchar();
		if(Dost == '1')
		{
			getchar();
			Dost = 'I';
		}
		else if(isdigit(Dost))
			Dost = Dost-'2'+'A';
		else if(Dost == 'Q')
			Dost = 'K';
		else if(Dost == 'K')
			Dost = 'L';
		else if(Dost == 'A')
			Dost = 'M';

		Mast = getchar();
	}

	bool operator<(const Card& c) const
	{
		return Dost < c.Dost;
	}

	bool operator==(const Card& c) const
	{
		return Mast == c.Mast && Dost == c.Dost;
	}

	bool IsNext(const Card& c) const
	{
		return (c.Dost-Dost) == 1;
	}
};

struct Comb
{
	vector<Card> Cs;
	int Priority;

	bool operator<(const Comb& c) const
	{
		if(Priority != c.Priority)
			return Priority < c.Priority;

		if(Priority == 500)
		{
			if(Cs[1].Dost != c.Cs[1].Dost)
				return (Cs[1] < c.Cs[1]);
			if(Cs[1].Dost == Cs[2].Dost)
			{
				if(c.Cs[1].Dost == c.Cs[2].Dost)
					return Cs[0] < c.Cs[0];
				else if(c.Cs[0].Dost == c.Cs[1].Dost)
					return Cs[0] < c.Cs[2];
			}
			else if(Cs[0].Dost == Cs[1].Dost)
			{
				if(c.Cs[1].Dost == c.Cs[2].Dost)
					return Cs[2] < c.Cs[0];
				else if(c.Cs[0].Dost == c.Cs[1].Dost)
					return Cs[2] < c.Cs[2];
			}
		}
		else
		{
			for(int i = 2; i >= 0; i--)
				if(Cs[i].Dost != c.Cs[i].Dost)
					return (Cs[i] < c.Cs[i]);
		}
		return false;
	}

	Comb()
	{
		Priority = 0;
	}

	void ProcessHand()
	{
		sort(Cs.begin(), Cs.end());

		if(Cs[0].Dost == Cs[1].Dost && Cs[1].Dost == Cs[2].Dost && Cs[0].Dost == 'B')//3
			Priority = 1000;
		else
		{
			bool straight = Cs[0].IsNext(Cs[1]) && Cs[1].IsNext(Cs[2]);
			bool flush = (Cs[0].Mast == Cs[1].Mast) && (Cs[1].Mast == Cs[2].Mast);

			if(straight && flush)
				Priority = 900;
			else if(Cs[0].Dost == Cs[1].Dost && Cs[1].Dost == Cs[2].Dost)
				Priority = 800;
			else if(straight)
				Priority = 700;
			else if(flush)
				Priority = 600;
			else if(Cs[0].Dost == Cs[1].Dost || Cs[1].Dost == Cs[2].Dost)
				Priority = 500;
			else
				Priority = 400;
		}
	}

	Comb(Card c1, Card c2, Card c3)
	{
		Cs.push_back(c1);
		Cs.push_back(c2);
		Cs.push_back(c3);

		ProcessHand();	
	}

	void Scan()
	{
		Card tmp;
		for(int i = 0; i < 3; i++)
		{
			tmp.Scan();
			Cs.push_back(tmp);
			getchar();
		}

		ProcessHand();
	}
};

void Process()
{
	Comb san, dim;
	Card a,b;

	bool usecards[] = {true,true};

	san.Scan();
	dim.Scan();

	a.Scan();
	getchar();
	b.Scan();
	getchar();

	if(a == b)
		usecards[1] = false;

	for(int i = 0; i < 3; i++)
	{
		if(san.Cs[i] == a)
			usecards[0] = false;
		if(san.Cs[i] == b)
			usecards[1] = false;

		if(dim.Cs[i] == a)
			usecards[0] = false;
		if(dim.Cs[i] == b)
			usecards[1] = false;
	}

	if(usecards[0])
		dim.Cs.push_back(a);
	if(usecards[1])
		dim.Cs.push_back(b);

	Comb max;

	for(int i = 0; i < dim.Cs.size(); i++)
		for(int j = i + 1; j < dim.Cs.size(); j++)
			for(int k = j + 1; k < dim.Cs.size(); k++)
			{
				Comb tmp(dim.Cs[i], dim.Cs[j], dim.Cs[k]);
				if(max < tmp)
					max = tmp;
			}

	if(san < max)
		puts("Dima");
	else if(max < san)
		puts("Sasha");
	else
		puts("Artyom");
}

void main()
{
	//freopen("input.txt", "r", stdin);

	while(true)
	{
		char c = getchar();
		if(c == EOF)
			break;
		else if(isalpha(c) || isdigit(c))
		{
			ungetc(c,stdin);
			Process();
		}
	}
}