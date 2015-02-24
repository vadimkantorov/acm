#include <iostream>
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;
bool finished = false;
bool issol(int k, int n)
{
	return (k +	1 == n*n);
}
struct CAN
{
	int cand;
	int hor;
	int ver;
	CAN()
	{
		cand = 500;
	}
};
int great(const void* a, const void* b)
{
	if(((CAN*)a)->cand >((CAN*)b)->cand)
		return 1;
	if(((CAN*)a)->cand >((CAN*)b)->cand)
		return -1;
	return 0;
}
void getstr(char* c, int* d, int num, int mod)
{
	*d = num / mod;
	if(num % mod != 0)
		(*d)++;
	
	switch(num % mod)
	{
	case 1:
		*c = 'a';
		break;
	case 2:
		*c = 'b';
		break;
	case 3:
		*c = 'c';
		break;
	case 4:
		*c = 'd';
		break;
	case 5:
		*c = 'e';
		break;
	case 6:
		*c = 'f';
		break;
	case 7:
		*c = 'g';
		break;
	case 0:
		switch(mod)
		{
		case 1:
			*c = 'a';
			break;
		case 2:
			*c = 'b';
			break;
		case 3:
			*c = 'c';
			break;
		case 4:
			*c = 'd';
			break;
		case 5:
			*c = 'e';
			break;
		case 6:
			*c = 'f';
			break;
		case 7:
			*c = 'g';
			break;
		case 8:
			*c = 'h';
			break;
		}
		break;
	}

}
void processsol(int a[], int k, int n)
{
	finished = true;
	int d;
	char c;
	for(int i = 0; i <= k; i++)
	{
		getstr(&c,&d,a[i], n);
		cout << c << d << endl;
	}
}
bool correct(int a[], int k, int n, int hor, int ver)
{
	if( hor <= 0 || ver <= 0 || hor > n || ver > n)
		return false;
	else
	{
		int p = (ver-1)*n + hor;
		for(int i = 0; i < k-1; i++)
			if(a[i] == p)
				return false;
		return true;
	}
}
int getcandnum(int a[], int k, int n)
{
	int hor = a[k-1] % n;
	int hor1,ver1;
	int res = 0;
	if(hor == 0)
	{
		switch(n)
		{
		case 4:
			hor = 4;
			break;
		case 5:
			hor = 5;
			break;
		case 6:
			hor = 6;
			break;
		case 7:
			hor = 7;
			break;
		case 8:
			hor = 8;
			break;
		}
	}
	int ver = a[k-1] / n;
	if(a[k-1] % n != 0)
		ver++;
	CAN Cans[8];
	//5)
	hor1 = hor + 2;
	ver1 = ver + 1;
	if(correct(a,k,n,hor1,ver1))
	{
		res++;
	}
	//6)
	hor1 = hor + 2;
	ver1 = ver - 1;
	if(correct(a,k,n,hor1,ver1))
	{
		res++;
	}
	//7)
	hor1 = hor + 1;
	ver1 = ver - 2;
	if(correct(a,k,n,hor1,ver1))
	{
		res++;
	}
	//1)
	hor1 = hor - 2;
	ver1 = ver - 1;
	if(correct(a,k,n,hor1,ver1))
	{
		res++;
	}
	//2)
	hor1 = hor - 2;
	ver1 = ver + 1;
	if(correct(a,k,n,hor1,ver1))
	{
		res++;
	}
	//3)
	hor1 = hor - 1;
	ver1 = ver + 2;
	if(correct(a,k,n,hor1,ver1))
	{
		res++;
	}
	//4)
	hor1 = hor + 1;
	ver1 = ver + 2;
	if(correct(a,k,n,hor1,ver1))
	{
		res++;
	}
	
	//8)
	hor1 = hor - 1;
	ver1 = ver - 2;
	if(correct(a,k,n,hor1,ver1))
	{
		res++;	
	}
	return res;
}
void constructcand(int a[], int k, int n, int c[], int* ncand)
{
	
	int cand = 0;
	if(k == 0)
	{
		cand = n*n;
		for(int i = 1; i <= n*n; i++)
			c[i-1] = i;
	}
	else
	{
		int hor = a[k-1] % n;
		if(hor == 0)
		{
			switch(n)
			{
			case 4:
				hor = 4;
				break;
			case 5:
				hor = 5;
				break;
			case 6:
				hor = 6;
				break;
			case 7:
				hor = 7;
				break;
			case 8:
				hor = 8;
				break;
			}
		}
		int ver = a[k-1] / n;
		if(a[k-1] % n != 0)
			ver++;
		CAN Cans[8];
		//5)
		Cans[0].hor = hor + 2;
		Cans[0].ver = ver + 1;
		if(correct(a,k,n,Cans[0].hor,Cans[0].ver))
		{
			a[k] = (Cans[0].ver-1)*n + Cans[0].hor;
			Cans[0].cand = getcandnum(a,k+1,n);
		}
		//6)
		Cans[1].hor = hor + 2;
		Cans[1].ver = ver - 1;
		if(correct(a,k,n,Cans[1].hor,Cans[1].ver))
		{
			a[k] = (Cans[1].ver-1)*n + Cans[1].hor;
			Cans[1].cand = getcandnum(a,k+1,n);
		}
		//7)
		Cans[2].hor = hor + 1;
		Cans[2].ver = ver - 2;
		if(correct(a,k,n,Cans[2].hor,Cans[2].ver))
		{
			a[k] = (Cans[2].ver-1)*n + Cans[2].hor;
			Cans[2].cand = getcandnum(a,k+1,n);
		}
		//1)
		Cans[3].hor = hor - 2;
		Cans[3].ver = ver - 1;
		if(correct(a,k,n,Cans[3].hor,Cans[3].ver))
		{
			a[k] = (Cans[3].ver-1)*n +Cans[3].hor;
			Cans[3].cand = getcandnum(a,k+1,n);
		}
		//2)
		Cans[4].hor = hor - 2;
		Cans[4].ver = ver + 1;
		if(correct(a,k,n,Cans[4].hor,Cans[4].ver))
		{
			a[k] = (Cans[4].ver-1)*n + Cans[4].hor;
			Cans[4].cand = getcandnum(a,k+1,n);
		}
		//3)
		Cans[5].hor = hor - 1;
		Cans[5].ver = ver + 2;
		if(correct(a,k,n,Cans[5].hor,Cans[5].ver))
		{
			a[k] = (Cans[5].ver-1)*n + Cans[5].hor;
			Cans[5].cand = getcandnum(a,k+1,n);
		}
		//4)
		Cans[6].hor = hor + 1;
		Cans[6].ver = ver + 2;
		if(correct(a,k,n,Cans[6].hor,Cans[6].ver))
		{
			a[k] = (Cans[6].ver-1)*n + Cans[6].hor;
			Cans[6].cand = getcandnum(a,k+1,n);
		}
		
		//8)
		Cans[7].hor = hor - 1;
		Cans[7].ver = ver - 2;
		if(correct(a,k,n,Cans[7].hor,Cans[7].ver))
		{
			a[k] = (Cans[7].ver-1)*n + Cans[7].hor;
			Cans[7].cand = getcandnum(a,k+1,n);
		}
        qsort(Cans,8,sizeof(CAN),great);
		for(int i = 0; i < 8; i++)
		{
			if(Cans[i].cand != 500)
			{
				c[cand++] = (Cans[i].ver-1)*n + Cans[i].hor;
			}
		}
	}
	*ncand = cand;
}

void backtrack(int a[], int k, int n)
{
	int c[65];
	int ncand;

	if(issol(k,n))
		processsol(a,k,n);
	else
	{
		k++;
		constructcand(a,k,n,c,&ncand);
		for(int i = 0; i < ncand; i++)
		{
			a[k] = c[i];
			backtrack(a,k,n);
			if(finished)
				return;
		}
	}
}
void solve(int n)
{
	int a[65];
	backtrack(a,-1,n);
}
void main()
{
	int n;
	cin >> n;
	solve(n);
	if(!finished)
		cout << "IMPOSSIBLE";
}