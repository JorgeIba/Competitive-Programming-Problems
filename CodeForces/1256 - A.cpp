#include <bits/stdc++.h>
#define lli long long int

using namespace std;


void solve()
{
	lli a, b, n, S;
	cin>>a>>b>>n>>S;

	if( (n*a + b)  >= S)
	{
		lli minimo = min( (lli)(S/n) , a);
		lli absoluto = abs(S - n*minimo);
		if(absoluto <= b)
		{
			cout<<"YES\n";
			return;
		}	
	}
	cout<<"NO\n";
}



int main()
{
	lli t;
	cin>>t;
	while(t--)
	{
		solve();
	}
	
	return 0;
}
