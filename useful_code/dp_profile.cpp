#include <cstdio>
#include <cassert>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>

int k, p;

using namespace std;

vector<char> bigN;

void NormBigN()
{
	while (bigN.size() > 1 && bigN.back() == '0')
		bigN.pop_back();
}

int DivRem2()
{
	int mod = 0;
	for (int i = bigN.size() - 1; i >= 0; i--)
	{
		int dig = (bigN[i] - '0') + 10 * mod;
		mod = dig % 2;
		bigN[i] = dig / 2 + '0';
	}
	NormBigN();
	return mod;
}

void ReadBigN()
{
	string line;
	cin >> line;
	reverse(line.begin(), line.end());
	bigN.assign(line.begin(), line.end());

	int borrow = 0;
	for (int i = 0; i < bigN.size(); i++)
	{
		int dig = bigN[i] - '0' - (i == 0) - borrow;
		if (dig < 0)
		{
			borrow = 1;
			dig += 10;
		}
		else
			borrow = 0;
		bigN[i] = dig + '0';
	}

	NormBigN();
}

struct Matrix
{
	static const int N = 1 << 6;
	int M[N][N], size;

	Matrix(int size = 0) : size(size) { }

	Matrix operator*(Matrix& x)
	{
		assert(x.size == size);
		Matrix m(size);
		
		for(int i = 0; i < size; i++)
		{
			for(int j = 0; j < size; j++)
			{
				int res = 0;
				for(int k = 0; k < size; k++)
					res = (res + (M[i][k]*x.M[k][j]) % p) % p;
				m.M[i][j] = res;
			}
		}

		return m;
	}

	Matrix Raise()
	{
		Matrix res(size), curm = *this;
		bool started = false;
		
		while(!(bigN.size() == 1 && bigN[0] == '0'))
		{
			if(DivRem2() == 1)
			{
				if(started)
					res = res*curm;
				else
				{
					started = true;
					res = curm;
				}
			}

			curm = curm*curm;
		}

		return res;
	}
};

/*int Raise(int x, int power)
{
	int res = 1, curm = x;
	while(power != 0)
	{
		if(power%2 == 1)
			res *= curm;

		curm *= curm;
		power /= 2;
	}
	return res;
}

int Raise(int x, int power)
{
	if(power == 1)
		return x;

	if(power%2 == 0)
	{
		int t = Raise(x,power/2); 
		return t*t;
	}
	else
	{
		int t = Raise(x,power/2);
		return t*t*x;
	}
}*/

Matrix transm;

int IsBitSet(int num, int bit)
{
	return (num & (1 << bit)) != 0;
}

void ComputeCompatibleProfiles(int k)
{
	transm.size = 1 << k;
	for(int i = 0; i < transm.size; i++)
	{
		for(int j = i; j < transm.size; j++)
		{
			bool comp = true;

			for(int p = 1; comp && p < k; p++)
			{
				int sum = IsBitSet(i, p) + IsBitSet(i, p - 1)
					+ IsBitSet(j, p) + IsBitSet(j, p - 1);
				comp = sum != 0 && sum != 4;
			}
			
			transm.M[i][j] = transm.M[j][i] = (int) comp % p;
		}
	}
}

int main()
{	
	//freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);

	ReadBigN();
	cin >> k >> p;

	ComputeCompatibleProfiles(k);
	if(bigN.size() == 1 && bigN[0] == '0')
	{
		printf("%d", transm.size);
		return 0;
	}
	
	transm = transm.Raise();

	int res = 0;
	for(int i = 0; i < transm.size; i++)
		for(int j = 0; j < transm.size; j++)
			res = (res + transm.M[i][j]) % p;
	
	cout << res;
	return 0;
}