#include <bits/stdc++.h>
#define lli long long int
#define INF 1000000000000000LL
using namespace std;

string cadenas[100010][2];
lli costo[100010];
lli dp[100010][2][2];

lli n;

lli funcion (lli indice, lli estadoAnterior, lli estadoActual)
{	
	if (indice >= n)
	{
		return 0;
	}	
	if (dp[indice][estadoAnterior][estadoActual]!=-1)
	{
		return dp[indice][estadoAnterior][estadoActual];
	}
	string cadenaAnterior = cadenas[indice-1][estadoAnterior];
	string cadenaActual = cadenas[indice][estadoActual];
	if( cadenaActual.compare(cadenaAnterior) < 0 )
	{
		return INF;
	}
	
	lli si = funcion(indice+1, estadoActual, 1) + costo[indice+1];
	lli no = funcion(indice+1, estadoActual, 0);
	return dp[indice][estadoAnterior][estadoActual] = min(si,no);
	 
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	memset(dp, -1, sizeof(dp));
	cin>>n;
	
	for (int i=0; i<n; i++)
	{
		lli x;
		cin>>x;
		costo[i]=x;
	}
	for (int i=0; i<n; i++)
	{
		string s;
		cin>>s;
		cadenas[i][0] = s;
		reverse(s.begin(), s.end());
		cadenas[i][1] = s;
	}
	lli mini = min( funcion(1, 0, 0), funcion(1, 0, 1) + costo[1]);
	lli mini2 = min( funcion(1,1,0) + costo[0], funcion(1,1,1) + costo[0] + costo[1] );
	lli resultado = min(mini,mini2);
	if (resultado>=INF)
	{
		cout<<-1<<endl;
	}
	else
	{
		cout<<resultado<<endl;	
	}
	
	
	return 0;
}
