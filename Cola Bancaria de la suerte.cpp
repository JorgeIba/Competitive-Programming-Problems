#include <bits/stdc++.h>
using namespace std;

void agregarPuntos(char letra, int puntosExtra, vector< pair<int,string> > &cola)
{
	string letraAuxiliar;
	for (int i=0; i<cola.size(); i++)
	{
		letraAuxiliar=cola[i].second;
		if (letraAuxiliar[0]==letra)
		{
			cola[i].first+=puntosExtra;
		}
	}
}

int main()
{
	ios::sync_with_stdio(false);
	bool flag=false;
	vector< pair<int,string> > cola;
	int eventos=0, num=0, puntosExtra=0;
	char opcion, letra;
	string auxiliar;
	
	cin>>eventos;
	
	for (int i=0; i<eventos; i++) 
	{
		cin>>opcion;
		switch(opcion)
		{
			case 'C': 
				cin>>auxiliar>>num;
				cola.push_back(make_pair(num, auxiliar));
				flag=true;
			break;
			case 'S':
				cin>>letra>>puntosExtra;
				agregarPuntos(letra, puntosExtra, cola);
				flag=true;
			break;
			case 'A':
				if (flag=true)
				{
					sort (cola.begin(), cola.end());
					flag=false;	
				}
				cout<<cola.back().second<<e"\n";
				cola.pop_back();
			break;
		}
	}
	return 0;
}
