#include <bits/stdc++.h>
using namespace std;

vector< pair< pair<int,int>,int > > clientes;
vector< pair<int,int> > mesas;
vector< pair<int,int> > respuesta;
int suma=0;
int contador=0;

void funcion(int indice)
{
	int tamano=mesas.size();
	int l=0, r=tamano-1, posible;
	int candidata=-1;
	while(l<=r)
	{
		posible = l + (r-l)/2;
		if (clientes[indice].first.second <= mesas[posible].first)
		{
			candidata=posible;
			r=posible-1;
		}
		else
		{
			l=posible+1;
		}
	}
	if (candidata!=-1)
	{
		respuesta.push_back(make_pair(mesas[candidata].second,clientes[indice].second));
		suma+=clientes[indice].first.first;
		contador++;
		mesas.erase(mesas.begin()+candidata);
	}
	
}



int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int cantidadClientes, aux1, aux2;
	cin>>cantidadClientes;
	for (int i=1; i<=cantidadClientes; i++)
	{
		cin>>aux1>>aux2;
		pair<int,int> aux;
		aux.first=aux2;
		aux.second=aux1;
		
		clientes.push_back(make_pair(aux,i));
	}
	sort(clientes.rbegin(),clientes.rend());
	int cantidadMesas;
	cin>>cantidadMesas;
	for (int i=1; i<=cantidadMesas; i++)
	{
		cin>>aux1;
		mesas.push_back(make_pair(aux1,i));
	}
	sort(mesas.begin(), mesas.end());
	
	
	for (int i=0; i<cantidadClientes; i++)
	{
		funcion(i);
	}
	
	sort(respuesta.begin(),respuesta.end());
	
	cout<<contador<<" "<<suma<<endl;
	
	for (int i=0; i<respuesta.size(); i++)
	{
		cout<<respuesta[i].second<<" "<<respuesta[i].first<<endl;
	}
	
	
	
	
	return 0;
}
