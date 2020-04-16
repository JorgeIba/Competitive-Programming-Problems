#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli n;
	cin>>n;
	int arreglo[n-1][2];
	for (int i=0; i<n-1; i++)
	{
		cin>>arreglo[i][0];
	}
	
	for (int i=n-2; i>=0; i--)
	{
		if (i==n-2)
		{
			arreglo[i][1]=arreglo[i][0];
			continue;
		}
		arreglo[i][1]=min(arreglo[i][0], arreglo[i+1][0]);
	}
	lli suma=arreglo[0][0];
	for (int i=0; i<n-1; i++)
	{
		suma+=arreglo[i][1];
	}
	
	cout<<suma<<endl;
	return 0;
}
