#include <cstdio>
#include <algorithm>
using namespace std;

int n;
int A[1000];

int Hoare_Partition(int l, int r)
{
	int x = A[l];
	int i = l;
	int j = r;
	while(i <= j)
	{
		while(A[i] < x)
			i++;
		
		while(A[j] > x)
			j--;
		
		if(i <= j)
			swap(A[i++],A[j++]);
	}
	return j;
}

void QuickSort(int l, int r)
{
	if(l < r)
	{
		int p = Hoare_Partition(l,r);
		QuickSort(l,p-1);
		QuickSort(p+1,r);
	}
}

void main()
{
	freopen("input.txt","r",stdin);
	
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
		scanf("%d",&A[i]);
	QuickSort(0,n-1);
	for(int i = 0; i < n; i++)
		printf("%d ",A[i]);
}