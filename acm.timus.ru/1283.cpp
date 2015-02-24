#include <iostream>
using namespace std;

int main()
{
	double left,deadline,percents;
	int years = 0;
	cin >> left >> deadline >> percents;
	while ( left > deadline )
	{
		left -= left*percents/100;
		years++;
	}
	cout << years << endl;
	return 0;
}