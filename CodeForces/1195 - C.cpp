#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli matr[2][100001];
lli dp[100001][2];


lli funcion(lli indice, lli fila)
{
	lli arribaSi=0, arribaNo=0, abajoNo=0, abajoSi=0;
	if (indice>=100001)
	{
		return 0;
	}
	if (dp[indice][fila]!=-1)
	{
		return dp[indice][fila];
	}

	if (fila==0)
	{
		abajoSi=funcion(indice+1, 1) + matr[0][indice];
		abajoNo=funcion(indice+1, 0);
	}
	else
	{
		arribaSi=funcion(indice+1, 0) + matr[1][indice];
		arribaNo=funcion(indice+1, 1);
	}
		
	
	dp[indice][fila] = max(max(abajoSi, abajoNo), max(arribaSi,arribaNo));
	return dp[indice][fila];
}



int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	memset(dp, -1, sizeof(dp));
	lli n;
	cin>>n;
	for (lli i=0; i<2; i++)
	{
		for (lli j=0; j<n; j++)
		{
			cin>>matr[i][j];
		}
	}
	lli maxi=max(funcion(0,0), funcion(0,1));
	cout<<maxi<<endl;
	
	return 0;
}
