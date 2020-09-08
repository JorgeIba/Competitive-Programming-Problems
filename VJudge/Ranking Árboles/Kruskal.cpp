#include <bits/stdc++.h>
using namespace std;

int adj[10000];
pair< int, pair<int, int> > registro[100000];
int edges, nodos;
void inicializar()
{
	for (int i=0; i<10000; i++)
	{
		adj[i]=i;
	}
}

int find(int x)
{
	while(adj[x] != x)
	{
		adj[x]=adj[adj[x]];
		x=adj[x];
	}
	return x;
}


void unir(int x, int y)
{
	int p, q;
	p=find(x);
	q=find(y);
	adj[p]=adj[q];
}


int funcion()
{
	int x, y, costo, costoMenor=0;

	for (int i=0; i<edges; i++)
	{
		x=registro[i].second.first;
		y=registro[i].second.second;
		costo=registro[i].first;
		if (find(x) != find(y)) //Checa si el nodo x y el nodo y estan "Unidos" en un mismo conjunto
		{
			costoMenor+=costo; //Si no estan en el mismo conjunto, agrega la arista
			unir(x,y); //y une los dos nodos en un mismo grupo
		}
	}
	return costoMenor;
}

int main()
{
	int costo, x, y, res;
	inicializar();
	cin>>nodos>>edges;
	for (int i=0; i<edges; i++)
	{
		cin>>x>>y>>costo;
		registro[i]=make_pair(costo, make_pair(x,y));
	}
	sort(registro, registro + edges); //ordenar todas las aristas de menor costo
	res=funcion();
	cout<<res;
	return 0;
}