#include <bits/stdc++.h>
using namespace std;	
int contadorTotal=0;
void visitar(int nodoActual, vector <int> nodos[] ,bool visited[])
{
	contadorTotal++;
	int conexiones=nodos[nodoActual].size();
	
	visited[nodoActual]=true;
	
	for (int i=0; i<conexiones; i++)
	{
		if (visited[nodos[nodoActual][i]]==false)
		{	
			visitar(nodos[nodoActual][i], nodos, visited);
		}
	}
	
}
int main()
{
	int cantidadNodos=0, caminos=0, nodo1=0, nodo2=0, start=0;
	cin>>cantidadNodos>>caminos;
	vector<int> nodos[cantidadNodos];
	bool visited[cantidadNodos];
	
	for (int i=0; i<caminos; i++)
	{
		cin>>nodo1>>nodo2;
		nodos[nodo1-1].push_back(nodo2-1);
		nodos[nodo2-1].push_back(nodo1-1);
	}
	
	cin>>start;
	
	for (int i=0; i<cantidadNodos; i++)
	{
		visited[i]=false;
	}
	visitar(start-1, nodos, visited);
	cout<<cantidadNodos-contadorTotal;	
	return 0;
}
