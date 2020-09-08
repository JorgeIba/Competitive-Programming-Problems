#include <bits/stdc++.h>
using namespace std;


bool primalityTest(int numero)
{
	if (numero==1)
	{	
		return false;
	}
	if (numero<4)
	{
		return true;
	}
	if ((numero%2==0)or(numero%3==0))
	{
		return false;
	}
	if (numero<10)
	{
		return true;
	}
	for (int i=5; i*i<=numero; i=i+6)
	{
		if ((numero%(i+2)==0)or(numero%(i)==0))
		{
			return false;
		}
	}
	return true;
}

int main()
{
	int contador=2, candidato=3, primo;;
	while (contador<=10000)
	{
		candidato+=2;
		if (primalityTest(candidato))
		{
			primo=candidato;
			contador++;
		}
	}
	cout<<primo;
	return 0;
}
