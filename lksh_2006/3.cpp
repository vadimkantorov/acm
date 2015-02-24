#include <algorithm>
#include <iterator>
#include <iostream>
using namespace std;

int X[10002];
int main()
{
	/*freopen("input.txt","w",stdout);
	puts("10000");
	for(int i = 1; i <= 10000; i++)
		printf("%d\n",i%3);*/
	
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int n;
	cin >> n;
	copy(istream_iterator<int>(cin), istream_iterator<int>(), X);
	sort(X, X + n);
	copy(X, X + n, ostream_iterator<int>(cout, " "));
	return 0;
}