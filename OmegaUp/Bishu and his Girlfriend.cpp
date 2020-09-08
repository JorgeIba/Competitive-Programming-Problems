#include <bits/stdc++.h>

using namespace std;

int caminoFacil=0;
int lugarFacil=0;

void inicializarVisited(bool visited[], int cantidadNodos)
{
	for (int i=0; i<cantidadNodos; i++)
	{
		visited[i]=false;
	}
}

void inicializarMorritas(bool lugarMorritas[],int cantidadMorritas)
{
	for (int i=0; i<cantidadMorritas; i++)
	{
		lugarMorritas[i]=false;
	}
}


void visitarPaises(int nodoActual, int contCaminos, vector<int> nodos[], bool visited[], bool lugarMorritas[])
{
	int conexiones=nodos[nodoActual].size();
	visited[nodoActual]=true;
	if ((lugarMorritas[nodoActual]==true)and(contCaminos<=caminoFacil))
	{
		if((contCaminos==caminoFacil)and(nodoActual<lugarFacil))
		{
		caminoFacil=contCaminos;
		lugarFacil=nodoActual+1;	
		}
		else if(contCaminos<caminoFacil)
		{
		caminoFacil=contCaminos;
		lugarFacil=nodoActual+1;	
		}
		
	}
	
	for (int i=0; i<conexiones; i++)
	{
		if (visited[nodos[nodoActual][i]]==false)
		{
			visitarPaises(nodos[nodoActual][i], contCaminos+1, nodos, visited, lugarMorritas);
		}
	}
	
}		

int main()

{
	int cantidadNodos=0, cantidadMorritas=0, pais1=0, pais2=0, lugar=0;
	cin>>cantidadNodos;
	caminoFacil=cantidadNodos-1;
	lugarFacil=cantidadNodos;
	vector<int> nodos[cantidadNodos];
	bool visited[cantidadNodos];
	
	for (int i=0;  i<cantidadNodos-1; i++)
	{
		cin>>pais1>>pais2;
		nodos[pais1-1].push_back(pais2-1);
		nodos[pais2-1].push_back(pais1-1);
	}
		
	inicializarVisited(visited, cantidadNodos);
	
	cin>>cantidadMorritas;
	bool lugarMorritas[cantidadMorritas];
	
	inicializarMorritas(lugarMorritas, cantidadMorritas);
	
	for (int x=0; x<cantidadMorritas; x++)
	{
		cin>>lugar;
		lugarMorritas[lugar-1]=true;
	}
	
	visitarPaises(0, 0,nodos, visited, lugarMorritas);
	
	cout<<lugarFacil;
	return 0;
}


