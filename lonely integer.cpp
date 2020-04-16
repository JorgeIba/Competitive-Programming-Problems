#include <bits/stdc++.h>
using namespace std;
int main()
{
	int numero=0, n=0, mask=0, res=0;
	vector<int> numeros;
	cin>>n;
	for (int i=0; i<n; i++)
	{
		cin>>numero;
		numeros.push_back(numero);
	}
	for (int x=0; x<n; x++)
	{
		res^=numeros[x];
	}
	cout<<res;
	return 0;
}
