#include <bits/stdc++.h>
#define lli long long unsigned int
using namespace std;
lli arreglo[30][30];



int main()
{
	
	memset(arreglo,0,sizeof(arreglo));
	for (int i=3; i<=22; i++)
	{
		for (int j=3; j<=22; j++)
		{
			cin>>arreglo[i][j];
		}
	}
	lli maxi=0;
	for (int i=3; i<=22; i++)
	{
		for (int j=3; j<=22; j++)
		{
			lli arri=arreglo[i][j]*arreglo[i-1][j-1]*arreglo[i-2][j-2]*arreglo[i-3][j-3];
			maxi=max(maxi,arri);
			lli arr=arreglo[i][j]*arreglo[i-1][j]*arreglo[i-2][j]*arreglo[i-3][j];
			maxi=max(maxi,arr);
			lli arrd=arreglo[i][j]*arreglo[i-1][j+1]*arreglo[i-2][j+2]*arreglo[i-3][j+3];
			maxi=max(maxi,arrd);
			lli der=arreglo[i][j]*arreglo[i][j+1]*arreglo[i][j+2]*arreglo[i][j+3];
			maxi=max(maxi,der);
			lli abad=arreglo[i][j]*arreglo[i+1][j+1]*arreglo[i+2][j+2]*arreglo[i+3][j+3];
			maxi=max(maxi,abad);
			lli aba=arreglo[i][j]*arreglo[i+1][j]*arreglo[i+2][j]*arreglo[i+3][j];
			maxi=max(maxi,aba);
			lli abi=arreglo[i][j]*arreglo[i+1][j-1]*arreglo[i+2][j-2]*arreglo[i+3][j-3];
			maxi=max(maxi,abi);
			lli izq=arreglo[i][j]*arreglo[i][j-1]*arreglo[i][j-2]*arreglo[i][j-3];
			maxi=max(maxi,izq);
			
		}
	}
	cout<<maxi<<endl;
	
	return 0;
}

