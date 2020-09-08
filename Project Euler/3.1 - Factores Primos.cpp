#include <bits/stdc++.h>
using namespace std;


void factoresPrimos(int numero)
{
	int i=2;
	vector<int> factores;
	while (numero>1)
	{
		while ((numero%i)==0)
		{
			factores.push_back(i);
			numero=numero/i;
		}
			i++;
	}
	for (int i=0; i<factores.size(); i++)
	{
		cout<<factores[i]<<" ";
	}
}


int main()
{
	factoresPrimos(504);
}
