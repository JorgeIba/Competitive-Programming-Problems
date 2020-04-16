#include <bits/stdc++.h>
#define lli long long int
using namespace std;

lli matriz[1005][1005];
lli dp[1005][1005];



lli maxi(lli i, lli j)
{
	if ((i >= 1002)or(j>=1002))
	{
		return 0;
	}
	if (dp[i][j]!=-1)
	{
		return dp[i][j];
	}
	lli izq=0,centro=0,der=0;
	
	if (j!=0)
	{
		izq= maxi(i+1, j-1) + matriz[i][j];
		centro= maxi(i+1, j) + matriz[i][j];
		der =maxi(i+1, j+1) + matriz[i][j];	
	}
	else
	{
		centro= maxi(i+1, j) + matriz[i][j];
		der=maxi(i+1, j+1) + matriz[i][j];	
	}
	dp[i][j]=max( max(izq,centro), der );
	
	return dp[i][j];
	
	
}



void funcion()
{
	memset(dp, -1, sizeof(dp));
	memset(matriz, 0, sizeof(matriz));
	lli n;
	cin>>n;
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			cin>>matriz[i][j];
		}
	}
	
	lli best=0;
	for (int i=0; i<n; i++)
	{
		maxi(0,i);
	}
	
	for (int i=0; i<n; i++)
	{
		best=max(best,dp[0][i]);
	}	
	cout<<best<<endl;
	
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
