#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli arreglo[102][102];
lli dp[102][102];


lli funcion(lli row, lli col)
{
	lli abajo=0, der=0;
	if((row>=101)or(col>=101))
	{
		return 0;
	}
	if(dp[row][col]!=-1)
	{
		return dp[row][col];
	}
	abajo = funcion(row+1, col) + arreglo[row][col];
	der = funcion(row+1, col+1) + arreglo[row][col];
	
	return dp[row][col] = max(abajo,der);
}




int main()
{
	memset(dp,-1,sizeof(dp));
	for (int i=1; i<=100; i++)
	{
		for (int j=1; j<=i; j++)
		{
			cin>>arreglo[i][j];
		}
	}
	
	//for (int i=1; i<=100; i++)
	{
		//for (int j=1; j<=i; j++)
		{
			//cout<<arreglo[i][j]<<" ";
		}
	//	cout<<endl;
	}
	
	
	
	cout<<funcion(1,1)<<endl;
	
	return 0;
}
