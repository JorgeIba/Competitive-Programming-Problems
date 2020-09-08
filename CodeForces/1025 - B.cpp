#include <bits/stdc++.h>
#define lli long long unsigned int
using namespace std;


set<lli> primos;

void descomponer(lli n)
{
	if(n%2==0)
	{
		primos.insert(2);
		while(n%2==0)
		{
			n/=2;
		}
	}

	for(lli i = 3; i*i<=n; i+=2)
	{
		if(n%i==0)
		{
			primos.insert(i);
			while(n%i==0)
			{
				n/=i;
			}
		}
	}

	if (n>1)
	{
		primos.insert(n);
	}
}



 
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lli n; cin>>n;
	vector< pair<lli, lli> > parejas(n);
	for(int i=0; i<n; i++)	
	{
		cin>>parejas[i].first>>parejas[i].second;
	}

	descomponer(parejas[0].first);
	descomponer(parejas[0].second);

	for(int i=1; i<n; i++)
	{
		lli uno = parejas[i].first;
		lli dos = parejas[i].second;
		set<lli> aux = primos;
		for(auto x: aux)
		{
			if((uno % x == 0)or(dos % x == 0))
			{
				continue;
			}
			else
			{
				//cout<<x<<endl;
				primos.erase(x);
			}
		}
	}

	if(primos.size() > 0)
	{
		auto x = primos.begin();
		cout<<*x<<endl;
	}
	else
	{
		cout<<-1<<endl;
	}
	

	
	

	return 0;
}
