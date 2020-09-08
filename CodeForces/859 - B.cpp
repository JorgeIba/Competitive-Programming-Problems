#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli known, numero;
	lli mayor=0;
	cin>>known;
	for (int i=0; i<known; i++)
	{
		cin>>numero;
		mayor=max(mayor,numero);
	}
	if (mayor<=25)
	{
		cout<<0<<endl;
	}
	else
	{
		cout<<(mayor-25)<<endl;
	}
	return 0;
}
