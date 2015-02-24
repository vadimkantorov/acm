#include <cstdio>
#include <cstring>

int models[12][4] = {
	{1,2,3,4}, {1,3,4,2}, {1,4,2,3},
	{2,4,3,1}, {2,3,1,4}, {2,1,4,3},
	{3,2,4,1}, {3,4,1,2}, {3,1,2,4},
	{4,3,2,1}, {4,2,1,3}, {4,1,3,2}
};

char A[6], B[6], R[6];

void Rotate(char* comb, int num)
{
	strcpy(R,"");
	for(int i = 0; i < 4; i++)
		R[i] = comb[models[num][i]-1];
	R[4] = '\0';
}

void main()
{
	gets(A);
	gets(B);

	for(int i = 0; i < 12; i++)
	{
		Rotate(B,i);
		if(strcmp(R,A) == 0)
		{
			puts("equal");
			return;
		}
	}
	puts("different");
}