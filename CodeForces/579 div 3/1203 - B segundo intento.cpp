#include <bits/stdc++.h>
#define lli long long int
using namespace std;

void funcion()
{
	vector<lli> numeros;
	lli cantidad, aux, resultado;
	cin>>cantidad;
	for (lli i=0; i<cantidad*4; i++)
	{
		cin>>aux;
		numeros.push_back(aux);
	}
	sort(numeros.begin(), numeros.end());
	
	resultado= numeros[0] * numeros[cantidad*4-1];
	
	lli j=cantidad*4-1;
	
	
	int bitmask=numeros[0];
	
	for (int i=1; i<numeros.size(); i++)
	{
		bitmask^=numeros[i];
	}
	
	if (bitmask!=0)
	{
		cout<<"NO\n";
		return;
	}
	for (lli i=0; i<cantidad*2; i++)
	{
		if (numeros[i] * numeros[j] != resultado)
		{
			cout<<"NO\n";
			return;
		}
		j--;
	}
	cout<<"YES\n";
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli q;
	cin>>q;
	for(int i=0; i<q; i++)
	{
		funcion();
	}
	return 0;
}
