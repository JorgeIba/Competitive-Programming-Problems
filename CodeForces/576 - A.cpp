#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int main()
{
	lli n;
	cin>>n;
	bool arreglo[n+1];
	memset(arreglo, false, sizeof(arreglo));
	
	for(lli i=2; i<=n; i++)
	{
		for (lli j=i+1; j<=n; j++)
		{
			lli lcm = i*j / __gcd(i,j);
			//cout<<i<<" "<<j<<" "<<lcm<<endl;
			if ((lcm <= n)and(i!=lcm)and(j!=lcm))
			{
				arreglo[lcm] = true;
			}
		}
	}
	lli contador=0;
	for (lli i=2; i<=n; i++)
	{
		if (arreglo[i]==false)
		{
			contador++;
		}
	}
	cout<<contador<<endl;
	
	for (lli i=2; i<=n; i++)
	{
		if (arreglo[i]==false)
		{
			cout<<i<<" ";
		}
	}
	
	return 0;
}
