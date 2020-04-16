#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	lli n;
	cin>>n;
	vector<lli> numeros(n);
	lli maxi=-1;
	for (int i=0; i<n; i++)
	{
		cin>>numeros[i];
		maxi=max(maxi,numeros[i]);
	}
	vector<lli> aux;
	lli gcd=0;
	for (int i=0; i<n; i++)
	{
		if(numeros[i]!=maxi)
		{
			aux.push_back(maxi-numeros[i]);
			gcd=__gcd(gcd, maxi-numeros[i]);
		}
	}
	lli res=0;
	for (int i=0; i<aux.size(); i++)
	{
		res+= (aux[i]/gcd);
	}
	cout<<res<<" "<<gcd<<endl;
	
	
	
	return 0;
}
