#include <bits/stdc++.h>
using namespace std;
int main()
{
	vector<int> numeros;
	long int cantidad=0, mayor=0, numaux=0, contador=0, total=0;
	cin>>cantidad;
	for (int i=0; i<cantidad; i++)
	{
		cin>>numaux;
		if (numaux>mayor)
		{
			mayor=numaux;
		}
		numeros.push_back(numaux);
	}
	for (int x=0; x<cantidad; x++)
	{
		numeros[x]==mayor?contador++:contador=0;
		if (contador>total)
		{
			total=contador;
		}
	}
	cout<<total;
	return 0;
}
