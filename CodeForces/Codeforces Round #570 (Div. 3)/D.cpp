#include <bits/stdc++.h>
#define lli long long int
using namespace std;

void funcion()
{
	lli n,suma=0, aux;
	cin>>n;
	vector<int> tam(n+1);
	for(lli i=1; i<=n; i++)
	{
		cin>>aux;
		tam[aux]++;
	}
	
	sort(tam.rbegin(), tam.rend());
	
	lli actual=tam[0];
	suma=actual;
	for(int i=1; i<tam.size(); i++)
	{
		if(actual==0)
		{
			break;
		}
		if (tam[i]<=actual-1)
		{
			suma+=tam[i];
			actual=tam[i];
		}
		else
		{
			suma+=actual-1;
			actual--;
		}
	}
	cout<<suma<<endl;
	return;
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli q;
	cin>>q;
	for (lli i=0; i<q; i++)
	{
		funcion();
	}
	return 0;
}
