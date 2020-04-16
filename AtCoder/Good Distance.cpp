#include <bits/stdc++.h>

using namespace std;
int main()
{
	int n,d, auxentero=0, contador=0, auxinsertar;
	set<int> cuadrados;
	
	
	for (int i=0; i<=200; i++)
	{
		cuadrados.insert(i*i);
	}
	
	int aux=0;
	cin>>n>>d;
	vector< vector<int> > coordenadas(n+1);
	
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<d; j++)
		{
			cin>>auxinsertar;
			coordenadas[i].push_back(auxinsertar);
		}
	}
	
	
	for (int i=0; i<n; i++)
	{
		for (int j=i+1; j<n; j++)
		{
			aux=0;
			
			for (int q=0; q<d; q++)
			{	
				aux+=(coordenadas[i][q]-coordenadas[j][q])*(coordenadas[i][q]-coordenadas[j][q]);
		 	}
			 if (cuadrados.find(aux)!=cuadrados.end())
			 {
			 	contador++;
			 }
		}
	}
	cout<<contador<<endl;
	
	return 0;
}
