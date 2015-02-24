#include <cstdio>
#include <utility>
#include <algorithm>
#define N 502
using namespace std;

struct Segment
{
	int A,B;
	int Number;

	bool operator<(const Segment& s) const
	{
		if(A != s.A)
			return A < s.A;
		return B < s.B;
		
	}
};

Segment input[N];
int predCount[N], pred[N];

void main()
{
	//freopen("input.txt", "r", stdin);
	
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d %d", &input[i].A, &input[i].B);
		input[i].B = -input[i].B;
		input[i].Number = i+1;
		pred[i] = -1;
	}
	sort(input, input+n);

 	int best = 0;
	
	for(int i = 1; i < n; i++)
	{
		int testPred = -1;
		for(int j = 0; j < i; j++)
		{
			if( input[j].A != input[i].A && input[j].B < input[i].B && (testPred == -1 || predCount[j] > predCount[testPred]))
				testPred = j;
		}
		if(testPred != -1)
		{
			predCount[i] = predCount[testPred] + 1;
			pred[i] = testPred;
		}

		if(predCount[i] > predCount[best])
			best = i;
	}

	printf("%d\n",predCount[best] + 1);
	int cur = best;
	while(cur != -1)
	{
		printf("%d ", input[cur].Number);
		cur = pred[cur];
	}
}