#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli n,k,aux;
	cin>>n>>k;
	lli contador=0;
	vector<lli> numeros(n+1);
	for(int i=1; i<=n; i++)
	{
		cin>>numeros[i];
	}
	for (int i=1; i<=n; i++)
	{
		if ((numeros[i]>0)and(numeros[i]>=numeros[k]))
		{
			contador++;
		}
	}
	cout<<contador<<endl;
	return 0;
}
