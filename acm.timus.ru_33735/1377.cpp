#include <iostream>
using std::cin;
using std::cout;

enum dir
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};
struct point
{
	int x,y;

	bool operator==(point& b)
	{
		return (x==b.x && y==b.y);
	}
	bool operator!= (point& b)
	{
        return !(*this == b);
	}
};
point a,b,cur;
bool A[101][101];
int n,m,count;
dir d = RIGHT;

bool move()
{
	A[cur.x][cur.y] = true;
	switch(d)
	{
	case UP:
		if ( !A[cur.x-1][cur.y] && cur.x != 1 )
		{
			cur.x--;
			count++;
			return true;
		}
		else
		{
			d = RIGHT;
		}
		break;
	case DOWN:
		if ( !A[cur.x+1][cur.y] && cur.x != n)
		{
			cur.x++;
			count++;
			return true;
		}
		else
		{
			d = LEFT;
			//cur.x--;
		}
		break;
	case LEFT:
		if ( !A[cur.x][cur.y-1] && cur.y != 1 )
		{
			cur.y--;
			count++;
			return true;
		}
		else
		{
			d = UP;
			//cur.y--;
		}
		break;
	case RIGHT:
		if ( !A[cur.x][cur.y+1] && cur.y != m )
		{
			cur.y++;
			count++;
			return true;
		}
		else
		{
			d = DOWN;
			//cur.y++;
		}
		break;
	}
	return false;
}
int main()
{
	cin >> n >> m >> a.x >> a.y >> b.x >> b.y;
	cur.x = 1;
	cur.y = 1;
	while(cur != a && cur != b)
	{
		move();
	}
	count = 0;
	while(!move());
	while(cur != a && cur != b)
	{
		move();
	}
	cout << count;
}