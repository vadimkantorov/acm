#include <cstdio>

int main()
{
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);

	int a,b,c,d;
	scanf("%d%d%d%d",&a,&b,&c,&d);
	if(a >= c)
	{
		printf("%d",a);
		return 0;
	}

	bool driver = false;
	while(true)
	{
		if(driver)
		{
			if(c - d < a)
			{
				printf("%d",a);
				return 0;
			}
			else
				c -= d;
			
			driver = false;
		}
		else
		{
			if(a + b > c)
			{
				printf("%d",c);
				return 0;
			}
			else
				a += b;

			driver = true;
		}
	}

	return 0;
}