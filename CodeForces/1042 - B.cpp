#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli inf=100000000000LL;

vector< pair<lli, lli> > rel;
lli dp[10010][9];

lli funcion(lli indice, lli suma)
{
	
	if ((indice>rel.size()))	
	{
		return inf;
	}
	if(dp[indice][suma]!=-1)
	{
		return dp[indice][suma];
	}
	if (suma == 7)
	{
		return 0;
	}
	
	lli si= funcion(indice + 1, (suma | rel[indice].second)) + rel[indice].first;
	lli no= funcion(indice + 1, suma);
	
	return dp[indice][suma]=min(si,no);
		
	
}



lli valor(char aux)
{
	if (aux=='A')
	{
		return 1;
	}
	else if (aux=='B')
	{
		return 2;
	}
	else
	{
		return 4;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	memset(dp, -1, sizeof(dp));
	lli n, aux1, aux3;
	string aux2;
	cin>>n;
	for (int i=0; i<n; i++)
	{
		aux3=0;
		cin>>aux1>>aux2;
		for (int i=0; i<aux2.length(); i++)
		{
			aux3+=valor(aux2[i]);
		}
		rel.push_back( make_pair(aux1,aux3) );
	}
	
	/*
	for (auto x: rel)
	{
		cout<<x.first<<" "<<x.second<<" "<<(x.second | (1<<1))<<endl;
	}
	*/


	
	lli res=funcion(0,0);
	if (res==inf)
	{
		cout<<-1<<endl;
	}
	else
	{
		cout<<res<<endl;
	}
	
	
	return 0;
}
