#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli n;
	cin>>n;
	vector<lli> numeros(n+1);
	vector<lli> ordenados;
	for (int i=1; i<=n; i++)
	{
		cin>>numeros[i];
		if(numeros[i]==i)
		{
			ordenados.push_back(numeros[i]);
		}
	}
	
	if (ordenados.size()%2==0)
	{
		cout<<(lli)(ordenados.size()/2)<<endl;
		for (int i=0; i<ordenados.size(); i+=2)
		{
			cout<<ordenados[i]<<" "<<ordenados[i+1]<<endl;
		}
	}
	else if (ordenados.size()==1)
	{
		lli x = ordenados[0];
		cout<<1<<endl;
		for(int i=1; i<=n; i++)
		{
			if (x!=numeros[i])
			{
				cout<<x<<" "<<numeros[i]<<endl;
				return 0;
			}
		}
	}
	else
	{
		lli x = ordenados[ordenados.size()-1];
		cout<<(lli)(ordenados.size()/2 + 1)<<endl;
		for (int i=0; i<ordenados.size()-1; i+=2)
		{
			cout<<ordenados[i]<<" "<<ordenados[i+1]<<endl;
		}
		cout<<ordenados[0]<<" "<<x<<endl;
	}	
	return 0;
}
