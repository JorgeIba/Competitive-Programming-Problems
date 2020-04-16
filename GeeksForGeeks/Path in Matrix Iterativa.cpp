#include <bits/stdc++.h>
#define lli long long int
using namespace std;

void funcion()
{
	lli MAXIMO=0;
	lli n;
	cin>>n;
	lli matriz[n+3][n+3];
	memset(matriz, 0, sizeof(matriz));
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=n; j++)
		{
			cin>>matriz[i][j];
		}
	}
	
	for (int i=n; i>=1; i--)
	{
		for (int j=n; j>=1; j--)
		{
			lli aux = max ( matriz[i+1][j] + matriz[i][j], matriz[i+1][j+1] + matriz[i][j] );
			matriz[i][j] = max(aux, matriz[i+1][j-1] + matriz[i][j]);
			MAXIMO = max(MAXIMO, matriz[i][j]);
		}
	}
	cout<<MAXIMO<<endl;
}

int main()
{
	int q;
	cin>>q;
	while(q--)
	{
		funcion();
	}
	
	return 0;
}
