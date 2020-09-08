#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli n;
	cin>>n;
	vector<lli> numeros(n);
	for (int i=0; i<n; i++)
	{
		cin>>numeros[i];
	}
	
	lli resmin=1e9;
	lli resmax=0;
	
	for (int i=0; i<n; i++)
	{
		if (i==0)
		{
		resmin=abs(numeros[i] - numeros[i+1]);
		resmax=abs(numeros[i] - numeros[n-1]);
		cout<<resmin<<" "<<resmax<<endl;
			continue;
		}
		if (i==n-1)
		{
			resmin=abs(numeros[i] - numeros[i-1]);
			resmax=abs(numeros[i] - numeros[0]);
			cout<<resmin<<" "<<resmax<<endl;
			continue;
		}
		
		resmin=min( abs(numeros[i] - numeros[i-1])  , abs(numeros[i] - numeros[i+1])  );
		resmax=max( abs(numeros[i] - numeros[0])  , abs(numeros[i] - numeros[n-1]) );
		cout<<resmin<<" "<<resmax<<endl;
	}	
	return 0;
}
