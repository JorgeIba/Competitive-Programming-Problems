#include <iostream>
using namespace std;

	//Prototipo de Funciones
	void BusquedaBinaria(int [], int, int);

int main()	
{
	ios::sync_with_stdio(false);
	int n=0;
	int k=0;
	cin>>n;
	int puertas[n];
	for (int i=0; i<n; i++)
	{
		cin>>puertas[i];
	}
	cin>>k;
	int llaves[k];
	for (int e=0; e<k; e++)
	{
		cin>>llaves[e];
		BusquedaBinaria(puertas, n, llaves[e]);
	}
	return 0;
}

void BusquedaBinaria(int puertas[], int tamano, int numero)
{
	int inferior=0, superior=tamano-1, medio;
	while (inferior<=superior)
	{
		medio=(inferior+superior)/2;
		if (puertas[medio]==numero)
		{
			cout<<medio+1<< " ";
			return;
		}
		else if (numero > puertas[medio])
		{
			inferior=medio+1;
		}
		else if (numero < puertas[medio])
		{
			superior = medio-1;
		}	
	}
	cout<<"0 ";
}
