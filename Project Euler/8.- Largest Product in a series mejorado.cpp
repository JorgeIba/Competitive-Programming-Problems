#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	char numeros[1001];
	long long int maximo=0, aux1=0,aux2=1;
	int numeros1[1001],  ultimo1=0, contador=0;
	
	for (int i=0; i<1000; i++)
	{
		cin>>numeros[i];
	}
	
	
	for (int i=0; i<1000; i++)
	{
		
		aux1=numeros[i]-'0';
		numeros1[i]=aux1;
		cout<<i;
	}
	
	for (int i=0; i<1000; i++)
	{
		aux2*=numeros1[i];
		if (i>12)
		{
			ultimo1=numeros1[i-12];
			contador=0;
			maximo=max(aux2, maximo);
			aux2/=ultimo1;
		}
	}
	
	cout<<maximo;
	return 0;
}
