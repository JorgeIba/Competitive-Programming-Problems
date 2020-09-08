#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli n;
	cin>>n;
	lli matriz[n+1][n+1];
	memset(matriz, 0, sizeof(matriz));
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=i; j++)
		{
			cin>>matriz[i][j];
		}
	}
	
	
	for (int i=n-1; i>=1; i--)
	{
		for (int j=n-1; j>=1; j--)
		{
			matriz[i][j] = max ( matriz[i+1][j] + matriz[i][j], matriz[i+1][j+1] + matriz[i][j] );
		}
	}
	lli maxi=0;
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=i; j++)
		{
			maxi=max(maxi, matriz[i][j]);
		}
	}
	cout<<maxi<<endl;
	
	return 0;
}
