#include <bits/stdc++.h>
#define lli long long int
using namespace std;

void funcion()
{
	lli n;
	cin>>n;
	lli suma=0;
	for (int i=0; i<n; i++)
	{
		lli aux;
		cin>>aux;
		suma+=aux;
	}
	lli res=0;
	if (suma%n!=0)
	{
		res = suma/n + 1;
	}
	else
	{
		res = suma/n;
	}
	cout<<res<<endl;
	return;
}


int main()
{
	lli q;
	cin>>q;
	while(q--)
	{
		funcion();
	}
	return 0;
}
