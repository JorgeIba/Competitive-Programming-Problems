#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	unordered_multiset<lli> check;
	lli n,aux;
	cin>>n;
	lli best=n+1;
	vector<pair<lli, lli> > numeros(n);
	
	for (int i=0; i<n; i++)
	{
		cin>>aux;
		numeros[i].first=aux;
		check.insert(aux);
	}
	
	for (int i=0; i<n; i++)
	{
		if (check.count(numeros[i].first)==1)
		{
			numeros[i].second=0;
		}
		else
		{
			numeros[i].second= check.count(numeros[i].first);
			check.erase(check.find(numeros[i].first));
		}
	}
	
	lli l=0, numAux;
	for (int i=0; i<n; i++)
	{
		if (numeros[i].second!=0)
		{
			numAux=numeros[i].first;
			l=i;
			break;
		}
	}
	
	lli r=0;
	
	for (int i=n-1; i>=0; i--)
	{
		if (numeros[i].second!=0)
		{
			r=i;
			break;
		}
	}
	bool flag=false;
	
	for (int i=l+1; i<=r; i++)
	{
		if(numeros[i].first==numAux)
		{
			l++;
			break;
		}
	}
	r=r+1 -l;
	cout<<r<<endl;
	
	return 0;
}
