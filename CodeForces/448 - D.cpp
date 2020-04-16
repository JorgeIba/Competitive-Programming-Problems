#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	lli n,m;
	cin>>n>>m;
	vector<lli> numeros;
	for (int i=1; i<=n; i++)
	{
		for (int j=1; j<=m; j++)
		{
			cout<<i*j<<" ";
			numeros.push_back(i*j);
		}
		cout<<endl;
	}
	cout<<endl;
	
	sort(numeros.begin(), numeros.end());
	
	for(auto x: numeros)
	{
		cout<<x<<" ";
	}
	
	return 0;
}
