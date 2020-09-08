#include <iostream>
#include <stack>
using namespace std;
	//Prototipo de Funciones
	void principal();


int main()
{
	int t=0;
	cin>>t;
	for (int i=0; i<t; i++)
	{
		principal();
	}
	return 0;
}

void principal()
{
	long int n=0, numero=0, acum=0,auxiliar=1;
	stack<long int> pila;
	cin>>n;
	long int arreglo[n];
	for (long int i=0; i<n; i++)
	{
		cin>>arreglo[i];
	}
	pila.push(arreglo[0]);
	do
	{
		if (arreglo[auxiliar] > pila.top())
		{
			pila.pop();
			acum=acum+arreglo[auxiliar];
		}
		
		
		if (pila.empty())
		{
			pila.push(arreglo[auxiliar]);
			auxiliar=auxiliar+1;
		}
		else if (arreglo[auxiliar] <= pila.top())
		{
			pila.push(arreglo[auxiliar]);
			auxiliar=auxiliar+1;
		}
	}while(auxiliar!=(n));
	cout<<acum<<endl;
}
