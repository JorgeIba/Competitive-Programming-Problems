#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli mid;


int posible(lli valorMedio,lli k, vector<lli> numeros)
{
	lli contador=0;
	lli aux;
	aux=valorMedio-numeros[mid];
	k-=aux;
	numeros[mid]=valorMedio;
	
	for (lli i=mid; i<numeros.size()-1; i++)
	{
		if (numeros[i]<=numeros[i+1])
		{
			continue;
		}
		else
		{
			if (numeros[i]-numeros[i+1] <= k )
			{
				k= k -(numeros[i]-numeros[i+1]);
				numeros[i+1]= numeros[i+1] + (numeros[i]-numeros[i+1]);
			}
			else
			{
				return -1;
			}
		}
	}	
	
	return numeros[mid];
	
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli n, k, aux;
	cin>>n>>k;
	vector<lli> numeros;
	for (int i=0; i<n; i++)
	{
		cin>>aux;
		numeros.push_back(aux);
	}
	
	sort(numeros.begin(), numeros.end());
	
	lli l,r;
	
	mid=(n-1)/2;
	
	l=numeros[mid];
	r=numeros[mid]+k;
	lli valorMedio, maxi=0, aux2;
	while(l<=r)
	{	
		valorMedio=l+(r-l)/2;
		
		aux2=posible(valorMedio, k, numeros);
		
		if (aux2!=-1)
		{
			maxi=max(maxi,aux2);
			l=valorMedio+1;
		}
		else
		{
			r=valorMedio-1;
		}
	}
	cout<<maxi<<endl;
		
	return 0;
}
