#include <bits/stdc++.h>
#define lli long long int
#define MOD 998244353
using namespace std;

int main()
{
	lli n;
	cin>>n;
	vector<lli> numeros(n);
	for(int i=0; i<n; i++)
	{
		cin>>numeros[i];
	}
	lli suma = 0;
	for (int i=0; i<n-1; i++)
	{
		for (int j=i+1; j<n; j++)
		{
			//cout<<numeros[i]<<" -> "<<numeros[j]<<"   ";
			suma += numeros[i]*numeros[j];
		}
	}
	cout<<(lli)(suma%MOD)<<endl;
	
	return 0;
}
