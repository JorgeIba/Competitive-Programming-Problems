#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	int n, k, q;
	cin>>n>>k>>q;
	int suma[n+1];
	memset(suma, 0, sizeof(suma));
	for (int i=0; i<q; i++)
	{
		int aux;
		cin>>aux;
		suma[aux]++;
	}
	for (int i=1; i<=n; i++)
	{
		if (suma[i] + k - q>0)
		{
			cout<<"Yes\n";
		}
		else
		{
			cout<<"No\n";
		}
	}
	
	return 0;
}
