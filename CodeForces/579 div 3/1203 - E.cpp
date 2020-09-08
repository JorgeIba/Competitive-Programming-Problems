#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	lli n;
	cin>>n;
	lli arreglo[150010][2];
	lli maxi=0;
	memset(arreglo, 0, sizeof(arreglo));
	for (int i=0; i<n; i++)
	{
		lli x;
		cin>>x;
		maxi=max(maxi,x);
		arreglo[x][0]++;
	}
	
	
	for (int i=1; i<=maxi+1; i++)
	{
		if(( arreglo[1][0] >= 2 )and(i==1))
		{
			arreglo[2][1]++;
			arreglo[1][1]++;
		}
		else if ((arreglo[1][0]==1)and(i==1))
		{
			arreglo[1][1]++;
		}
		if (i==1)
		{
			continue;
		}
		if (arreglo[i][0]>=1)
		{
			if(arreglo[i-1][1]==0)
			{
				arreglo[i-1][1]++;
				arreglo[i][0]--;
			}
			if((arreglo[i][1]==0)and(arreglo[i][0]>=1))
			{
				arreglo[i][1]++;
				arreglo[i][0]--;
			}
			if (arreglo[i][0]>=1)
			{
				arreglo[i+1][1]++;
				arreglo[i][0]--;
			}
		}
	}
	lli contador=0;
	for (int i=1; i<=maxi+1; i++)
	{
		//cout<<i<<" -> "<<arreglo[i][1]<<endl;
		if (arreglo[i][1]!=0)
		{
			contador++;
		}
	}
	cout<<contador<<endl;


	return 0;	
}
