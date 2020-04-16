#include <bits/stdc++.h>
#define lli long long unsigned int

using namespace std;

int main()
{
	lli x,p;
	cin>>x>>p;
	vector<lli> horas(x);
	vector<lli> pred(p);
	for (int i=0; i<x; i++)
	{
		cin>>horas[i];
	}
	for (int i=0; i<p; i++)
	{
		cin>>pred[i];
	}
	lli gcd=0;
	for (int i=0; i<x-1; i++)
	{
		gcd=__gcd(gcd, horas[i+1] - horas[i]);
	}
	for(int i=0; i<p; i++)
	{
		if(gcd%pred[i]==0)
		{
			cout<<"YES\n"<<horas[0]<<" "<<(int)(i+1)<<endl;
			return 0;
		}
	}
	cout<<"NO\n";
	
	
	return 0;
}
