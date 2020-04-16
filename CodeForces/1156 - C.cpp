#include <bits/stdc++.h>
#define lli long long int
using namespace std;
lli n, lim;

lli funcion(lli posible, vector<lli> puntos)
{
	unordered_set<lli> posiciones;
	lli contador=0;
	for (int i=1; i<=(n-posible); i++)
	{
		if (( abs( puntos[i] - puntos[i+posible] ) >= lim ) and (posiciones.find(i)==posiciones.end()) and(posiciones.find(i+posible)==posiciones.end()))
		{
			//cout<<puntos[i]<<" "<<puntos[i+posible]<<endl;
			posiciones.insert(i);
			posiciones.insert(i+posible);
			contador++;
		}
	}
	return contador;
}



int main()
{
	
	cin>>n>>lim;
	vector< lli > puntos(n+1);
	for (int i=1; i<=n; i++)
	{
		cin>>puntos[i];
	}
	lli l=1, r=n-1, posible=0, res=0;
	sort(puntos.begin(), puntos.end());
	while (l<=r)
	{
		posible=l + (r-l)/2;
		lli aux=funcion(posible, puntos);
		if (aux!=0)
		{
			res = max(res, aux);
			r=posible-1;
		}
		else
		{
			l=posible+1;	
		}
	}
	cout<<res<<endl;
	
	return 0;
}
