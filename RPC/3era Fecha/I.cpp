#include <bits/stdc++.h>
#define lli long long int
using namespace std;

vector<int> posibles;
lli n, m;
lli dp[300000];

lli funcion(lli indice)
{
	if (indice>=n)
	{
		return 0;
	}
	if (dp[indice]!=-1)
	{
		return dp[indice];
	}
	lli si=funcion(indice + m) + posibles[indice];
	lli no=funcion(indice+1);
	
	return dp[indice] = max(si,no);
}


int main()
{
	memset(dp, -1, sizeof(dp));
	lli aux;
	cin>>n>>m;
	for(int i=0; i<n; i++)
	{
		cin>>aux;
		posibles.push_back(aux);
	}
	
	cout<<funcion(m+1)<<endl;
	
	return 0;
}
