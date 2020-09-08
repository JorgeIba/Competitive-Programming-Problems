#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	ios_base::sync_with_stdio(NULL);
	cin.tie(NULL);
	cout.tie(NULL);
	srand(time(NULL));
	for(int i=0; i<1000; i++)
	{
		lli num = rand()%1000000;
		cout<<num<<endl;
	}
	cout<<0<<endl;
	return 0;
}
