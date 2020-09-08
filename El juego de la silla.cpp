#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int busquedaB(vector<lli> sillas, lli numero)
{
	lli medio, inferior=0, superior=sillas.size()-1;
	
	if (sillas[inferior]>numero)
	{
		return sillas[inferior]-numero;
	}
	if (sillas[superior]<numero)
	{
		return numero-sillas[superior];
	}
	while (inferior<=superior)
	{
		medio=(inferior+superior)/2;
		if (numero==sillas[medio])
		{
			return 0;
		}
		else if (numero>sillas[medio])
		{
			if (numero>sillas[medio+1])
			{
				inferior=medio+1;
			}
			else if (numero<sillas[medio+1])
			{
				return (min(numero-sillas[medio], sillas[medio+1] - numero ));
			}
		}
		else if (numero<sillas[medio])
		{
			if (numero<sillas[medio-1])
			{
				superior=medio-1;	
			}
			else if (numero>sillas[medio-1])
			{
				return (min(sillas[medio]-numero, numero-sillas[medio-1]));
			}
		}
	}
	
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n, p, q;
	cin>>n;
	vector<lli> sillas(n);
	for (int i=0; i<n; i++)
	{
		cin>>sillas[i];
	}
	sort(sillas.begin(), sillas.end());
	cin>>p;
	for (int i=0; i<p; i++)
	{
		cin>>q;
		cout<<busquedaB(sillas, q)<<endl;
	}
	return 0;
}
