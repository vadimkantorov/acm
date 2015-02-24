#include <cstdio>
#include <list>
#include <algorithm>

using namespace std;

const int N = 1005;

struct Order
{
	int Fee, Deadline, Index;

	bool operator<(const Order& x) const
	{
		if(Deadline != x.Deadline)
			return Deadline < x.Deadline;
		return Fee < x.Fee;
	}
};

Order orders[N];

list<int> res;

void main()
{
	//freopen("input.txt","r",stdin);
	
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d%d",&orders[i].Deadline,&orders[i].Fee);
		orders[i].Index = i+1;
	}

	sort(orders,orders+n);

	for(int i = 0; i < n; i++)
	{
		if(res.size() >= orders[i].Deadline)
		{
			list<int>::reverse_iterator minit = res.rbegin();
			for(list<int>::reverse_iterator it = minit; it != res.rend(); it++)
			{
				if(orders[*it].Fee < orders[*minit].Fee)
					minit = it;
			}
			res.erase((++minit).base());
		}
		res.push_back(i);
	}
	
	printf("%d\n",res.size());
	for(list<int>::iterator i = res.begin(); i != res.end(); i++)
		printf("%d ", orders[*i].Index);
}