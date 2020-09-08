#include <bits/stdc++.h>
#define lli long long int
using namespace std;

vector<int> vectorPrimos;
int county[10010];
int county2[10010];

void descPrimos1(int numero)
{
	lli auxNumero=numero;
	for (int i=2; i<=10010; i++)
	{
		while(numero%i==0)
		{
			vectorPrimos.push_back(i);
			numero/=i;
		}	
		if (numero==1)
		{
			return;
		}
	}
}


void funcion()
{
	int numero, aux;
	vector<int> numeros;
	cin>>numero;
	for (int i=0; i<numero*4; i++)
	{
		cin>>aux;
		if (aux!=1)
		{
			county[aux]=county[aux]+1;	
		}
	}
	
	for (int i=1; i<=10010; i++)
	{
		if ((county[i]!=0)and(county[i]!=1))
		{
			while (county[i]!=1)
			{
				
				numeros.push_back(i);
				county[i]/=2;
				
			}	
		}	
	}
	for (int i=0; i<numeros.size(); i++)
	{
		descPrimos1(numeros[i]);
	}
	
	for (int i=0; i<vectorPrimos.size(); i++)
	{
		county2[vectorPrimos[i]]++;
	}
	
	for (int i=1; i<=10010; i++)
	{

		if (county2[i]!=0)
		{
			if (county2[i]%numero!=0)
			{
				cout<<"NO\n";
				return;
			}
		}
	}
	cout<<"YES\n";
}



int main()
{
	lli q;
	cin>>q;
	for(int i=0; i<q; i++)
	{
		vectorPrimos.clear();
		memset(county, 0, sizeof(int)*10010);
		memset(county2, 0, sizeof(int)*10010);
		funcion();
	}
	return 0;
}
