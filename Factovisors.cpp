#include <bits/stdc++.h>
#define lli long long int
using namespace std;
vector< pair<lli,lli> > descomp;


void primeFactors(lli n)
{
	lli contador2=0;
	while(n%2==0)
	{
		contador2++;
		n/=2;
	}
	if(contador2>0)
	{
		descomp.emplace_back(2,contador2);
	}
	
	for(lli i=3; i*i<=n; i+=2)
	{
		lli contador=0;
		while(n%i==0)
		{
			contador++;
			n/=i;
		}
		if(contador>0)
		{
			descomp.emplace_back(i, contador);
		}
		
	}
	if(n>2)
	{
		descomp.emplace_back(n,1);
	}
}


lli contarPrimos(lli fact, lli n)
{
	lli aux = fact/(n);
	lli auxiliarn = n;
	lli contador=0;
	while( aux>0 )
	{
		contador += aux;
		n = n*auxiliarn;
		aux = fact/n;
	}
	
	return contador;
}

void solve(lli fact, lli n)
{
	descomp.clear();
	if(n==0)
	{
		cout<<n<<" divides "<<fact<<"!\n";	
		return;
	}
	primeFactors(n);

	/*
	for(auto x: descomp)
	{
		cout<<x.first<<" "<<x.second<<endl;
	}
	cout<<"/////////////////\n";
	*/
	for(lli i=0; i<descomp.size(); i++)
	{
		if(contarPrimos(fact, descomp[i].first) < descomp[i].second)
		{
			cout<<n<<" does not divide "<<fact<<"!\n";
			return;
		}
	}
	cout<<n<<" divides "<<fact<<"!\n";
}

int main()
{
	lli fact,n;
	while(cin>>fact>>n)
	{
		solve(fact,n);
	}
	
	return 0;
}
