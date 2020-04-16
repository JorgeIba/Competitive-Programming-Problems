#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lli n, p;
	cin>>n>>p;
	vector<long double> probabilidades(n);
	
	for(int i=0; i<n; i++)
	{
		lli l, r;
		cin>>l>>r;
		lli divisores = (lli)(r/p) - (lli)((l-1)/p);
		probabilidades[i] = (long double)divisores/(r-l+1);
	}
	long double suma=0;
	for(int i=0; i<n; i++)
	{
		long double p,q;
		if(i!=(n-1))
		{
			p = probabilidades[i];
			q = probabilidades[i+1];
		}
		else
		{
			p = probabilidades[i];
			q = probabilidades[0];
		}
		long double probaUnion = (1-p)*q + p*(1-q) + p*q;
		suma+=probaUnion;
	}
	
	suma*=2000;
	cout<<fixed<<setprecision(10)<<suma<<endl;
	
	
	return 0;
}
