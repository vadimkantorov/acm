struct Summator
{
	int M[33000];

	static const int R = 1 << 15;

	int Diff(int idx)
	{
		return (idx & -idx);
	}

	
	void Add(int x)
	{
		int idx = x;
		while(idx <= R)
		{
			M[idx]++;
			idx += Diff(idx);
		}
	}

	int Sum(int l, int r)
	{
		if(l == 0 && r == 0)
			return 0;
		if(l != 0)
			return Sum(0,r) - Sum(0,l-1);

		int idx = r, sum = 0;
		while(idx > 0)
		{
			sum += M[idx];
			idx -= Diff(idx);
		}
		return sum;
	}
};