#include <bits/stdc++.h>
#define lli long long int
using namespace std;

void funcion()
{
	lli a,b,c;
	cin>>a>>b>>c;
	lli div=(a+b+c)/3;
	lli res=min(a,b);
	res=min(res,div);
	cout<<res<<endl;
}


int main()
{
	lli t;
	cin>>t;
	while(t--)
	{
		funcion();
	}
	return 0;
}
