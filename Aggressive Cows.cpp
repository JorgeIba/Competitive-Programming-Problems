#include <bits/stdc++.h>
#define lli long long int

using namespace std;

bool checar(lli distanciaChida, vector<int> establos, lli vacas)
{
	lli ultimo=establos[0], contador=1;
	
	for (int i=1; i<establos.size(); i++)
	{
		if (establos[i] - ultimo >= distanciaChida )
		{
			contador++;
			ultimo = establos[i];
			if (contador==vacas)
			{
				return true;
			}
		}
	}
	
	return false;
}


void funcion()
{
	lli numEst, vacas;
	cin>>numEst>>vacas;
	vector<int> establos(numEst);
	
	for (int i=0; i<numEst; i++)
	{
		cin>>establos[i];
	}
	sort(establos.begin(), establos.end());
	lli distancia=establos[numEst-1] - establos[0];
	lli respuesta=0;
	lli l=0, r=distancia/2;
	lli distanciaChida=0;
	while (l<r)
	{
		distanciaChida = l + (r-l)/2;
		if (checar(distanciaChida, establos, vacas))
		{
			respuesta=distanciaChida;
			l=distanciaChida+1;
		}
		else
		{
			r=distanciaChida;
		}
		
	}
	
	cout<<respuesta<<endl;
	
	
	
}





int main()
{
	int t;
	cin>>t;
	for (int i=0; i<t; i++)
	{
		funcion();
	}
	
	return 0;
}
