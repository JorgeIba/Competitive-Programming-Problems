#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli n;
	cin>>n;
	lli potencia = pow(2,n);
	vector<lli> numeros(potencia);
	for(lli i=0; i<potencia; i++)
	{
		cin>>numeros[i];
	}
	sort(numeros.begin(), numeros.end());
	for(lli i=1; i<potencia; i++)
	{
		cout<<numeros[i];
	}
	
	
	return 0;
}
