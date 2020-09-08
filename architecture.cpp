#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
	lli n,m;
	cin>>n>>m;
	lli maximo=0;
	vector<lli> arriba(n);
	vector<lli> abajo(m);
	for(lli i=0; i<n; i++)
	{
		cin>>arriba[i];	
		maximo=max(maximo, arriba[i]);
	}
	for(lli i=0; i<m; i++)
	{
		cin>>abajo[i];		
		maximo=max(maximo, abajo[i]);
	}
	lli contadorU=0, contadorD=0;
	for(lli i=0; i<n; i++)
	{
		if(arriba[i]==maximo)
		{
			contadorU++;
		}
	}
	for(lli i=0; i<m; i++)
	{
		if(abajo[i]==maximo)
		{
			contadorD++;
		}
	}
	if((contadorU!=0)and(contadorD!=0))
	{
		cout<<"possible\n";
	}
	else
	{
		cout<<"impossible\n";
	}
	
	return 0;
}
