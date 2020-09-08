#include <bits/stdc++.h>
#define lli int
using namespace std;

void solve()
{
	lli n;
	cin>>n;
	lli piedra1, papel1, tijera1;
	cin>>piedra1>>papel1>>tijera1;
	string cadena;
	cin>>cadena;
	vector< pair<char,string> > res(cadena.length());
	for(int i=0; i<cadena.length(); i++)
	{
		res[i].first = cadena[i];
	}
	lli contador = 0;
	for(int i=0; i<cadena.length(); i++) //piedra1s
	{
		if((res[i].first == 'S')and(piedra1>0))
		{
			res[i].second = "R";
			piedra1--;
			contador++;
		}
	}

	for(int i=0; i<cadena.length(); i++) //papel1
	{
		if((res[i].first == 'R')and(papel1>0))
		{
			res[i].second = "P";
			papel1--;
			contador++;
		}
	}

	for(int i=0; i<cadena.length(); i++) //tijera1s
	{
		if((res[i].first == 'P')and(tijera1>0))
		{
			res[i].second = "S";
			tijera1--;
			contador++;
		}
	}

	
	for(int i=0; i<cadena.length(); i++) //Las que sobran
	{
		if(res[i].second.empty())
		{
			if(piedra1 > 0)
			{
				res[i].second = "R";
				piedra1--;
				continue;
			}
			if (papel1 > 0)
			{
				res[i].second = "P";
				papel1--;
				continue;
			}
			if (tijera1>0)
			{
				res[i].second = "S";
				tijera1--;
				continue;
			}
		}
	}

	lli limit = (n+1)/2;
	if (contador<limit)
	{
		cout<<"NO\n";
	}
	else
	{
		cout<<"YES\n";
		for(auto x: res)
		{
			cout<<x.second;
		}
		cout<<endl;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lli t;
	cin>>t;
	while(t--)
	{
		solve();
	}	
	return 0;
}
