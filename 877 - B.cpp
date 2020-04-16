#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli n;
	cin>>n;
	char cadena[2][n];
	for (int i=0; i<n; i++)
	{
		cin>>cadena[0][i];
	}
	if (n==1)
	{
		cout<<1<<endl;
		return 0;
	}
	cadena[1][0]=1;
	lli best=0;
	for (int i=1; i<n; i++)
	{
		if (cadena[0][i]=='b')
		{
			if (cadena[0][i-1]=='b')
			{
				cadena[1][i]=cadena[1][i-1]+1;
			}
			else
			{
				cadena[1][i]=2;
			}
		}
		else
		{
			if (cadena[0][i-1]=='b')
			{
				cadena[1][i]=cadena[1][i-1]+1;
			}
			else
			{
				cadena[1][i]=2;
			}
		}
	}
	
	for(int i=0; i<2; i++)
	{
		for (int j=0; j<n; j++)
		{
			cout<<cadena[i][j]<<" ";
		}
		cout<<endl;
	}
	
	
	
	
	return 0;
}
