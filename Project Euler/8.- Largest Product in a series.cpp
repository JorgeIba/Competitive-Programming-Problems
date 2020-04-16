#include <bits/stdc++.h>
using namespace std;

int main()
{
	char numeros[1001];
	long long int maximo=0, aux1, aux2, numeros1[1001];
	for (int i=0; i<1001; i++)
	{
		cin>>numeros[i];
	}
	for (int i=0; i<1001; i++)
	{
		aux1=numeros[i]-'0';
		numeros1[i]=aux1;
	}
	for (int i=0; i<987; i++)
	{
		aux2=1;
		for (int j=i; j<i+13; j++)
		{
			aux2*=numeros1[j];
		}
		maximo=max(aux2,maximo);
	}
	cout<<maximo;
	return 0;
}
