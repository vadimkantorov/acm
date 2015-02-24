#include <cstdio>
#include <cstring>

char A[20002], B[20002];

void main()
{
	//freopen("input.txt", "r", stdin);
		
	gets(A);
	gets(B);
	int n = strlen(A)/2;

	int textChar = ' ';
	for(int i = 0; i < 2*n+2; i+=2)
	{
		int encTextChar;
		sscanf(B+i,"%2x",&encTextChar);

		int keyChar = textChar^encTextChar;
		printf("%02X",keyChar);

		if(i != 2*n+1)
		{
			sscanf(A+i,"%2x",&encTextChar);
			textChar = keyChar^encTextChar;
		}
	}
}