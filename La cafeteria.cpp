#include <bits/stdc++.h>
using namespace std;

int main ()
{
	long long int totalservidos=0;
	double balde;
	cin>>balde;
	totalservidos= (floor) (((balde*150)-3)/3.5)+2;
	cout<<totalservidos<<endl;
	return 0;
}
