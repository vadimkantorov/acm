#include <cstdio>
#include <cstring>

char map[10][10];
bool used[10][10];
char s[20];
int slen;
int curInd;

bool Find(int i, int j, int ind)
{
	if(map[i][j] != s[ind] || used[i][j])
		return false;

	if(ind == slen - 1)
		return true;

	int dx[] = {0,0,1,-1};
	int dy[] = {1,-1,0,0};

	used[i][j] = true;
	for(int k = 0; k < 4; k++)
	{
		int x = i + dx[k];
		int y = j + dy[k];

		if(0 <= x && x < 4 &&
			0 <= y && y < 4 && map[x][y] == s[ind+1])
			if(Find(x,y,ind+1))
				return true;
	}

	used[i][j] = false;
	return false;
}

bool Find()
{
	for(int i =0 ; i < 10; i++)
		for(int j =0 ; j < 10; j++)
			used[i][j] = false;

	for(int i = 0 ; i < 4; i++)
		for(int j = 0; j < 4; j++)
			if(Find(i,j,0))
				return true;
	return false;
}

int main()
{
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);

	for(int i = 0; i < 4; i++)
		gets(map[i]);

	int n;
	scanf("%d\n",&n);
	for(int i = 0; i < n; i++)
	{
		gets(s);
		slen = strlen(s);
		if(Find())
			printf("%s: YES\n",s);
		else
			printf("%s: NO\n",s);
	}

	return 0;
}