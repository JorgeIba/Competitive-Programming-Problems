#include <bits/stdc++.h>
using namespace std;

long long int grupos[10010];

long long int nodos=0, aristas=0, opciones=0;

pair < long long unsigned int, pair<long long int, long long int> > registro[200010];



void inicializar(long long int nodos)
{
	for (long long int i=0; i<=nodos; ++i)
	{
		grupos[i]=i;
	}
}

long long int find(long long int x)
{
	while (grupos[x] != x)
	{
		grupos[x] = grupos[ grupos[x] ];
		x=grupos[x];
	}
	return x;
}

void unir(long long int x, long long int y)
{
	long long int p,q;
	p=find(x);
	q=find(y);
	grupos[p]=grupos[q];
	return;
}


long long int MST()
{
	long long unsigned int x, y, costo, costoMenor=0;
	
	for (long long int i=0; i<aristas+opciones; ++i)
	{
		x=registro[i].second.first;
		y=registro[i].second.second;
		costo=registro[i].first;
		if (find(x) != find(y))
		{
			costoMenor+=costo;
			unir(x,y);
		}
	}
	return costoMenor;
}


void principal()
{
		long long unsigned int contador=0;
		long long unsigned int x, y, v, w, costo, costoMenor=0;
		cin>>nodos>>aristas;
		inicializar(nodos);
		for (long long int i=0; i<aristas; ++i)
		{
			cin>>x>>y>>costo;
			registro[i]=make_pair(0, make_pair(x,y));
		}
		cin>>opciones;
		for (long long int i=0; i<opciones; ++i)
		{
			cin>>v>>w>>costo;
			registro[i+aristas]=make_pair(costo, make_pair(v,w));
		}
		sort(registro, registro+aristas+opciones);
		costoMenor= MST();
		contador=0;
		for (long long int i=1; i<=nodos; ++i)
		{
			if (grupos[i]==i)
				contador++;
		}
		if (contador>=2)
		{
			cout<<"You better hire someone else\n";
			return;
		}		
		else
		{	
			if(costoMenor==0)
			{
				cout<<"Thank you, Goodbye\n";
				return;
			}
			else
			{
				cout<<costoMenor<<endl;	
				return;
			}
		}
	return;
}

int main()
{
	ios::sync_with_stdio(false);
	int t=0;
	cin>>t;
	for (int i=0; i<t; i++)
	{
		principal();
	}
	return 0;
}
















