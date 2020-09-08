#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	char numeros[1001];
	long long int maximo=0, aux1=0,aux2=1, ultimo, contador=0;
	int numeros1[1001];
	
	for (int i=0; i<1001; i++)
	{
		cin>>numeros[i];
	}
	for (int i=0; i<1001; i++)
	{
		aux1=numeros[i]-'0';
		numeros1[i]=aux1;
	}
	
	for (int i=0; i<1001; i++)
	{
		aux2*=numeros1[i];
		if (i>3)
		{
			ultimo=numeros1[i-3];
			contador=0;
			maximo=max(aux2, maximo);
			aux2/=ultimo;
		}
	}
	cout<<maximo;
	return 0;
}
