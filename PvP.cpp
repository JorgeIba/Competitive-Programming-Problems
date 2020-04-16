#include <bits/stdc++.h>
#define lli long long int
using namespace std;


stack< lli > pila;
lli contador=0;

void funcion1(lli n)
{
	lli maximo=0;
	vector<lli> numeros(n);
	for (lli i=0; i<n; i++)
	{
		cin>>numeros[i];
	}
		
	for (lli i=n-1; i>=0; i--)
	{
		if (pila.empty())
		{
			pila.push(numeros[i]);	
		}
		else
		{
			while ( (!pila.empty()) and (numeros[i]>pila.top()) ) 
			{
				pila.pop();
				contador++;
			}
			pila.push(numeros[i]);
		}
		maximo=max(maximo,contador);
		contador=0;
		
	}
	cout<<maximo<<endl;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli n;
	cin>>n;
	funcion1(n);
	return 0;
}
