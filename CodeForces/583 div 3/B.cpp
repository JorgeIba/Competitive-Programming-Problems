#include <bits/stdc++.h>
#define lli long long int
using namespace std;
 
void funcion()
{
	lli n, aux=0, contador=0;
	cin>>n;
	vector<lli> arreglo2;
	vector<vector<lli> > arreglo(n);
	
	for(int i=0; i<n; i++)
	{
		cin>>aux;
		arreglo2.push_back(aux);
	}
		if (n==1)
	{
		cout<<0<<endl;
		return;
	}
	arreglo[0]=arreglo2;
	arreglo[1]=arreglo2;

	arreglo[1][n-1]=arreglo[0][n-1];

	for (int i=n-2; i>=0; i--)
	{
		aux=min(arreglo[0][i+1], arreglo[1][i+1]);
		
		if (arreglo[0][i]>aux)
		{
			contador++;
			arreglo[1][i]=aux;
		}
		else
		{
			arreglo[1][i]=arreglo[0][i];
		}
	}
	
//	for (int i=0; i<2; i++)
	{
//		for (int j=0; j<n; j++)
		{
//			cout<<arreglo[i][j]<<" ";
		}
//		cout<<endl;
	}
	
	cout<<contador<<endl;
	return;
	
}
 
 
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli t;
	cin>>t;
	for(int i=0; i<t; i++)
	{
		funcion();
	}
	return 0;
}

