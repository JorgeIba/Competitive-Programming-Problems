#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli n,m, timen, timem, k;
vector<lli> ida;
vector<lli> vuelta;
	
lli posicion(lli lim)
{
	lli l=0, r=vuelta.size(), respuesta=0;
	lli posible=0;
	while(l<=r)
	{
		posible=l + (r-l)/2;
		if (vuelta[posible]>=(lim))
		{
			r=posible-1;
			respuesta=posible;
		}
		else
		{
			l=posible+1;
		}
	}
	return respuesta;
}


lli respuesta(lli indice, lli k)
{
	if (((indice + k)>=m)or(k>=n))
	{
		return -1;
	}
	else
	{
		return vuelta[indice + k];
	}
}



int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m>>timen>>timem>>k;
	lli aux;
	for (int i=0; i<n; i++)
	{
		cin>>aux;
		ida.push_back(aux);
	}
	for (int i=0; i<m; i++)
	{
		cin>>aux;
		vuelta.push_back(aux);
	}
	
	lli maxi=0;
	//cout<<ida[] + timen<<endl;
	lli indice=0;
	lli mayor = vuelta[m-1];
	for (int i=0; i<=k; i++)
	{
		indice=posicion(ida[i] + timen);
		lli aux=respuesta(indice, k-i);
		if ((aux==-1)or( ((ida[i] + timen > mayor)) and (i<=k)))
		{
			//cout<<ida[i] + timen<<" "<<mayor<<" "<<i<<endl;
			cout<<-1<<endl;
			return 0;	
		}
		maxi = max(maxi, aux + timem);
	}
	
	cout<<maxi<<endl;
	
	
	return 0;
}
