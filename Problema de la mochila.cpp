#include <bits/stdc++.h>
#define lli long long int
using namespace std;


vector< pair<lli, lli> > value;
lli dp[10010][1010];


lli funcion(lli peso, lli indice)
{
	
	if(indice==value.size())
	{
		return 0;
	}
	if (peso<0)
	{
		return -100000;
	}
	if (dp[peso][indice]!=-1)
	{
		return dp[peso][indice];
	}
	
	lli	si=funcion(peso-value[indice].second, indice) + value[indice].first;
	lli	no=funcion(peso, indice+1);	
	dp[peso][indice]= max(si,no);
	return dp[peso][indice];
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	memset(dp, -1, sizeof(dp));
	lli n,w, aux1, aux2;
	cin>>n>>w;
	for(lli i=0; i<n; i++)
	{
		cin>>aux1>>aux2;
		value.push_back (make_pair(aux1,aux2));
	}
	cout<<funcion(w,0)<<endl;
	
	return 0;
}
