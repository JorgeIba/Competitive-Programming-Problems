#include <bits/stdc++.h>
using namespace std;


void factoresPrimos(int numero, int matriz[21][21])
{
	int i=2;
	int numaux=numero;
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
		matriz[numaux][factores[i]]++;
	}
}


int main()
{
	int matriz[21][21];
	int auxMayor=0, minimoComun=1;
	memset(matriz, 0, sizeof matriz);
	
	for (int i=1; i<=20; i++)
	{
		factoresPrimos(i, matriz);
	}
	
	for (int i=2; i<=20; i++)
	{
		auxMayor=0;
		for (int j=2; j<=20; j++)
		{
			auxMayor=max(auxMayor,matriz[j][i]);
		}
		cout<<i<<"aparece mas veces: "<<auxMayor<<endl;
		if (auxMayor!=0)
		{
			minimoComun*=pow(i,auxMayor);	
		}	
	}
	
	cout<<minimoComun;
	return 0;
}
