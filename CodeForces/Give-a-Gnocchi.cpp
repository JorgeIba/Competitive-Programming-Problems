#include <bits/stdc++.h>
#define lli long long int
using namespace std;

vector<bool> primos;
lli n, k;
void inicializar()
{
	lli lim = 2000100;
	primos.resize(lim, false);
	primos[1]=false;
	for (lli i=4; i<=lim; i+=2)
	{
		primos[i]=true;
	}
	for (lli i=3; i<=lim; i+=2)
	{
		if (primos[i]==false)
		{
			if (i*i<=lim)
			{
				for (lli j=i*i; j<=lim; j+=2*i)	
				{
					primos[j] = true;
				}
			}
			
		}
	}
}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k;
	inicializar();
	bool arreglo[2000100];	
	for (lli i=2; i<=n; i++)
	{
		if((arreglo[i] == false)and(primos[i] == false))
		{
			for(lli j=2; j*i<=2000100; j++)
			{
				arreglo[i*j] = true;
				//cout<<i<<" "<<j<<" "<<i*j<<endl;
			}		
		}
	}
	lli contador=0;
	
	for (lli i=n*n; i<=2000100; i++)
	{
		if ((primos[i]==true)and(arreglo[i]==false))
		{
			contador++;
			if (contador==k)
			{
				cout<<i<<endl;
				return 0;
			}
		}
	}
		
	return 0;
}
