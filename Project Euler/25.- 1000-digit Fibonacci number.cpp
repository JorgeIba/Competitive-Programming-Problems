#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	vector<lli> fibo;
	fibo.push_back(1);
	fibo.push_back(1);
	lli x = -1;
	lli i= 2;
	while( x <= 0 )
	{
		fibo.push_back( fibo[i-2] + fibo[i-1]  );
		x = fibo[i]/1000;
		i++;
		//cout<<x<<" ";
	}
	for(auto x: fibo)
	{
		cout<<x<<" ";
	}
	
	return 0;
}
